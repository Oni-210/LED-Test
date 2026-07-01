#pragma once
#include "visuals.h"
#include <SPI.h>
#include <SD.h>
#include <Audio.h>
#include <Wire.h>
#include <SerialFlash.h>

const float SOUND_LEVELS[7] = {
    0.1,
    0.2,
    0.3,
    0.4,
    0.5,
    0.6,
    0.7
};

const unsigned int BLINK_GAP_MAX = 3000;
const unsigned int BLINK_GAP_MIN = 500;

// GUItool: begin automatically generated code
extern AudioInputI2S            i2s;           //xy=303,297
extern AudioAnalyzeRMS          rms;           //xy=523,251
extern AudioConnection          patchCord1;
// GUItool: end automatically generated code

class FacePlayer : public Visual {
    public:
        FacePlayer(char* eye_path, char* mouth_path, char* talking_path);
        FacePlayer(char* eye_path, char* mouth_path, char* talking_path, char* blink_path);
        ~FacePlayer();
        std::unique_ptr<Color[]> run() override;
    private:
        File eye_file;
        File mouth_file;
        File talking_file;
        File blink_file;
        bool is_blink;
        bool currently_blinking = false;
        unsigned int current_blink_frame = 0;
        unsigned int blink_frame_count;
        elapsedMillis since_last_blink = 0;
        unsigned int blink_gap;
        unsigned int current_frame = 0;
        unsigned int frame_count;
        
};