/**
 * @file Steganography.cpp
 * @author Gabriel Speer and Justin Finn
 * @date 2023-09-25
 * @brief Implementation of the Steganography class
 *
 * Contains all method implementations for encoding and decoding
 * hidden text messages inside PPM images using least-significant
 * bit (LSB) steganography.
 */

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "Steganography.h"

using namespace std;


void Steganography::readImage(string fileName) {
    ifstream file;
    file.open(fileName + ".ppm");

    // Validate file opened successfully
    if (!file.is_open()) {
        cerr << "Error: could not open image file '" << fileName << ".ppm'" << endl;
        exit(1);
    }

    // Read PPM header: magic number, dimensions, max color value
    file >> magicNumber >> width >> height >> maxColor;

    // Load all pixel color values into the vector
    int value = 0;
    while (file >> value) {
        colorData.push_back(value);
    }
    file.close();
}

void Steganography::printImage(string fileName) {
    fileName = fileName + ".ppm";
    ofstream outFile(fileName);

    if (!outFile.is_open()) {
        cerr << "Error: could not write image file '" << fileName << "'" << endl;
        exit(1);
    }

    // Write PPM header
    outFile << magicNumber << "\n";
    outFile << width << " " << height << "\n";
    outFile << maxColor << "\n";

    // Write pixel data
    for (auto it = colorData.begin(); it != colorData.end(); ++it) {
        outFile << *it << " ";
    }
    outFile.close();
}

void Steganography::readCipherText(string fileName) {
    ifstream file;
    file.open(fileName + ".txt");

    if (!file.is_open()) {
        cerr << "Error: could not open text file '" << fileName << ".txt'" << endl;
        exit(1);
    }

    // Read full file contents including multiple lines
    string line;
    while (getline(file, line)) {
        if (!cipherText.empty()) cipherText += "\n";
        cipherText += line;
    }
    file.close();
}

void Steganography::printCipherText(string fileName) {
    fileName = fileName + ".txt";
    ofstream outFile(fileName);

    if (!outFile.is_open()) {
        cerr << "Error: could not write text file '" << fileName << "'" << endl;
        exit(1);
    }

    outFile << cipherText << endl;
    outFile.close();
}

void Steganography::cleanImage() {
    // Zero the LSB of every pixel value to prepare for encoding
    for (auto it = colorData.begin(); it != colorData.end(); ++it) {
        *it = *it - (*it % 2);
    }
}

void Steganography::encipher() {
    cleanImage();

    // Append null terminator so decipher knows where the message ends
    string message = cipherText + '\0';

    int length = message.length();
    auto it = colorData.begin();

    // Embed each character's 8 bits into 8 consecutive pixel LSBs
    for (int count = 0; count < length; count++) {
        char ch = message[count];
        for (int cycle = 0; cycle < 8; cycle++) {
            if (it == colorData.end()) {
                cerr << "Error: message too long for this image." << endl;
                return;
            }
            *it = *it + getNthBit(ch, cycle);
            ++it;
        }
    }
}

void Steganography::decipher() {
    string d = "";

    // Extract the LSB from every pixel value
    for (auto it = colorData.begin(); it != colorData.end(); ++it) {
        d += to_string(*it % 2);
    }

    cipherText = "";
    int size = d.length() / 8;

    // Reconstruct characters from every 8-bit group
    for (int i = 0; i < size; i++) {
        string byte = d.substr(i * 8, 8);
        int base = 1;
        int dec_value = 0;

        // Convert binary string to integer
        for (int j = 7; j >= 0; j--) {
            if (byte[j] == '1') {
                dec_value += base;
            }
            base *= 2;
        }

        // Stop decoding at null terminator
        if (dec_value == 0) break;

        cipherText += static_cast<char>(dec_value);
    }
}

int Steganography::getNthBit(char cipherChar, int n) {
    int store[8];
    int letter = static_cast<int>(cipherChar);
    int count = 0;

    // Convert character to binary representation
    while (letter != 0) {
        store[count] = letter % 2;
        letter = letter / 2;
        count++;
    }

    // Pad remaining bits with 0
    while (count < 8) {
        store[count] = 0;
        count++;
    }

    // Reverse to get MSB-first order
    for (int tic = 0; tic < 4; tic++) {
        int temp = store[tic];
        store[tic] = store[7 - tic];
        store[7 - tic] = temp;
    }

    return store[n];
}
