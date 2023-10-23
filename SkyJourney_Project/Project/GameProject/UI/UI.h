#pragma once
class Whiteout :public Task {
private:
    int White_count = 0;
    const int MaxWhite_count = 120;
public:
    Whiteout();
    void Update();
    void Render();
    void Whiteout();
    CVector4D Whiteout_ColorSet();
};

