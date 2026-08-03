#pragma once
#include <math.h>
#include <CirquePinnacle.h>
#include <functional>

enum class Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Gestures {
    public:
        Gestures(
            std::function<void(Direction direction)> swipe_cb, 
            std::function<void(int degrees)> circle_cb, 
            std::function<void(bool is_long)> tap_cb) : 
            swipe_cb(swipe_cb), circle_cb(circle_cb), tap_cb(tap_cb) {};

        void run();

    private:
        std::function<void(Direction direction)> swipe_cb;
        std::function<void(int degrees)> circle_cb;
        std::function<void(bool is_long)> tap_cb;
        
        int coord_x;
        int coord_y;
        int coord_z;

        elapsedMillis millis_since_tap;
        bool is_tap = false;
        bool is_circle;
        int start_degrees;
        bool has_been_center;
        bool has_been_ring;
        int start_x;
        int start_y;
};