#include "file_player.h"

FilePlayer::FilePlayer(char* new_filepath) {
    filepath = new_filepath;
    SD.begin(BUILTIN_SDCARD);
    file = SD.open(filepath);
}

FilePlayer::~FilePlayer() {
    file.close();
}

void FilePlayer::render(SMLayerBackground<rgb24, 0U>& canvas) {
    if (!file) {
        return;
    }
    file.seek(current_frame * canvas.localWidth() * canvas.localHeight() * 3);
}