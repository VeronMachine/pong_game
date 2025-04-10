#include <raylib.h>
#include "game/paddle.hpp"

namespace game {

void paddle::LimitMovement() {
    if (y <= 0) {
        y = 0;
    }
    if (y + height >= GetScreenHeight()) {
        y = GetScreenHeight() - height;
    }
}

void paddle::draw() {
    DrawRectangleRounded(Rectangle{ x, y, width, height }, 0.8, 0, WHITE);
}

void paddle::update() {
    if (IsKeyDown(KEY_UP)) {
        y = y - speed;
    }
    if (IsKeyDown(KEY_DOWN)) {
        y = y + speed;
    }
    LimitMovement();
}

void cpu_paddle::Update(int ball_y) {
    if (y + height / 2 > ball_y) {
        y = y - speed;
    }
    if (y + height / 2 <= ball_y) {
        y = y + speed;
    }
    LimitMovement();
}

} // namespace game