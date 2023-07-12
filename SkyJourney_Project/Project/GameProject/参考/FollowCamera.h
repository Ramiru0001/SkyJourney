#pragma once
#include "../Base/Base.h"
class FollowCamera :public Base {
private:
	//�}�E�X�̈ړ���
	CVector2D mouse_vec;
	//�v���C���[�̍��W
	CVector3D p_pos;
	CVector3D cam_at;
	//�J�����̈ʒu
	CVector3D cam_pos = CVector3D(-10, 10, 10);;
	//�J������]�l
	CVector3D cam_rot = CVector3D(DtoR(30), DtoR(125), 0);
	//��p
	float fov=DtoR(60.0f);
	//��p��`�拗����ύX
	float z_near = 1.0f;
	float z_far = 1000.0f;
	//�����_�܂ł̋����B�ύX�����珉���̎��_�ꏊ���ς��
	float cam_dist = 6.0f;
	//��]���x�W��
	float cam_speed = 0.002f;
	void Update();
public:
	FollowCamera();
};