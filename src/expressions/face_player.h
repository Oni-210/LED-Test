#pragma once
#include "visuals.h"
#include <SPI.h>
#include <SD.h>

class FacePlayer : public Visual {
    public:
        FacePlayer(char* eye_path, char* mouth_path, char* talking_path, int& new_sound_level);
        FacePlayer(char* eye_path, char* mouth_path, char* talking_path, char* blink_path, int& new_sound_level);
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
        int* sound_level;
};