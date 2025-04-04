#include <cstdio>
#include <raylib.h>

#include "game/constants.hpp"
#include "game/ball.hpp"
#include "game/paddle.hpp"


int main() {

    int32_t player_score = 0;
    int32_t cpu_score = 0;

    std::printf("Starting the game");

    const int32_t screen_width = 1280;
    const int32_t screen_height = 800;

    InitWindow(screen_width, screen_height, "My Pong Game!");
    SetTargetFPS(60);

    game::Ball ball;
    ball.radius = 20;
    ball.x = screen_width / 2;
    ball.y = screen_height / 2;
    ball.speed_x = 7;
    ball.speed_y = 7;

    game::Paddle player;
    player.width = 25;
    player.height = 120;
    player.x = screen_width - player.width - 10;
    player.y = screen_height / 2 - player.height / 2;
    player.speed = 6;

    game::CpuPaddle cpu;
    cpu.height = 120;
    cpu.width = 25;
    cpu.x = 10;
    cpu.y = screen_height / 2 - cpu.height / 2;
    cpu.speed = 6;

    while (WindowShouldClose() == false) {
        BeginDrawing();

        // Updating

        ball.Update();
        player.Update();
        cpu.Update(ball.y);

        // Checking for collisions
        if (CheckCollisionCircleRec({ball.x, ball.y}, ball.radius, {player.x, player.y, player.width, player.height})) {
            ball.speed_x *= -1;
        }

        if (CheckCollisionCircleRec({ball.x, ball.y}, ball.radius, {cpu.x, cpu.y, cpu.width, cpu.height})) {
            ball.speed_x *= -1;
        }

        // Drawing
        ClearBackground(game::background_color);
        DrawRectangle(screen_width / 2, 0, screen_width / 2, screen_height, game::Green);
        DrawCircle(screen_width / 2, screen_height / 2, 150, game::Light_Green);
        DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, WHITE);
        ball.Draw();
        cpu.Draw();
        player.Draw();
        DrawText(TextFormat("%i", cpu_score), screen_width / 4 - 20, 20, 80, WHITE);
        DrawText(TextFormat("%i", player_score), 3 * screen_width / 4 - 20, 20, 80, WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
