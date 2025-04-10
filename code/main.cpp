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

    const Vector2 screen_center{
        static_cast<float>(screen_width / 2),
        static_cast<float>(screen_height / 2)
    };

    InitWindow(screen_width, screen_height, "My Pong Game!");
    SetTargetFPS(60);

    game::ball ball{ 20.0f, screen_center, Vector2{ 7.0f, 7.0f }};

    game::paddle player;
    player.width = 25;
    player.height = 120;
    player.x = screen_width - player.width - 10;
    player.y = screen_center.y - player.height / 2;
    player.speed = 6;

    game::cpu_paddle cpu;
    cpu.height = 120;
    cpu.width = 25;
    cpu.x = 10;
    cpu.y = screen_center.y - cpu.height / 2;
    cpu.speed = 6;

    while (!WindowShouldClose()) {
        BeginDrawing();

        // Updating

        ball.update();


        if (ball.right_bound() >= GetScreenWidth()) {
            cpu_score++;
            ball.reset();
        } else if (ball.left_bound() <= 0) {
            player_score++;
            ball.reset();
        }

        player.update();
        cpu.Update(ball.get_position().y);

        // Checking for collisions
        if (CheckCollisionCircleRec(ball.get_position(), ball.get_radius(), {player.x, player.y, player.width, player.height})) {
            ball.set_velocity_x(-ball.get_velocity().x);
        } else if (CheckCollisionCircleRec(ball.get_position(), ball.get_radius(), {cpu.x, cpu.y, cpu.width, cpu.height})) {
            ball.set_velocity_x(-ball.get_velocity().x);
        }

        // Drawing
        ClearBackground(game::background_color);
        DrawRectangle(screen_center.x, 0, screen_center.x, screen_height, game::Green);
        DrawCircleV(screen_center, 150, game::Light_Green);
        DrawLine(screen_center.x, 0, screen_center.x, screen_height, WHITE);
        ball.draw();
        cpu.draw();
        player.draw();
        DrawText(TextFormat("%i", cpu_score), screen_width / 4 - 20, 20, 80, WHITE);
        DrawText(TextFormat("%i", player_score), 3 * screen_width / 4 - 20, 20, 80, WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
