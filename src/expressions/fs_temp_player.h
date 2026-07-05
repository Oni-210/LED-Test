#pragma once
#include "visuals.h"
#include <SPI.h>
#include <SD.h>
#include <memory>

class FSTempPlayer : public Visual{
    public:
        FSTempPlayer(char* filepath);
        ~FSTempPlayer();
        std::unique_ptr<Color[]> run() override;

    private:
        File file;
        unsigned int current_frame = 0;
        unsigned int frame_count;
};