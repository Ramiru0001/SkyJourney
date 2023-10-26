#pragma once
class SkyBox :
    public Task
{
private:
    CModelObj SkyBox_model;
public:
    SkyBox();
    void Render();
    void Update();
};

