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
class Sandstorm :public Task {
private:
    int FeatherBrake_CountDown = 0;
    bool FeatherBrake_flag = false;
public:
    Sandstorm();
    void Update();
    void Render();
    //void Damage();
    CVector4D ColorSet();
};

