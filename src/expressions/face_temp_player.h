#pragma once
#include "visuals.h"
#include <memory>
#include <SPI.h>
#include <SD.h>

class FaceTempPlayer : public Visual {
    public:
        FaceTempPlayer(char * eye_path, char* mouth_path, char* talking_path, int& new_sound_level) : sound_level(&new_sound_level) {};
        ~FaceTempPlayer();
        std::unique_ptr<Color[]> run() override;

    private:
        File eye_file;
        File mouth_file;
        File talking_file;
        unsigned int current_frame = 0;
        unsigned int frame_count;
        int* sound_level;
};