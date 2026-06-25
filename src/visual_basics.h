#include <Arduino.h>
##include <Enum.h>

struct Color {
    byte red;
    byte green;
    byte blue;
};

enum class Expressions {
	neutral,
    happy,
    sad,
    annoyed,
    insult,
    error,
    dead,
    confused,
    beatsync,
    shy
};

enum class TempExpression {
	wink,
    blink,
	social_battery
}