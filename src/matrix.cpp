#include "matrix.h"

Matrix::Matrix() {
    matrix.addLayer(&backgroundLayer);
    matrix.begin();
}

int Matrix::nextFrame() {
    int return_val = frames_since_last_call;
    frames_since_last_call = 0;
    return return_val;
}

void Matrix::bufferFrame(rgb24* frame) {
    for (int y = 0; y < kMatrixHeight; y++) {
        for (int x = 0; x < kMatrixWidth; x++) {
            backgroundLayer.drawPixel(x, y, frame[y * kMatrixWidth + x]);
        }
    }
}

void Matrix::bufferPaletteFrame(uint8_t* frame) {
    for (int y = 0; y < kMatrixHeight; y++) {
        for (int x = 0; x < kMatrixWidth; x++) {
            backgroundLayer.drawPixel(x, y, palette[frame[y * kMatrixWidth + x]]);
        }
    }
}

void Matrix::setPalette(uint8_t* new_palette) {
    for (int i = 0; i < 256; i++) {
        palette[i] = new_palette[i];
    }
}

void Matrix::run() {
    if (last_frame_time == 0) {
        last_frame_time = millis();
    } else {
        unsigned long current_time = millis();
        if (current_time - last_frame_time >= 17) {  // ~60fps
            frames_since_last_call += (current_time - last_frame_time) / 17;
            last_frame_time = current_time;
        } else {
            return;
        }
    }
    backgroundLayer.swapBuffers();
}