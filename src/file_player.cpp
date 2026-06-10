#include "file_player.h"

FilePlayer::FilePlayer(Matrix* matrix) : Visual(matrix) {
    SD.begin(BUILTIN_SDCARD);
}

void FilePlayer::run() {
    if (!file) {
        return;
    }
    if (isPalette) {
        uint8_t* frame = new uint8_t[kMatrixWidth * kMatrixHeight];
        for (int x = 0; x < kMatrixWidth; x++) {
            for (int y = 0; y < kMatrixHeight; y++) {
                frame[y * kMatrixWidth + x] = file.read();
            }
        }
        matrix->bufferPaletteFrame(frame);
        delete[] frame;
    } else {
        rgb24* frame = new rgb24[kMatrixWidth * kMatrixHeight];
        for (int x = 0; x < kMatrixWidth; x++) {
            for (int y = 0; y < kMatrixHeight; y++) {
                uint8_t r = file.read();
                uint8_t g = file.read();
                uint8_t b = file.read();
                frame[y * kMatrixWidth + x] = rgb24(r, g, b);
            }
        }
        matrix->bufferFrame(frame);
        delete[] frame;
    }
}

FileError FilePlayer::loadFile(const char* filename) {
    if (!SD.exists(filename)) {
        return FileError::FileNotFound;
    }
    File new_file = SD.open(filename);
    if (!new_file) {
        return FileError::UnknownError;
    }
    if (new_file.size() / (isPalette ? 1 : 3) != kMatrixWidth * kMatrixHeight) {
        new_file.close();
        return FileError::InvalidFormat;
    }
    file = new_file;
    return FileError::None;
}