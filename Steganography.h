/**
 * @file Steganography.h
 * @author Gabriel Speer and Justin Finn
 * @date 2023-09-20
 * @brief Header file containing the Steganography class declaration
 *
 * Contains all method declarations and private member variables
 * for encoding and decoding hidden messages inside PPM images
 * using least-significant bit (LSB) steganography.
 */

#ifndef STEGANOGRAPHY_H
#define STEGANOGRAPHY_H
#include <vector>
#include <string>

class Steganography {
 private:
  // PPM format identifier (e.g. "P3")
  std::string magicNumber;
  // Image dimensions
  int width;
  int height;
  // Maximum color value
  int maxColor;
  // Stores all RGB pixel values as integers
  std::vector<int> colorData;
  // Holds the hidden message text
  std::string cipherText;

  /**
   * Extracts the nth bit of a character for LSB embedding
   * @param cipherChar The character to extract a bit from
   * @param n The bit position (0-7, MSB to LSB)
   * @return The bit value (0 or 1)
   */
  int getNthBit(char cipherChar, int n);

 public:
  /**
   * Reads a PPM image file and loads pixel data into colorData
   * @param fileName Name of the PPM file (without extension)
   */
  void readImage(std::string fileName);

  /**
   * Writes the current pixel data out to a new PPM file
   * @param fileName Name of the output file (without extension)
   */
  void printImage(std::string fileName);

  /**
   * Reads the full contents of a text file into cipherText
   * @param fileName Name of the text file (without extension)
   */
  void readCipherText(std::string fileName);

  /**
   * Writes the decoded cipherText out to a text file
   * @param fileName Name of the output file (without extension)
   */
  void printCipherText(std::string fileName);

  /**
   * Zeroes the least significant bit of every pixel value
   * to prepare the image for clean message embedding
   */
  void cleanImage();

  /**
   * Encodes cipherText into the image using LSB steganography
   * Embeds each character bit-by-bit into pixel LSBs
   * Appends a null terminator so the decoder knows where to stop
   */
  void encipher();

  /**
   * Reads LSBs from pixel data and reconstructs the hidden message
   * Stops decoding when a null terminator character is encountered
   */
  void decipher();
};

#endif // STEGANOGRAPHY_H
