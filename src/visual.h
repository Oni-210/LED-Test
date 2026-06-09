#pragma once

#include "matrix.h"

class Visual {
    public:
        Visual(Matrix* matrix) : matrix(matrix) {};
        virtual void run() =0;
    private:
        Matrix* matrix;
};