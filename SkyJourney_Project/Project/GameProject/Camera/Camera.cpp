#include "Camera.h"
#include "../Global.h"
Camera::Camera() :Task(ETaskPrio::eCamera, EType::eCamera){
	PublicNum::Camera_On = true;
	m_pos = CVector3D(-10, 10, 10);
	m_rot = CVector3D(DtoR(30), DtoR(-125), 0);
}
void Camera::Render() {
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
		//CVector3D p_pos = p->m_pos;//プレイヤーの座標
		CVector3D p_pos = PublicNum::Player_pos;
		mouse_vec = CInput::GetMouseVec();
		m_rot += CVector3D(mouse_vec.y, -mouse_vec.x, 0) * m_speed;
		//上下角制限
		m_rot.x = min(DtoR(80), max(DtoR(-80), m_rot.x));
		//180～-180に正規化
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
void Camera::Collision(Task* a) {
	//CVector3D v(0, 0, 0);
	//switch (a->GetType()) {
	//case EType::eField:
	//{
	//	m_rad = 0,1f;
	//	auto tri = a->GetModel()->CollisionSphere(m_pos + CVector3D(0, m_rad, 0), m_rad);
	//	for (auto& t : tri) {
	//		if (t.m_normal.y < -0.5f) {
	//			if (m_vec.y > 0) {
	//				m_vec.y = 0;
	//			}
	//		}
	//		else if (t.m_normal.y > 0.5f) {
	//			if (m_vec.y < 0)m_vec.y = 0;
	//		}
	//		float max_y = max(t.m_vertex[0].y, max(t.m_vertex[1].y, t.m_vertex[2].y));
	//		//めり込んだら押し戻す
	//		CVector3D nv = t.m_normal * (m_rad - t.m_dist);
	//		//最も大きな移動量を求める
	//		v.y = fabs(v.y) > fabs(nv.y) ? v.y : nv.y;
	//		//zennbu押し戻される
	//		v.x = fabs(v.x) > fabs(nv.x) ? v.x : nv.x;
	//		v.z = fabs(v.z) > fabs(nv.z) ? v.z : nv.z;
	//	}
	//	//押し戻す
	//	m_pos += v;
	//	PublicNum::Player_pos = m_pos;
	//}
	//break;
	////case EType::eEnemy:
	////	if ((a->m_pos - m_pos).Length() < a->m_rad + m_rad) {
	////		CVector3D PEVec = a->m_pos - m_pos;
	////		m_pos += PEVec.GetNormalize() * 0.5f * move_speed;
	////		a->m_pos -= PEVec.GetNormalize() * 0.5f * move_speed;
	////	}
	////	break;
	////case EType::eObject:
	////	if (a->GetCollision() == true) {
	////		if ((a->m_pos - m_pos).Length() < a->m_rad + m_rad) {
	////			CVector3D PEVec = a->m_pos - m_pos;
	////			m_pos -= PEVec.GetNormalize() * move_speed;
	////		}
	////	}
	////	break;
	////case eCharacter:
	////{
	////	auto tri = a->GetModel()->CollisionSphere(m_pos + CVector3D(0, m_rad, 0), m_rad);
	////	for (auto& t : tri) {
	////		if (t.m_normal.y < -0.5f) {
	////			if (m_vec.y > 0) {
	////				m_vec.y = 0;
	////			}
	////		}
	////		else if (t.m_normal.y > 0.5f) {
	////			if (m_vec.y < 0)m_vec.y = 0;
	////		}
	////		float max_y = max(t.m_vertex[0].y, max(t.m_vertex[1].y, t.m_vertex[2].y));
	////		//めり込んだら押し戻す
	////		CVector3D nv = t.m_normal * (m_rad - t.m_dist);
	////		//最も大きな移動量を求める
	////		v.y = fabs(v.y) > fabs(nv.y) ? v.y : nv.y;
	////		//zennbu押し戻される
	////		v.x = fabs(v.x) > fabs(nv.x) ? v.x : nv.x;
	////		v.z = fabs(v.z) > fabs(nv.z) ? v.z : nv.z;
	////	}
	////	//押し戻す
	////	m_pos += v;
	////}
	////break;
	////break;
	////default:
	////	break;
	////}
	//}
}
Camera::~Camera() {
	PublicNum::Camera_On = false;
}