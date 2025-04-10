#pragma once

#include <raylib.h>

namespace game {

class paddle {
public:
    paddle(Rectangle rect, float speed) noexcept;

    void draw();
    void update();

    Rectangle get_rect() const noexcept;
    float x() const noexcept;
    float y() const noexcept;
    float width() const noexcept;
    float height() const noexcept;


protected:
    Rectangle m_rect{};
    float m_speed;

    void LimitMovement();
};

class cpu_paddle : public paddle {
public:
    using paddle::paddle;

    void cpu_update(float ball_y);
};

} // namespace game