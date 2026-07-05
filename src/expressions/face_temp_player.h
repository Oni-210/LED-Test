#pragma once
#include "visuals.h"
#include <memory>
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
extern AudioInputI2S            i2s;           //xy=303,297
extern AudioAnalyzeRMS          rms;           //xy=523,251
extern AudioConnection          patchCord1;
// GUItool: end automatically generated code

class FaceTempPlayer : public Visual {
    public:
        FaceTempPlayer(char * eye_path, char* mouth_path, char* talking_path);
        ~FaceTempPlayer();
        std::unique_ptr<Color[]> run() override;

    private:
        File eye_file;
        File mouth_file;
        File talking_file;
        unsigned int current_frame = 0;
        unsigned int frame_count;
};