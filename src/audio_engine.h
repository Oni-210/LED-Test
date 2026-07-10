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

extern const int NUM_BANDS;

class AudioEngine {
    public:
        AudioEngine();
        void run();
        int getSoundLevel();
        void setVolume(float volume);
        void setBeatsyncCB(std::function<void(bool is_low_beat, bool is_mid_beat, bool is_high_beat, int avg_volume)>);

        int sound_level;

    private:
        float current_rms;
        float fft_bands[NUM_BANDS];
};