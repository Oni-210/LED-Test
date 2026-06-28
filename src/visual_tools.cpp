#include "visual_tools.h"

std::unique_ptr<Visual> VisualTools::getExpression(Expression expression) {
    switch (expression) {
        case Expression::NEUTRAL:
            return std::make_unique<FacePlayer>("neutral/eyes.bin", "neutral/mouth.bin", "default/talking.bin");
        case Expression::HAPPY:
            return std::make_unique<FacePlayer>("happy/eyes.bin", "happy/mouth.bin", "default/talking.bin");
        case Expression::SAD:
            return std::make_unique<FacePlayer>("sad/eyes.bin", "sad/mouth.bin", "default/talking.bin");
        case Expression::ANNOYED:
            return std::make_unique<FacePlayer>("annoyed/eyes.bin", "annoyed/mouth.bin", "default/talking.bin");
        case Expression::INSULT:
            return std::make_unique<FCPlayer>("fc/insult.bin");
        case Expression::ERROR:
            return std::make_unique<FCPlayer>("fc/error.bin");
        case Expression::DEAD:
            return std::make_unique<FacePlayer>("dead/eyes.bin", "dead/mouth.bin", "default/talking.bin");
        case Expression::CONFUSED:
            return std::make_unique<FacePlayer>("confused/eyes.bin", "confused/mouth.bin", "default/talking.bin");
        case Expression::SHY:
            return std::make_unique<FacePlayer>("shy/eyes.bin", "shy/mouth.bin", "default/talking.bin");
        default:
            return nullptr;
    }
}