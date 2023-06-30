#include "PlayerCamera.h"
PlayerCamera::PlayerCamera():Base(BaseType::eCamera){
	m_rot = CVector3D(0, 0, 0);
	m_pos = CVector3D(0, 0, 0);
}
void PlayerCamera::Update() {
	//�J�����̉�]�l���擾
	//cam_ang = m_rot.y;
	////�����L�[�̃x�N�g��
	//CVector3D key_dir = CVector3D(0, 0, 0);
	//if (HOLD(CInput::eUp))key_dir.z = 1;
	//if (HOLD(CInput::eDown))key_dir.z = -1;
	//if (HOLD(CInput::eLeft))key_dir.x = 1;
	//if (HOLD(CInput::eRight))key_dir.x = -1;
	////���͂�����΁B
	//if (key_dir.LengthSq() > 0) {
	//	if (key_dir.LengthSq() > 0) {
	//		CVector3D dir = CMatrix::MRotationY(m_rot.y) * key_dir;
	//	}
	//}
	CVector2D mouse_vec = CInput::GetMouseVec();
	m_rot += CVector3D(mouse_vec.y, -mouse_vec.x, 0) * cam_speed;
	//���z���J����
	//�v���C���[�̌��̈ʒu�ɁB�J�����̊p�x�Ŕz�u
	{
		Base* Player = Base::FindObject(BaseType::ePlayer);
		p_pos = Player->m_pos;
		//�L�����N�^�[�̉E�����ɃJ������ݒu����
		CMatrix cam_matrix = CMatrix::MTranselate(p_pos)
			* CMatrix::MTranselate(CVector3D(0, 1.5, 0))
			* CMatrix::MRotation(m_rot)
			* CMatrix::MTranselate(CVector3D(-0.5, 0.2, -2));
		//�J�����ʒu���s��Ŏw��
		CCamera::GetCurrent()->SetTranseRot(cam_matrix);
	}
}