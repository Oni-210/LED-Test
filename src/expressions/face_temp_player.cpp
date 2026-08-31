#include "face_temp_player.h"

FaceTempPlayer::FaceTempPlayer(char* eye_path, char* mouth_path, char* talking_path, int& new_sound_level) 
    : sound_level(&new_sound_level) {
    SD.begin(BUILTIN_SDCARD);
    eye_file = SD.open(eye_path, FILE_READ);
    mouth_file = SD.open(mouth_path, FILE_READ);
    talking_file = SD.open(talking_path, FILE_READ);

    frame_count = eye_file.size() / (MATRIX_WIDTH * MATRIX_HEIGHT * 3) - 1;
}

FaceTempPlayer::~FaceTempPlayer() {
    eye_file.close();
    mouth_file.close();
    talking_file.close();
}

std::unique_ptr<Color[]> FaceTempPlayer::run() {
    auto frame = std::make_unique<Color[]>(MATRIX_WIDTH * MATRIX_HEIGHT);
    File* current_mouth;

    if (sound_level == 0) {
        current_mouth = &mouth_file;
         mouth_file.seek(MATRIX_WIDTH * MATRIX_HEIGHT * 3 * current_frame);
    } else {
        current_mouth = &talking_file;
        talking_file.seek(MATRIX_WIDTH * MATRIX_HEIGHT * 3 * *sound_level);
    }

    eye_file.seek(MATRIX_WIDTH * MATRIX_HEIGHT * 3 * current_frame);

    for (int pixel = 0; pixel <  MATRIX_WIDTH * MATRIX_HEIGHT; ++pixel) {
        frame[pixel].red = max(eye_file.read(), current_mouth -> read());
        frame[pixel].green = max(eye_file.read(), current_mouth -> read());
        frame[pixel].blue = max(eye_file.read(), current_mouth -> read());
    }

    if (current_frame >= frame_count) {
        return nullptr;
    }
    ++current_frame;

    return frame;
}