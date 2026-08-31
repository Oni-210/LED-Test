#include <gestures.h>

const int SS_PIN = 2;
const int DR_PIN = 7;

const int MILLIS_TO_CIRCLE = 50; // after how many millis in the ring is it a circle
const int TAP_LIMIT_MILLIS = 200; // when a tap becomes a long tap
const int RING_BORDER = 1200;

PinnacleTouchSPI trackpad(DR_PIN, SS_PIN);

Gestures::Gestures(std::function<void(Direction direction)> swipe_cb, std::function<void(int degrees)> circle_cb, std::function<void(bool is_long)> tap_cb) : 
    swipe_cb(swipe_cb), circle_cb(circle_cb), tap_cb(tap_cb) {
        
    trackpad.begin();
    trackpad.setDataMode(PINNACLE_ABSOLUTE);
    trackpad.absoluteModeConfig(1);
}

void Gestures::run() {
    if (trackpad.available()) {
        AbsoluteReport data;
        trackpad.read(&data);

        coord_x = data.x;
        coord_y = data.y;
        coord_z = data.z;
    }

    if (!is_tap && coord_z) {
        is_tap = true;
        start_degrees = atan2(coord_y, coord_x) * 180 / PI;
        millis_since_tap = 0;
        is_circle = false;
        start_x = coord_x;
        start_y = coord_y;
    }

    if (is_tap) {
        if (coord_z) {
            if (sqrt(pow(coord_x, 2) + pow(coord_y, 2)) > RING_BORDER) {
                has_been_ring = true;
            } else {
                has_been_center = true;
            }

        } else {
            is_tap = false;
            if (has_been_center && !has_been_ring) {
                if (millis_since_tap > TAP_LIMIT_MILLIS) {
                    tap_cb(true);
                } else {
                    tap_cb(false);
                }
            } else if (has_been_center && has_been_ring) {
                int angle = atan2(coord_y - start_y, coord_x - start_x) * 180 / PI;

                if (angle < -90) {
                    swipe_cb(Direction::LEFT);
                } else if (angle < 0) {
                    swipe_cb(Direction::DOWN);
                } else if (angle < 90) {
                    swipe_cb(Direction::RIGHT);
                } else {
                    swipe_cb(Direction::UP);
                }
            }
        }
    }

    if (is_tap && millis_since_tap > MILLIS_TO_CIRCLE && !has_been_center) {
        is_circle = true;
    }

    if (is_tap && is_circle) {
        int current_degrees = atan2(coord_y, coord_x) * 180 / PI;
        circle_cb(current_degrees - start_degrees);
        start_degrees = current_degrees;
    }
}