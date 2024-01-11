#pragma once
class SkyBox :
    public Task
{
    enum {
        Normal,
        Sand,
        night,
    };
private:
    int ColorNum=Normal;
    CModelObj SkyBox_model;
public:
    SkyBox(int);
    void Render();
    void Update();
};

