#pragma once
class UI :public Task {
private:
    std::list<Task*> m_FeatherList[10];
    CVector2D Center_pos;
    /// <summary>
    /// ExclamationMark�̍��W
    /// </summary>
    CVector2D Ex_pos2D;
    CVector3D Ex_pos3D;
    CVector4D LightFeatherColor= CVector4D(0.98f, 1.0f, 0.76f, 1.0f);
    CVector4D DarkFeatherColor=CVector4D(0.39f, 0.4f, 0.3f, 1.0f);
    CImage ExclamationMark_img;
    int ThroughList[100];
    int maxThroughNum=0;
    /// <summary>
    /// ExclamationMark�̕`�掞�Ԃ��J�E���g
    /// </summary>
    int Ex_count;
public:
    UI();
    void Update();
    void Render();
    void AddThroughList();
    /// <summary>
    /// ��ʏ㕔�ɉH��\��
    /// </summary>
    void FeatherRender();
    /// <summary>
    /// ����̃L�[���������Ƃ��ɖړI�n��\��
    /// </summary>
    void DestinationRender();
    void DestinationUpdate();
    CVector4D ColorSet();
};

