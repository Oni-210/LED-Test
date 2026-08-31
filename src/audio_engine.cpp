#include "audio_engine.h"

// GUItool: begin automatically generated code
AudioInputI2S            i2s;           //xy=387,195
AudioEffectBitcrusher    bitcrusher;    //xy=612,229
AudioAnalyzePeak         peak;          //xy=614,155
AudioAnalyzeFFT256       fft256;       //xy=618,332
AudioAmplifier           amp;           //xy=838,262
AudioOutputI2S2          i2s2;         //xy=1064,305
AudioConnection          patchCord1(i2s, 0, bitcrusher, 0);
AudioConnection          patchCord2(i2s, 0, peak, 0);
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
//NUM_BANDS defined in audio_engine.h
const int BAND_LIMITS[NUM_BANDS + 1] = {
    0,
    64,
    100,
    128,
    150,
    270,
    256,
};
const int LOW_BAND_WEIGTHS[NUM_BANDS] = {
    0.5,
    0.7,
    0.2,
    0.0,
    0.0,
    0.0,
};
const int MID_BAND_WEIGTHS[NUM_BANDS] = {
    0.0,
    0.2,
    0.5,
    0.5,
    0.2,
    0.0,
};
const int HIGH_BAND_WEIGTHS[NUM_BANDS] = {
    0.0,
    0.0,
    0.0,
    0.2,
    0.7,
    0.5,
};

AudioEngine::AudioEngine(std::function<void()> low_cb, std::function<void()> mid_cb, std::function<void()> high_cb) 
    : low_cb(low_cb), mid_cb(mid_cb), high_cb(high_cb) {
    AudioMemory(12);
    bitcrusher.sampleRate(SAMPLE_RATE);
    bitcrusher.bits(BITDEPTH);
    amp.gain(DEFAULT_VOLUME);
    fft256.averageTogether(AVERAGE_TOGETHER);
}

void AudioEngine::run() {
    if (!fft256.available()) return;

    float current_peak = peak.read();
    for (int level = 0; level < sizeof(SOUND_LEVELS); ++level) {
        if (current_peak < SOUND_LEVELS[level]) {
            sound_level = level;
        }
    }
    sound_level = sizeof(SOUND_LEVELS);

    if (!is_beatsync) return;

    float fft_bands[NUM_BANDS];
    for (int band = 0; band < NUM_BANDS; ++band) {
        fft_bands[band] = fft256.read(BAND_LIMITS[band], BAND_LIMITS[band + 1]);
    }

    float fft_deltas[NUM_BANDS];
    for (int band = 0; band < NUM_BANDS; ++band) {
        fft_deltas[band] = fft_bands[band] - last_fft_bands[band];
    }

    float low_beat_prob = 0;
    for (int band; band < NUM_BANDS; ++band) {
        low_beat_prob += fft_deltas[band] * LOW_BAND_WEIGTHS[band];
    }
    if (low_beat_prob >= 1) low_cb();

    float mid_beat_prob = 0;
    for (int band; band < NUM_BANDS; ++band) {
        mid_beat_prob += fft_deltas[band] * MID_BAND_WEIGTHS[band];
    }
    if (mid_beat_prob >= 1) high_cb();

    float high_beat_prob = 0;
    for (int band; band < NUM_BANDS; ++band) {
        high_beat_prob += fft_deltas[band] * HIGH_BAND_WEIGTHS[band];
    }
    if (high_beat_prob >= 1) high_cb();

    for (float band_value : fft_bands) {
        avg_volume += band_value;
    }
    avg_volume /= NUM_BANDS;

    for (int i = 0; i < NUM_BANDS; ++i) {
        last_fft_bands[i] = fft_bands[i];
    }
}

void AudioEngine::setVolume(float volume) {
    amp.gain(volume);
}