#include <raylib.h>
#include "game/ball.hpp"
#include "game/constants.hpp"

namespace game {

void Ball::Draw() {
    DrawCircle(x, y, radius, Yellow);
}

void Ball::Update() {
    x += speed_x;
    y += speed_y;

    if (y + radius >= GetScreenHeight() || y - radius <= 0) {
       speed_y *= -1;
    }
       // Cpu wins
    if (x + radius >= GetScreenWidth()) {
        cpu_score++;
        reset();
    }

    if (x - radius <= 0) {
       player_score++;
       reset();
    }
}

void Ball::reset() {
   x = GetScreenWidth() / 2;
   y = GetScreenHeight() / 2;

   int speed_choices[2] = {-1, 1};
   speed_x *= speed_choices[GetRandomValue(0, 1)];
   speed_y *= speed_choices[GetRandomValue(0, 1)];
}

} // namespace game