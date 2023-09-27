#include "Camera.h"
#include "../Global.h"
Camera::Camera() :Task(ETaskPrio::eCamera, EType::eCamera){
	if (PublicNum::log_passage == true) {
		std::cout << "Camera" << std::endl;
	}
	PublicNum::Camera_On = true;
	m_pos = CVector3D(-10, 10, 10);
	m_rot = CVector3D(DtoR(30), DtoR(-125), 0);
	if (PublicNum::log_passage == true) {
		std::cout << "Camerafin" << std::endl;
	}
}
void Camera::Update() {
	if (PublicNum::log_passage == true) {
		std::cout << "CameraUpdate" << std::endl;
	}
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
		//CVector3D p_pos = p->m_pos;//プレイヤーの座標
		CVector3D p_pos = PublicNum::Player_pos;
		mouse_vec = CInput::GetMouseVec();
		m_rot += CVector3D(mouse_vec.y, -mouse_vec.x, 0) * m_speed;
		//上下角制限
		m_rot.x = min(DtoR(80), max(DtoR(-80), m_rot.x));
		//180〜-180に正規化
		m_rot.y = Utility::NormalizeAngle(m_rot.y);
		m_at = p_pos + CVector3D(0, 1.5, 0);
		m_pos = m_at + CMatrix::MRotation(m_rot).GetFront() * -m_dist;
		//注視点と座標の設定
		CCamera::GetCurrent()->LookAt(m_pos, m_at, CVector3D(0, 1, 0)/*上方向ベクトル*/);
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