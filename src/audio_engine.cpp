#include "audio_engine.h"

// GUItool: begin automatically generated code
AudioInputI2S            i2s;           //xy=387,195
AudioEffectBitcrusher    bitcrusher;    //xy=612,229
AudioAnalyzeRMS          rms;           //xy=614,155
AudioAnalyzeFFT256       fft256;       //xy=618,332
AudioAmplifier           amp;           //xy=838,262
AudioOutputI2S2          i2s2;         //xy=1064,305
AudioConnection          patchCord1(i2s, 0, bitcrusher, 0);
AudioConnection          patchCord2(i2s, 0, rms, 0);
AudioConnection          patchCord3(i2s, 1, fft256, 0);
AudioConnection          patchCord4(bitcrusher, amp);
AudioConnection          patchCord5(amp, 0, i2s2, 0);
// GUItool: end automatically generated code


const float SAMPLE_RATE = 0.3;
const int BITDEPTH = 8;
const float DEFAULT_VOLUME = 1.0;
const float SOUND_LEVELS[7] = {
    0.1,
    0.2,
    0.3,
    0.4,
    0.5,
    0.6,
    0.7
};

const int AVERAGE_TOGETHER = 24;
const int NUM_BANDS = 6;
const int BAND_LIMITS[NUM_BANDS + 1] = {
    0,
    64,
    100,
    128,
    150,
    270,
    256,
};

AudioEngine::AudioEngine() {
    AudioMemory(12);
    bitcrusher.sampleRate(SAMPLE_RATE);
    bitcrusher.bits(BITDEPTH);
    amp.gain(DEFAULT_VOLUME);
    fft256.averageTogether(AVERAGE_TOGETHER);
}

void AudioEngine::run() {
    sound_level = getSoundLevel();

    if (fft256.available()) {
        for (int band = 0; band < NUM_BANDS; ++band) {
            fft_bands[band] = fft256.read(BAND_LIMITS[band], BAND_LIMITS[band + 1]);
        }
    }

    float avg_volume = 0;
    for (float band_value : fft_bands) {
        avg_volume += band_value;
    }
    avg_volume /= NUM_BANDS;
}

int AudioEngine::getSoundLevel() {
    if (rms.available()) {
        current_rms = rms.read();
    }

    for (int level = 0; level < sizeof(SOUND_LEVELS); ++level) {
        if (current_rms < SOUND_LEVELS[level]) {
            return level;
        }
    }
    return sizeof(SOUND_LEVELS);
}

void AudioEngine::setVolume(float volume) {
    amp.gain(volume);
}