#include "Camera.h"
#include "../Global.h"
Camera::Camera() :Task(ETaskPrio::eCamera, EType::eCamera){
	PublicNum::Camera_On = true;
	m_pos = CVector3D(-10, 10, 10);
	m_rot = CVector3D(DtoR(30), DtoR(-125), 0);
}
void Camera::Update() {
	if (CShadow::GetInstance()->GetState() == CShadow::eShadow)return;
	switch(PublicNum::c_mode) {
	case PublicNum::FixedPoint:
		m_pos = CVector3D(-10, 10, 50);
		m_at= m_pos + CVector3D(0, 1.5, 0);
		//CCamera::GetCurrent()->LookAt(m_pos, m_at, CVector3D(0, 1, 0));
		m_rot = CVector3D(DtoR(30), DtoR(180), 0);
		CCamera::GetCurrent()->SetTranseRot(m_pos, m_rot);
		CCamera::GetCurrent()->Perspective(fov,
			(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
			z_near,
			z_far);
		PublicNum::Camera_rot = m_rot;
		break;
	case PublicNum::WithPlayer:
		//Task* p = Task::FindObject(EType::ePlayer);
		//CVector3D p_pos = p->m_pos;//�v���C���[�̍��W
		CVector3D p_pos = PublicNum::Player_pos;
		mouse_vec = CInput::GetMouseVec();
		m_rot += CVector3D(mouse_vec.y, -mouse_vec.x, 0) * m_speed;
		//�㉺�p����
		m_rot.x = min(DtoR(80), max(DtoR(-80), m_rot.x));
		//180�`-180�ɐ��K��
		m_rot.y = Utility::NormalizeAngle(m_rot.y);
		m_at = p_pos + CVector3D(0, 1.5, 0);
		m_pos = m_at + CMatrix::MRotation(m_rot).GetFront() * -m_dist;
		//�����_�ƍ��W�̐ݒ�
		CCamera::GetCurrent()->LookAt(m_pos, m_at, CVector3D(0, 1, 0)/*������x�N�g��*/);
		CCamera::GetCurrent()->SetTranseRot(m_pos, m_rot);
		CCamera::GetCurrent()->Perspective(fov,
			(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, z_near, z_far);
		PublicNum::Camera_rot = m_rot;
		break;
	}
}
Camera::~Camera() {
	PublicNum::Camera_On = false;
}