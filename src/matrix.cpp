#include "matrix.h"

SMARTMATRIX_ALLOCATE_BUFFERS(sm_matrix, kMatrixWidth, kMatrixHeight, kRefreshDepth, kDmaBufferRows, kPanelType, kMatrixOptions);
SMARTMATRIX_ALLOCATE_BACKGROUND_LAYER(kBackgroundLayer, kMatrixWidth, kMatrixHeight, COLOR_DEPTH, kBackgroundLayerOptions);


Matrix::Matrix() {
    sm_matrix.addLayer(&kBackgroundLayer);
    sm_matrix.begin();
}

void Matrix::setVisual(Visual* new_visual) {
    visual = new_visual;
}

int Matrix::nextFrame() {
    int return_value = passed_frames;
    passed_frames = 0;
    return return_value;
}

void Matrix::run() {
    if (millis() - last_frame_time < 17) {
        return;
    }
    passed_frames += (millis() - last_frame_time) / 17;
    last_frame_time = millis();
    if (visual) {
        visual->render(kBackgroundLayer);
    }
}