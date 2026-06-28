#pragma once
#include "visuals.h"
#include "expressions/fc_player.h"
#include "expressions/face_player.h"
#include <memory>

class VisualTools {
    public:
        static std::unique_ptr<Visual> getExpression(Expression expression);
        static std::unique_ptr<Visual> getExpression(TempExpression expression);
};