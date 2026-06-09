#pragma once
#include <MatrixHardware_Teensy4_ShieldV5.h>
#include <SmartMatrix.h>

class Visual {
    public:
        virtual void render(SMLayerBackground<rgb24, 0U>& canvas) =0;   // once at 60fps per frame
};