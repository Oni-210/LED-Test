#include "fs_player.h"

FSPlayer::FSPlayer(char* filepath) {
    SD.begin(BUILTIN_SDCARD);
    file = SD.open(filepath, FILE_READ);

    frame_count = (file.size() / (MATRIX_WIDTH * MATRIX_HEIGHT)) - 1;
}

FSPlayer::~FSPlayer() {
    file.close();
}

std::unique_ptr<Color[]> FSPlayer::run() {
    if (current_frame >= frame_count) {
        current_frame = 0;
    }

    auto frame = std::make_unique<Color[]>(MATRIX_WIDTH * MATRIX_HEIGHT);
    file.seek(current_frame * MATRIX_WIDTH * MATRIX_HEIGHT * 3);
    for (int pixel = 0; pixel < MATRIX_WIDTH * MATRIX_HEIGHT; ++pixel) {
        frame[pixel].red = file.read();
        frame[pixel].green = file.read();
        frame[pixel].blue = file.read();
    };

    if (current_frame >= frame_count) {
        current_frame = 0;
    } else {
        ++current_frame;
    }
    
    return frame;
}