#pragma once

#include <MatrixHardware_Teensy4_ShieldV5.h>
#include <SmartMatrix.h>

// Matrix configuration
#define COLOR_DEPTH 24
const uint16_t kMatrixWidth = 128;
const uint16_t kMatrixHeight = 32;
const uint8_t kRefreshDepth = 36;
const uint8_t kDmaBufferRows = 4;
const uint8_t kPanelType = SM_PANELTYPE_HUB75_32ROW_MOD16SCAN;
const uint32_t kMatrixOptions = (SM_HUB75_OPTIONS_NONE);
const uint8_t kBackgroundLayerOptions = (SM_BACKGROUND_OPTIONS_NONE);
SMARTMATRIX_ALLOCATE_BUFFERS(matrix, kMatrixWidth, kMatrixHeight, kRefreshDepth, kDmaBufferRows, kPanelType, kMatrixOptions);
SMARTMATRIX_ALLOCATE_BACKGROUND_LAYER(backgroundLayer, kMatrixWidth, kMatrixHeight, COLOR_DEPTH, kBackgroundLayerOptions);

class Matrix {
    public:
        Matrix();
        int nextFrame();    // return how many frames have passed since last call, 0 if none, 1 if next frame can be buffered
        void bufferFrame(rgb24* frame);
        void bufferPaletteFrame(uint8_t* frame);
        void setPalette(uint8_t* new_palette);
        void run();

    private:
        unsigned long last_frame_time = 0;
        int frames_since_last_call = 0;
        rgb24 palette[256];
};