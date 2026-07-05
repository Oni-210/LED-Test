#pragma once
#include <Arduino.h>
#include <memory>

const int MATRIX_WIDTH = 128;
const int MATRIX_HEIGHT = 32;

struct Color {
    byte red;
    byte green;
    byte blue;
};

enum class Expression {
	NEUTRAL,
    HAPPY,
    SAD,
    ANNOYED,
    INSULT,     // "Fuck off"
    ERROR,
    DEAD,
    CONFUSED,
    BEATSYNC,
    SHY
};

enum class TempExpression {
	WINK,
	BATTERY,
    NONE
};

enum class Palette {
    RED,
    PURPLE,
    BLUE,
    GREEN,
    BEATSYNC
};

class Visual {
    public:
        virtual std::unique_ptr<Color[]> run() =0;
        virtual ~Visual() = default;
};