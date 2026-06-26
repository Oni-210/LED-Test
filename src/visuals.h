#pragma once
#include <Arduino.h>
#include <memory>

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
    BLINK,
	SOCIAL_BATTERY,
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
};

class VisualTools {
    public:
        static Visual* getExpression(Expression expression);
        static Visual* getExpression(TempExpression expression);
};