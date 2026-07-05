#include "glitch_effect.h"

const int GLITCH_CHANCE = 5;
const int GLITCH_AMOUNT_MIN = 10;
const int GLITCH_AMOUNT_MAX = 20;

void GlitchEffect::run(std::unique_ptr<Color[]> frame) {
    auto row_buffer = std::make_unique<Color[]>(MATRIX_WIDTH * MATRIX_HEIGHT);

    for (int y = 0; y < MATRIX_HEIGHT; ++y) {
        if (rand() % 100 < GLITCH_CHANCE) {
            for (int x = 0; x < MATRIX_WIDTH; ++x) {
                row_buffer[x] = frame[x + MATRIX_WIDTH * y];
            }

            int row_shift = rand() % (GLITCH_AMOUNT_MAX - GLITCH_AMOUNT_MIN) + GLITCH_AMOUNT_MIN;
            for (int x = 0; x < MATRIX_WIDTH; ++x) {
                frame[x + MATRIX_WIDTH * y] = row_buffer[(rand() % 2 == 0 ? x + row_shift : x - row_shift) % MATRIX_WIDTH];
            }
        }
    }
}