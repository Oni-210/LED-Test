#include "matrix_old.h"

SMARTMATRIX_ALLOCATE_BUFFERS(matrix, kMatrixWidth, kMatrixHeight, kRefreshDepth, kDmaBufferRows, kPanelType, kMatrixOptions);
SMARTMATRIX_ALLOCATE_BACKGROUND_LAYER(backgroundLayer, kMatrixWidth, kMatrixHeight, COLOR_DEPTH, kBackgroundLayerOptions);

class Matrix {
    public:
        Matrix() {
            SD.begin();
            matrix.addLayer(&backgroundLayer);
            matrix.begin();
        }

        ~Matrix() {
           animation.close();
        }

        MatrixError displayAnimation(const char * filepath) {
            if (!SD.exists(filepath)) {
                return MatrixError::InvalidFile;
            }
            File file = SD.open(filepath);
            if (!file) {
                return MatrixError::InvalidFile;
            }
            animation = file;
            currentFrame = 0;
            return MatrixError::None;
        }

        MatrixError swapPalette(const char * filepath) {
            if (!SD.exists(filepath)) {
                return MatrixError::InvalidFile;
            }
            File file = SD.open(filepath);
            if (!file) {
                return MatrixError::InvalidFile;
            }
            if (file.size() == 0 || file.size() % 3 != 0) {
                file.close();
                return MatrixError::WrongDimensions;
            }
            for (int i = 0; i < 256; i++) {
                if (file.available() < 3) {
                    palette[i] = rgb24(0, 0, 0);
                }
                uint8_t r = file.read();
                uint8_t g = file.read();
                uint8_t b = file.read();
                palette[i] = rgb24(r, g, b);
            }
            file.close();
            return MatrixError::None;
        }

        void run() {
            if (lastFrameTime + 33 > millis()) {
                return;
            }
            lastFrameTime = millis();

            backgroundLayer.swapBuffers(false);

            if (!animation) {
                return;
            }

            if (animation.available() < kMatrixWidth * kMatrixHeight) {
                animation.seek(0);
                currentFrame = 0;
            }

            for (int y = 0; y < kMatrixHeight; y++) {
                for (int x = 0; x < kMatrixWidth; x++) {
                    uint8_t colorIndex = animation.read();
                    backgroundLayer.drawPixel(x, y, palette[colorIndex]);
                }
            }
            
            currentFrame++;
        }
        
    private:
        rgb24 palette[256];
        File animation;
        int currentFrame;
        int lastFrameTime;
};