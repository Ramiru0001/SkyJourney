#pragma once
class SkyBox :
    public Task
{
    enum {
        Normal,
        Sand,
        Purple,
        Lightpurple,
        Night,
    };
private:
    int ColorNum=Normal;
    CModelObj Normal_Model;
    CModelObj Sand_Model;
    CModelObj Purple_Model;
    CModelObj LightPurple_Model;
    CModelObj Night_Model;
public:
    SkyBox(int);
    void Render();
    void Update();
};

