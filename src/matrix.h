#pragma once

#include "visual.h"

#include <SPI.h>
#include <SD.h>

#include <MatrixHardware_Teensy4_ShieldV5.h>
#include <SmartMatrix.h>
#define COLOR_DEPTH 24
const uint16_t kMatrixWidth = 128;
const uint16_t kMatrixHeight = 32;
const uint8_t kRefreshDepth = 36;
const uint8_t kDmaBufferRows = 4;
const uint8_t kPanelType = SM_PANELTYPE_HUB75_32ROW_MOD16SCAN;
const uint32_t kMatrixOptions = (SM_HUB75_OPTIONS_NONE);
const uint8_t kBackgroundLayerOptions = (SM_BACKGROUND_OPTIONS_NONE);
const uint8_t kScrollingLayerOptions = (SM_SCROLLING_OPTIONS_NONE);
const uint8_t kIndexedLayerOptions = (SM_INDEXED_OPTIONS_NONE);


class Matrix {
    public:
        Matrix();
        ~Matrix();

        void setVisual(Visual* visual);
        int nextFrame();   // returns how many frames have passed since last call, 1 if next frame can be rendered, 0 if not yet
        void run();
    
    private:
        int passed_frames = 0;
        unsigned long last_frame_time = 0;
        Visual* visual = nullptr;
};