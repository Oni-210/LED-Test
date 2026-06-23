#include "visual.h"
#include "SPI.h"
#include "SD.h"

class MouthMoving : public Visual {
    public:
        MouthMoving(Matrix* matrix, char* eye_file_path, char* mouth_file_path) : Visual(matrix) {}

        void run() override;
        int openness = 1; // 0 - 7 

    private:
        File eye_file;  // a 128x16 static image for the eyes
        File mouth_file;  // 8 128x16 images with the mouth opening frame by frame
};

enum class MouthMovingError {
    None,
    EyeFileInvalid,
    MouthFileInvalid,
    UnknownError
};