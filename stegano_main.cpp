/**
 * @file main.cpp
 * @author Gabriel Speer and Justin Finn
 * @date 2023-09-25
 * @brief Entry point for the LSB steganography program
 *
 * Accepts user input to either encode a hidden text message
 * into a PPM image or decode a previously encoded PPM image
 * back into readable text.
 */

#include <iostream>
#include <string>
#include "Steganography.h"

using namespace std;

int main() {
    string PPM;
    string textfile;
    string outputName;
    Steganography stegano;

    cout << "Steganography — LSB Image Encoding/Decoding" << endl;
    cout << "Enter operation (E to encode, D to decode): ";
    char operation;
    cin >> operation;
    operation = tolower(operation);

    if (operation == 'e') {
        // --- ENCODING ---
        cout << "Enter the PPM filename (without extension): ";
        cin >> PPM;
        stegano.readImage(PPM);

        cout << "Enter the text filename to hide (without extension): ";
        cin >> textfile;
        stegano.readCipherText(textfile);

        stegano.encipher();

        cout << "Enter the output PPM filename (without extension): ";
        cin >> outputName;
        stegano.printImage(outputName);

        cout << "Message encoded successfully into '" << outputName << ".ppm'" << endl;

    } else if (operation == 'd') {
        // --- DECODING ---
        cout << "Enter the encoded PPM filename (without extension): ";
        cin >> PPM;
        stegano.readImage(PPM);

        stegano.decipher();

        cout << "Enter the output text filename (without extension): ";
        cin >> textfile;
        stegano.printCipherText(textfile);

        cout << "Message decoded successfully into '" << textfile << ".txt'" << endl;

    } else {
        cout << "Invalid operation. Please enter E or D." << endl;
        return 1;
    }

    return 0;
}
