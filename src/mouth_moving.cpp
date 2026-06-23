#include "mouth_moving.h"

MouthMoving::MouthMoving(Matrix* matrix, char* eye_file_path, char* mouth_file_path) : Visual(matrix) {
    SD.begin();
    if (SD.exists(mouth_file_path)) {
        mouth_file = SD.open(mouth_file_path);
    }
    if (SD.exists(eye_file_path)) {             //TODO: Check for correct file size
        eye_file = SD.open(eye_file_path);
    }
}

void MouthMoving::run() {
    rgb24* frame = new rgb16[kMatrixHeight * kMatrixWidth];
    eye_file.seek(0);
    for (int i = 0; i < (kMatrixHeight * kMatrixWidth / 2) - 1; i++) {
        frame[i] = eye_file.read();
    }

    mouth_file.seek((kMatrixHeight * kMatrixWidth / 2) * openness);
    for (int i = kMatrixHeight * kMatrixWidth / 2; i < kMatrixHeight * kMatrixWidth; i++) {
        frame[i] = mouth_file.read();
    }

    matrix->bufferFrame(frame);
}