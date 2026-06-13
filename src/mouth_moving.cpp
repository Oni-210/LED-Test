#include "mouth_moving.h"

MouthMoving::MouthMoving(Matrix* matrix, char* eye_file_path, char* mouth_file_path) : Visual(matrix) {
    SD.begin();
    if (SD.exists(mouth_file_path)) {
        mouth_file = SD.open(mouth_file_path);
    }
    if (SD.exists(eye_file_path)) {             //TODO: Check for correct file size
        eye_file = SD.open(eye_file_path);
    }
}

void MouthMoving::setOpenness(int openness) {

}