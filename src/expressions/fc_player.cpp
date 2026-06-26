#include "fc_player.h"

FCPlayer::FCPlayer(char* filepath) {
    SD.begin(BUILTIN_SDCARD);
    file = SD.open(filepath, FILE_READ);

    frame_count = (file.size() / (128 * 32)) - 1;
}

std::unique_ptr<Color[]> FCPlayer::run() {
    if (current_frame >= frame_count) {
        current_frame = 0;
    }

    auto frame = std::make_unique<Color[]>(128 * 32);
    file.seek(current_frame * 128 * 32 * 3);
    for (int i; i < 128 * 32; ++i) {
        frame[i].red = file.read();
        frame[i].green = file.read();
        frame[i].blue = file.read();
    };

    ++current_frame;
    return frame;
}