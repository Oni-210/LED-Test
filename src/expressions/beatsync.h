#include "visuals.h"
#include <SPI.h>
#include <SD.h>

class Beatsync : public Visual {
    public:
        Beatsync(float& avg_volume);
        ~Beatsync();
        std::unique_ptr<Color[]> run() override;
        void lowCB();
        void midCB();
        void highCB();
        
    private:
        int current_color = 0;
        float current_color_fraction = 0; // How much of the last color is still shining trough
        float flash_brightness = 0;
        int eye_shift = 0;
        int mouth_size = 0;
        float& avg_volume;

        File eye_file;
        File mouth_file;
};