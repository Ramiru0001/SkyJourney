#pragma once
class Whiteout :public Task {
private:
    int White_count = 0;
    int MaxWhite_count = 0;
public:
    Whiteout();
    void Update();
    void Render();
    CVector4D Whiteout_ColorSet();
};

