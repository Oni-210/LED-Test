#pragma once
#include "visuals.h"

#include <SPI.h>
#include <SD.h>

class FCPlayer: Visual {
    public:
        FCPlayer(char* filepath);
        std::unique_ptr<Color[]> run() override;
    private:
        File file;
        int current_frame = 0;
        int frame_count;
};