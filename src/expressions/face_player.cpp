#include "face_player.h"

// GUItool: begin automatically generated code
AudioInputI2S            i2s;           //xy=303,297
AudioAnalyzeRMS          rms;           //xy=523,251
AudioConnection          patchCord1(i2s, 0, rms, 0);
// GUItool: end automatically generated code

FacePlayer::FacePlayer(char* eye_path, char* mouth_path, char* talking_path) {
    SD.begin(BUILTIN_SDCARD);
    eye_file = SD.open(eye_path, FILE_READ);
    mouth_file = SD.open(mouth_path, FILE_READ);
    talking_file = SD.open(talking_path, FILE_READ);

    frame_count = eye_file.size() / (MATRIX_WIDTH * MATRIX_HEIGHT * 3) - 1;
    is_blink = false;
    AudioMemory(12);
}

FacePlayer::FacePlayer(char* eye_path, char* mouth_path, char* talking_path, char* blink_path) {
    SD.begin(BUILTIN_SDCARD);
    eye_file = SD.open(eye_path, FILE_READ);
    mouth_file = SD.open(mouth_path, FILE_READ);
    talking_file = SD.open(talking_path, FILE_READ);
    blink_file = SD.open(blink_path, FILE_READ);
    
    frame_count = eye_file.size() / (MATRIX_WIDTH * MATRIX_HEIGHT * 3) - 1;
    blink_frame_count = blink_file.size() / (MATRIX_WIDTH * MATRIX_HEIGHT * 3) - 1;
    is_blink = true;
    blink_gap = rand() % (BLINK_GAP_MAX - BLINK_GAP_MIN + 1) + BLINK_GAP_MIN;
    AudioMemory(12);
}

FacePlayer::~FacePlayer() {
    eye_file.close();
    mouth_file.close();
    talking_file.close();
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

    for (int i = 0; i <  MATRIX_WIDTH * MATRIX_HEIGHT; ++i) {
        frame[i].red = max(current_eye -> read(), current_mouth -> read());
        frame[i].green = max(current_eye -> read(), current_mouth -> read());
        frame[i].blue = max(current_eye -> read(), current_mouth -> read());
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