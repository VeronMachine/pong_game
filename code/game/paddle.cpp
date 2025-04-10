#include "game/paddle.hpp"

namespace game {

paddle::paddle(Rectangle rect, float speed) noexcept
    : m_rect{ rect }
    , m_speed{ speed }
{}

void paddle::LimitMovement() {
    if (m_rect.y <= 0) {
        m_rect.y = 0;
    } else if (m_rect.y + m_rect.height >= GetScreenHeight()) {
        m_rect.y = GetScreenHeight() - m_rect.height;
    }
}

void paddle::draw() {
    DrawRectangleRounded(m_rect, 0.8, 0, WHITE);
}

void paddle::update() {
    if (IsKeyDown(KEY_UP)) {
        m_rect.y -= m_speed;
    }
    if (IsKeyDown(KEY_DOWN)) {
        m_rect.y += m_speed;
    }
    LimitMovement();
}

Rectangle paddle::get_rect() const noexcept {
    return m_rect;
}

float paddle::x() const noexcept {
    return m_rect.x;
}

float paddle::y() const noexcept {
    return m_rect.y;
}

float paddle::width() const noexcept {
    return m_rect.width;
}

float paddle::height() const noexcept {
    return m_rect.height;
}

void cpu_paddle::cpu_update(float ball_y) {
    if (m_rect.y + m_rect.height / 2 > ball_y) {
        m_rect.y -= m_speed;
    } else {
        m_rect.y += m_speed;
    }
    LimitMovement();
}

} // namespace game