#pragma once

#include <raylib.h>
#include <cstdint>

namespace game {

class ball {
public:
    ball(float radius, Vector2 position, Vector2 velocity) noexcept;

    void draw();
    void update();
    void reset();

    float left_bound() const noexcept;
    float right_bound() const noexcept;
    float upper_bound() const noexcept;
    float lower_bound() const noexcept;

    Vector2 get_position() const noexcept;
    Vector2 get_velocity() const noexcept;
    float get_radius() const noexcept;

    void set_velocity_x(float other) noexcept;
    void set_velocity_y(float other) noexcept;

private:
    float m_radius{};
    Vector2 m_position{};
    Vector2 m_velocity{};
};

} // namespace game