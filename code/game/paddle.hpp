#pragma once

namespace game {

class paddle {
protected:
    void LimitMovement();


public:
    float x, y;
    float width, height;
    int speed;

    void draw();
    void update();
};

class cpu_paddle : public paddle {
public:
    void Update(int ball_y);
};

} // namespace game