#pragma once

#include <cstdint>

namespace game {

class Ball {
public:
    void Draw();
    void Update();
    void reset();

    // float get_x();
    // float get_y();
    // int32_t get_speed_x();
    // int32_t get_speed_y();
    // int32_t get_radius();

// private:
    float x{};
    float y{};
    int32_t speed_x{};
    int32_t speed_y{};
    int32_t radius{};
};

} // namespace game