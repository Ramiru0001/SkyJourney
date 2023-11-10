#pragma once
class UI :public Task {
private:
    std::list<Task*> m_FeatherList[10];
    CVector2D Center_pos;
    CVector4D LightFeatherColor= CVector4D(0.98f, 1.0f, 0.76f, 1.0f);
    CVector4D DarkFeatherColor=CVector4D(0.39f, 0.4f, 0.3f, 1.0f);
    int ThroughList[100];
    int maxThroughNum=0;
public:
    UI();
    void Update();
    void Render();
    void AddThroughList();
    CVector4D ColorSet();
};

