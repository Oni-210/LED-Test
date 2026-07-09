#pragma once

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

class AudioEngine {
    public:
        AudioEngine();
        void run();
        int getSoundLevel();
        void setVolume(float volume);

        int sound_level;
};