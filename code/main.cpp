#include <cstdio>
#include <raylib.h>

#include "game/constants.hpp"
#include "game/ball.hpp"
#include "game/paddle.hpp"


int main() {

    int32_t player_score = 0;
    int32_t cpu_score = 0;

    std::printf("Starting the game");

    constexpr int32_t screen_width = 1280;
    constexpr int32_t screen_height = 800;
    constexpr float paddle_width{ 25.0f };
    constexpr float paddle_height{ 120.0f };

    const Vector2 screen_center{
        static_cast<float>(screen_width / 2),
        static_cast<float>(screen_height / 2)
    };

    InitWindow(screen_width, screen_height, "Wimbledon Cup");

    InitAudioDevice();

    Sound fx_paddle = LoadSound("resources/Paddle.wav");
    Sound fx_wall = LoadSound("resources/Wall.wav");
    Sound fx_win = LoadSound("resources/Win.wav");

    SetTargetFPS(60);

    game::ball ball{ 20.0f, screen_center, Vector2{ 7.0f, 7.0f }};

    game::paddle player{
        Rectangle{
            screen_width - paddle_width - 10,
            screen_center.y - paddle_height,
            paddle_width, paddle_height,
        },
        6
    };

    game::cpu_paddle cpu{
        Rectangle{ 10,
            screen_center.y - paddle_height /2,
            paddle_width, paddle_height,
        },
        6
    };

    while (!WindowShouldClose()) {
        BeginDrawing();

        // Updating

        ball.update();

        if (ball.upper_bound() <= 0) {
            PlaySound(fx_wall);
        } else if (ball.lower_bound() >= GetScreenHeight()) {
            PlaySound(fx_wall);
        }


        if (ball.right_bound() >= GetScreenWidth()) {
            cpu_score++;
            PlaySound (fx_win);
            ball.reset();
        } else if (ball.left_bound() <= 0) {
            player_score++;
            PlaySound (fx_win);
            ball.reset();
        }

        player.update();
        cpu.cpu_update(ball.get_position().y);

        // Checking for collisions,  can be used inside ball.cpp (do a "collide(cpu.get_rect)" method)
        if (CheckCollisionCircleRec(ball.get_position(), ball.get_radius(), player.get_rect())) {
            PlaySound (fx_paddle);
            ball.set_velocity_x(-ball.get_velocity().x);
        } else if (CheckCollisionCircleRec(ball.get_position(), ball.get_radius(), cpu.get_rect())) {
            PlaySound (fx_paddle);
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

    UnloadSound(fx_paddle);
    UnloadSound(fx_wall);
    UnloadSound(fx_win);

    CloseAudioDevice();

    CloseWindow();
    return 0;
}
