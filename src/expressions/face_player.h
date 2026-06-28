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

// GUItool: begin automatically generated code
AudioInputI2S            i2s;           //xy=303,297
AudioAnalyzeRMS          rms;           //xy=523,251
AudioConnection          patchCord1(i2s, 0, rms, 0);
// GUItool: end automatically generated code

class FacePlayer : public Visual {
    public:
        FacePlayer(char* eye_path, char* mouth_path, char* talking_path);
        ~FacePlayer();
        std::unique_ptr<Color[]> run() override;
    private:
        File eye_file;
        File mouth_file;
        File talking_file;
        int current_frame = 0;
};