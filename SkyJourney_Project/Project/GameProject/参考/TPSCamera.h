#pragma once
#include "../Base/Base.h"
class Player;
class TPSCamera : public Base {
private:
	CMatrix cam_matrix;
	CVector3D p_pos;//�v���C���[���W
	CVector2D mouse_vec;//�}�E�X�ړ��x�N�g��
	float cam_speed = 0.005f;//��]���x
public:
	TPSCamera();
	void Update();
	void Render();
};