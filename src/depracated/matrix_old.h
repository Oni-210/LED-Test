#pragma once

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

        MatrixError displayAnimation(const char * filepath);
        MatrixError swapPalette(const char * filepath);
        void run();
};

enum class MatrixError {
    None,
    WrongDimensions,
    InvalidPalette,
    InvalidFile,
    UnknownError
};