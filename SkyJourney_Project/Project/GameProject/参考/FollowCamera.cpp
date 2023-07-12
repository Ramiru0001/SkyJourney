#include "FollowCamera.h"

FollowCamera::FollowCamera():Base(BaseType::eCamera) {
	//��p�A�A�X�y�N�g��A�N���b�v�ʁi�߁j�A�N���b�v�ʁi���j
	CCamera::GetCurrent()->Perspective(fov, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, z_near, z_far);
}
void FollowCamera::Update() {
	if (Base* p = Base::FindObject(BaseType::ePlayer)) {
		//�v���C���[�̍��W�����
		 p_pos = p->m_pos;
	}
	//�Ǐ]�J����
	//�}�E�X�̈ړ���
	mouse_vec = CInput::GetMouseVec();
	//�}�E�X�ړ�����J��������]
	//�}�E�X�ړ�Y��X����]�i�㉺�j
	//�}�E�X�ړ�X��Y����]�i���E�j
	cam_rot += CVector3D(mouse_vec.y, -mouse_vec.x, 0) * cam_speed;
	//�㉺�p����
	cam_rot.x = min(DtoR(60), max(DtoR(-35), cam_rot.x));
	//-180�x~180�x�ɐ��K��
	cam_rot.y = Utility::NormalizeAngle(cam_rot.y);
	//�ړ�����
	cam_dist = min(10.0f, max(2.0f, cam_dist + CInput::GetMouseWheel()));
	//�����_��ݒ�
	cam_at = p_pos + CVector3D(0, 1.5, 0);
	//�ʒu�ݒ�
	cam_pos = cam_at + CMatrix::MRotation(cam_rot).GetFront() * -cam_dist;
	//�ʒu�A�����_�A������̃x�N�g����ݒ�
	CCamera::GetCurrent()->LookAt(cam_pos, cam_at, CVector3D(0, 1, 0));
	//�ʒu�Ɖ�]�l
	CCamera::GetCurrent()->SetTranseRot(cam_pos, cam_rot);
}