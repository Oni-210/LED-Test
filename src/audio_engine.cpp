#include "audio_engine.h"

// GUItool: begin automatically generated code
AudioInputI2S            audio_i2s1_in;           //xy=310,298
AudioAnalyzeRMS          audio_rms_out;           //xy=523,251
AudioEffectBitcrusher    audio_bitcrusher;    //xy=550,343
AudioSynthWaveformDc     audio_dc_volume;            //xy=573,464
AudioEffectMultiply      audio_multiply;      //xy=781,373
AudioOutputI2S2          audio_i2s2_out;         //xy=1037,376
AudioConnection          patchCord1(audio_i2s1_in, 0, audio_rms_out, 0);
AudioConnection          patchCord2(audio_i2s1_in, 0, audio_bitcrusher, 0);
AudioConnection          patchCord3(audio_bitcrusher, 0, audio_multiply, 0);
AudioConnection          patchCord4(audio_dc_volume, 0, audio_multiply, 1);
AudioConnection          patchCord5(audio_multiply, 0, audio_i2s2_out, 0);
// GUItool: end automatically generated code

const float SAMPLE_RATE = 0.3;
const int BITDEPTH = 8;
const float DEFAULT_VOLUME = 0.7;
const float SOUND_LEVELS[7] = {
    0.1,
    0.2,
    0.3,
    0.4,
    0.5,
    0.6,
    0.7
};

AudioEngine::AudioEngine() {
    audio_bitcrusher.sampleRate(SAMPLE_RATE);
    audio_bitcrusher.bits(BITDEPTH);
    audio_dc_volume.amplitude(DEFAULT_VOLUME);
    AudioMemory(12);
}

void AudioEngine::run() {
    sound_level = getSoundLevel();
}

int AudioEngine::getSoundLevel() {
    float current_rms = audio_rms_out.read();

    for (int i = 0; i < sizeof(SOUND_LEVELS); ++i) {
        if (current_rms < SOUND_LEVELS[i]) {
            return i;
        }
    }
    return sizeof(SOUND_LEVELS);
}

void AudioEngine::setVolume(float volume) {
    audio_dc_volume.amplitude(volume);
}