#pragma once
#include <functional>

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

/*
BEATSYNC TYPES:

- low
- mid
- high
- avg_volume
*/

const int NUM_BANDS = 6;

class AudioEngine {
    public:
        AudioEngine(
            std::function<void()> low_cb, 
            std::function<void()> mid_cb, 
            std::function<void()> high_cb);

        void run();
        void setVolume(float volume);

        int sound_level;
        float avg_volume = 0;
        bool is_beatsync = false;
    private:
        float last_fft_bands[NUM_BANDS];
        std::function<void()> low_cb;
        std::function<void()> mid_cb;
        std::function<void()> high_cb;
};