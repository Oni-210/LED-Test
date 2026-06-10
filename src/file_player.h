#include "visual.h"
#include <SPI.h>
#include <SD.h>

class FilePlayer : public Visual {
    public:
        FilePlayer(Matrix* matrix) : Visual(matrix) {}
        ~FilePlayer() {}
        void run() override;
        FileError loadFile(const char* filename);
        bool isPalette = false;

    private:
        Matrix* matrix;
        File file;

};

enum class FileError {
    None,
    FileNotFound,
    InvalidFormat,
    UnknownError
};