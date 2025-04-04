#pragma once

namespace game {

class Paddle {
protected:
    void LimitMovement();


public:
    float x, y;
    float width, height;
    int speed;

    void Draw();
    void Update();
};

class CpuPaddle : public Paddle {
public:
    void Update(int ball_y);
};

} // namespace game