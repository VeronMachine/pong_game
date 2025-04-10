#include <raylib.h>
#include <raymath.h>
#include "game/ball.hpp"
#include "game/constants.hpp"

namespace game {

ball::ball(float radius, Vector2 position, Vector2 velocity) noexcept
    : m_radius{ radius }
    , m_position{ position }
    , m_velocity{ velocity }
{}

void ball::draw() {
    DrawCircleV(m_position, m_radius, Yellow);
}

void ball::update() {

    m_position = Vector2Add(m_position, m_velocity);

    if (lower_bound() >= GetScreenHeight() || upper_bound() <= 0) {
        m_velocity.y *= -1;
    }

}

void ball::reset() {
   m_position.x = static_cast<float>(GetScreenWidth() / 2);
   m_position.y = static_cast<float>(GetScreenHeight() / 2);

   constexpr float speed_choices[2]{ -1.0f, 1.0f };
   m_velocity.x *= speed_choices[GetRandomValue(0, 1)];
   m_velocity.y *= speed_choices[GetRandomValue(0, 1)];
}

float ball::left_bound() const noexcept {
    return m_position.x - m_radius;
}

float ball::right_bound() const noexcept {
    return m_position.x + m_radius;
}

float ball::upper_bound() const noexcept {
    return m_position.y - m_radius;
}

float ball::lower_bound() const noexcept {
    return m_position.y + m_radius;
}

Vector2 ball::get_position() const noexcept {
    return m_position;
}

Vector2 ball::get_velocity() const noexcept {
    return m_velocity;
}

float ball::get_radius() const noexcept {
    return m_radius;
}

void ball::set_velocity_x(float other) noexcept {
    m_velocity.x = other;
}

void ball::set_velocity_y(float other) noexcept {
    m_velocity.y = other;
}

} // namespace game