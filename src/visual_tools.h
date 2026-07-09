#pragma once
#include "visuals.h"
#include "expressions/fs_player.h"
#include "expressions/face_player.h"
#include "expressions/fs_temp_player.h"
#include "expressions/face_temp_player.h"
#include <memory>

class VisualTools {
    public:
        VisualTools(int& sound_level) : sound_level(sound_level) {};
        std::unique_ptr<Visual> getExpression(Expression expression);
        std::unique_ptr<Visual> getExpression(TempExpression expression);
        Palette getPalette(Expression expression);
        Palette getPalette(TempExpression expression);

        struct {
            unsigned int battery_level = 5; // 0 - 5
        } params;

    private:
        int& sound_level;
    };