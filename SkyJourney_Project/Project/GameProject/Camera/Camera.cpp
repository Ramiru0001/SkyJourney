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
	CVector3D p_pos = p->m_pos;//プレイヤーの座標
	mouse_vec = CInput::GetMouseVec();
	m_rot += CVector3D(mouse_vec.y, -mouse_vec.x, 0) * m_speed;
	//上下角制限
	m_rot.x = min(DtoR(60), max(DtoR(-35), m_rot.x));
	//180～-180に正規化
	m_rot.y = Utility::NormalizeAngle(m_rot.y);
	m_at = p_pos + CVector3D(0, 1.5, 0);
	m_pos = m_at + CMatrix::MRotation(m_rot).GetFront() * -m_dist;
	//注視点と座標の設定
	CCamera::GetCurrent()->LookAt(m_pos, m_at, CVector3D(0, 1, 0)/*上方向ベクトル*/);
	CCamera::GetCurrent()->SetTranseRot(m_pos, m_rot);
	CCamera::GetCurrent()->Perspective(fov,
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,z_near,z_far);
}