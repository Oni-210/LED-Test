#pragma once
#include "visual.h"

#include <SPI.h>
#include <SD.h>

class FilePlayer : public Visual {
    public:
        FilePlayer(char* filepath);
        ~FilePlayer();
        void render(SMLayerBackground<rgb24, 0U>& canvas) override;
    
    private:
        char* filepath;
        File file;
        int current_frame = 0;
};