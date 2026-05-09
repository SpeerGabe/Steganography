# Steganography

Hides secret text messages inside PPM images using least-significant bit (LSB) steganography. The encoded image is visually identical to the original — the hidden message is undetectable to the human eye.

## How It Works

Every pixel in a PPM image has RGB values (0-255). This program replaces the least significant bit of each value with one bit of the hidden message. Since flipping the LSB changes a color value by at most 1, the difference is imperceptible.

Each character requires 8 pixels to encode. A null terminator is embedded after the message so the decoder knows exactly where to stop.

## How to Run

```bash
make
./steganography
```

Choose `E` to encode or `D` to decode. Enter filenames without extensions when prompted.

## Example

```
# Encode
Enter operation: E
Enter PPM filename: cake
Enter text file to hide: secret
Enter output filename: cake_encoded
→ Message encoded into cake_encoded.ppm

# Decode
Enter operation: D
Enter encoded PPM filename: cake_encoded
Enter output filename: decoded_message
→ Message decoded into decoded_message.txt
```

## Files

| File | Description |
|---|---|
| `Steganography.cpp` | Core encode/decode logic |
| `Steganography.h` | Class declaration |
| `main.cpp` | User interface and program entry point |
| `cake.ppm` | Sample cover image |
| `cypher.txt` | Sample message to hide |
