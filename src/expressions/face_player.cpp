#include "face_player.h"

const unsigned int BLINK_GAP_MAX = 3000;
const unsigned int BLINK_GAP_MIN = 500;

FacePlayer::FacePlayer(char* eye_path, char* mouth_path, char* talking_path, int& new_sound_level) {
    SD.begin(BUILTIN_SDCARD);
    eye_file = SD.open(eye_path, FILE_READ);
    mouth_file = SD.open(mouth_path, FILE_READ);
    talking_file = SD.open(talking_path, FILE_READ);

    frame_count = eye_file.size() / (MATRIX_WIDTH * MATRIX_HEIGHT * 3) - 1;
}

FacePlayer::FacePlayer(char* eye_path, char* mouth_path, char* talking_path, char* blink_path, int& new_sound_level) {
    SD.begin(BUILTIN_SDCARD);
    eye_file = SD.open(eye_path, FILE_READ);
    mouth_file = SD.open(mouth_path, FILE_READ);
    talking_file = SD.open(talking_path, FILE_READ);
    blink_file = SD.open(blink_path, FILE_READ);

    frame_count = eye_file.size() / (MATRIX_WIDTH * MATRIX_HEIGHT * 3) - 1;
    blink_frame_count = blink_file.size() / (MATRIX_WIDTH * MATRIX_HEIGHT * 3) - 1;
    blink_gap = rand() % (BLINK_GAP_MAX - BLINK_GAP_MIN + 1) + BLINK_GAP_MIN;
}

FacePlayer::~FacePlayer() {
    eye_file.close();
    mouth_file.close();
    talking_file.close();

    if (is_blink) {
        blink_file.close();
    }
}

std::unique_ptr<Color[]> FacePlayer::run() {
    auto frame = std::make_unique<Color[]>(MATRIX_WIDTH * MATRIX_HEIGHT);
    File* current_mouth;

    if (sound_level == 0) {
        current_mouth = &mouth_file;
         mouth_file.seek(MATRIX_WIDTH * MATRIX_HEIGHT * 3 * current_frame);
    } else {
        current_mouth = &talking_file;
        talking_file.seek(MATRIX_WIDTH * MATRIX_HEIGHT * 3 * *sound_level);
    }
    
    if (is_blink && since_last_blink >= blink_gap) {
        blink_gap = rand() % (BLINK_GAP_MAX - BLINK_GAP_MIN + 1) + BLINK_GAP_MIN;
        currently_blinking = true;
        current_blink_frame = 0;
    }
    
    File* current_eye;
    
    if (currently_blinking) {
        current_eye = &blink_file;
        blink_file.seek(current_blink_frame);
    } else {
        current_eye = &eye_file;
        eye_file.seek(current_frame);
    } 
    
    eye_file.seek(MATRIX_WIDTH * MATRIX_HEIGHT * 3 * current_frame);

    for (int pixel = 0; pixel <  MATRIX_WIDTH * MATRIX_HEIGHT; ++pixel) {
        frame[pixel].red = max(current_eye -> read(), current_mouth -> read());
        frame[pixel].green = max(current_eye -> read(), current_mouth -> read());
        frame[pixel].blue = max(current_eye -> read(), current_mouth -> read());
    }

    if (current_frame >= frame_count) {
        current_frame = 0;
    } else {
        ++current_frame;
    }
    
    if (currently_blinking) {
        if (current_blink_frame >= blink_frame_count) {
            currently_blinking = false;
        } else {
            ++current_blink_frame;
        }  
    }

    return frame;
}