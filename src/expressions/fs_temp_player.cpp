#include "fs_temp_player.h"

FSTempPlayer::FSTempPlayer(char* filepath) {
    SD.begin();
    file = SD.open(filepath);

    frame_count = (file.size() / (MATRIX_WIDTH * MATRIX_HEIGHT)) - 1;
}

FSTempPlayer::~FSTempPlayer() {
    file.close();
}

std::unique_ptr<Color[]> FSTempPlayer::run() {
    if (current_frame >= frame_count) {
        return nullptr;
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