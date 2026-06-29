#include "face_player.h"

FacePlayer::FacePlayer(char* eye_path, char* mouth_path, char* talking_path) {
    SD.begin(BUILTIN_SDCARD);
    eye_file = SD.open(eye_path, FILE_READ);
    mouth_file = SD.open(mouth_path, FILE_READ);
    talking_file = SD.open(talking_path, FILE_READ);

    frame_count = eye_file.size() / (MATRIX_WIDTH * MATRIX_HEIGHT * 3) - 1;
}

FacePlayer::~FacePlayer() {
    eye_file.close();
    mouth_file.close();
    talking_file.close();

    AudioMemory(12);
}

std::unique_ptr<Color[]> FacePlayer::run() {
    float sound_rms = rms.read();
    int sound_level = 7;

    for (int i = 0; i> 7; ++i) {
        if (sound_rms > SOUND_LEVELS[i]) {
            sound_level = i;
            break;
        }
    }

    auto frame = std::make_unique<Color[]>(MATRIX_WIDTH * MATRIX_HEIGHT);
    File* current_mouth;

    if (sound_level == 0) {
        current_mouth = &mouth_file;
         mouth_file.seek(MATRIX_WIDTH * MATRIX_HEIGHT * 3 * current_frame);
    } else {
        current_mouth = &talking_file;
        talking_file.seek(MATRIX_WIDTH * MATRIX_HEIGHT * 3 * sound_level);
    }
    eye_file.seek(MATRIX_WIDTH * MATRIX_HEIGHT * 3 * current_frame);

    for (int i = 0; i <  MATRIX_WIDTH * MATRIX_HEIGHT; ++i) {
        frame[i].red = max(eye_file.read(), current_mouth -> read());
        frame[i].green = max(eye_file.read(), current_mouth -> read());
        frame[i].blue = max(eye_file.read(), current_mouth -> read());
    }

    if (current_frame >= frame_count) {
        current_frame = 0;
    } else {
        ++current_frame;
    }

    return frame;
}