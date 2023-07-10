#include "Camera.h"
Camera::Camera() :Task(ETaskPrio::eCamera){
	std::cout << "Camera" << std::endl;
	m_pos = CVector3D(-10, 10, 10);
	m_rot = CVector3D(DtoR(30), DtoR(-125), 0);
	std::cout << "Camerafin" << std::endl;
}
void Camera::Update() {
	switch(mode) {
		case FixedPoint:
		case WithPlayer:
	}
	std::cout << "CameraUpdate" << std::endl;
	Task* p = Task::FindObject(ETaskPrio::ePlayer);
	CVector3D p_pos = p->m_pos;//�v���C���[�̍��W
	mouse_vec = CInput::GetMouseVec();
	m_rot += CVector3D(mouse_vec.y, -mouse_vec.x, 0) * m_speed;
	//�㉺�p����
	m_rot.x = min(DtoR(60), max(DtoR(-35), m_rot.x));
	//180�`-180�ɐ��K��
	m_rot.y = Utility::NormalizeAngle(m_rot.y);
	m_at = p_pos + CVector3D(0, 1.5, 0);
	m_pos = m_at + CMatrix::MRotation(m_rot).GetFront() * -m_dist;
	//�����_�ƍ��W�̐ݒ�
	CCamera::GetCurrent()->LookAt(m_pos, m_at, CVector3D(0, 1, 0)/*������x�N�g��*/);
	CCamera::GetCurrent()->SetTranseRot(m_pos, m_rot);
	CCamera::GetCurrent()->Perspective(fov,
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,z_near,z_far);
}