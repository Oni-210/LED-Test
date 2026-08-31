#include "beatsync.h"

const char* EYE_PATH = "beatsync/eyes.bin";
const char* MOUTH_PATH = "beatsync/eyes.bin"; // See NUM_MOUTH_SIZE for how many frames back to back

const Color COLORS[6] = {
    {255, 0, 0},
    {255, 128, 0},
    {255, 255, 0},
    {0, 255, 0},
    {0, 0, 255},
    {100, 0, 100}
};
const float COLOR_CHANGE_RATE = 0.05;

const int MAX_FLASH_BRIGHTNESS = 200;
const int FLASH_FALLOFF_RATE = 5;

const int MAX_EYE_SHIFT = 5;
const int EYE_SHIFT_RATE = 1;

const int NUM_MOUTH_SIZES = 8;
const int MOUTH_CLOSE_RATE = 1;

Beatsync::Beatsync(float& avg_volume) : avg_volume(avg_volume) {
    SD.begin();
    eye_file = SD.open(EYE_PATH);
    mouth_file = SD.open(MOUTH_PATH);
}

std::unique_ptr<Color[]> Beatsync::run() {
    if (current_color_fraction >= 1){
        current_color = (current_color + 1) % sizeof(COLORS);
        current_color_fraction = 0;
    }  else {
        current_color += COLOR_CHANGE_RATE * avg_volume;
    }

    if (flash_brightness > 0) {
        flash_brightness -= FLASH_FALLOFF_RATE;
    }

    if (eye_shift > 0) {
        eye_shift -= EYE_SHIFT_RATE;
    }

    if (mouth_size > 0) {
        mouth_size -= MOUTH_CLOSE_RATE;
    }


    Color current_shade;
    current_shade.red = COLORS[current_color].red * current_color_fraction + COLORS[current_color == 0 ? sizeof(COLORS) : current_color - 1].red * (1 - current_color_fraction);
    current_shade.green = COLORS[current_color].green * current_color_fraction + COLORS[current_color == 0 ? sizeof(COLORS) : current_color - 1].green * (1 - current_color_fraction);
    current_shade.blue = COLORS[current_color].blue * current_color_fraction + COLORS[current_color == 0 ? sizeof(COLORS) : current_color - 1].blue * (1 - current_color_fraction);
    auto frame = std::make_unique<Color[]>(MATRIX_WIDTH * MATRIX_HEIGHT);

    eye_file.seek(0);
    mouth_file.seek(mouth_size * MATRIX_WIDTH * MATRIX_HEIGHT * 3);
    for (int pixel = 0; pixel < MATRIX_WIDTH * MATRIX_HEIGHT; ++pixel) {
        frame[pixel].red = min(current_shade.red, max(eye_file.read(), mouth_file.read()));
        frame[pixel].green = min(current_shade.green, max(eye_file.read(), mouth_file.read()));
        frame[pixel].blue = min(current_shade.blue, max(eye_file.read(), mouth_file.read()));
    }

    return frame;
}

void Beatsync::lowCB() {
    eye_shift = MAX_EYE_SHIFT;
}

void Beatsync::midCB() {
    mouth_size = NUM_MOUTH_SIZES - 1;
}

void Beatsync::highCB() {
    flash_brightness = MAX_FLASH_BRIGHTNESS;
}