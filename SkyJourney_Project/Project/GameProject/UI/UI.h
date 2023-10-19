#pragma once
class UI :public Task {
private:
    bool Whiteout_Flag = false;
    int Whiteout_Timer = 30;
public:
    UI();
    void Update();
    void Render();
    CVector4D Whiteout_ColorSet();
};

