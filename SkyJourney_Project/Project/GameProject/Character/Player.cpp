#include "Player.h"
Player::Player(CVector3D &pos):Task(ETaskPrio::ePlayer, EType::ePlayer){
	if (PublicNum::d_mode == PublicNum::LogOn) {
		std::cout << "Player" << std::endl;
	}
	m_rad = 0.5f;
	m_model = COPY_RESOURCE("Player", CModelA3M);
	m_pos = pos;
}
void Player::Render() {
	if (PublicNum::d_mode == PublicNum::LogOn) {
		std::cout << "PlayerRender" << std::endl;
	}
	m_model.SetPos(m_pos);
	m_model.SetScale(0.01f,0.01f,0.01f);
	m_model.SetRot(m_rot);;
	m_model.UpdateAnimation();
	m_model.Render();
}
void Player::Update() {
	if (PublicNum::d_mode == PublicNum::LogOn) {
		std::cout << "PlayerUpdate" << std::endl;
	}
	CVector2D mouse_vec = CInput::GetMouseVec();
	CVector3D key_dir = CVector3D(0, 0, 0);
	if (HOLD(CInput::eUp))key_dir.z = 1;
	if (HOLD(CInput::eDown))key_dir.z = -1;
	if (HOLD(CInput::eLeft))key_dir.x = 1;
	if (HOLD(CInput::eRight))key_dir.x = -1;
	if (key_dir.LengthSq() > 0) {
		CVector3D dir = CMatrix::MRotationY(m_rot.y) * key_dir;
		if (OnGround == true) {
			m_pos += dir * move_speed;
		}
		else {
			m_pos += dir * fly_speed;
		}
		//m_model.ChangeAnimation(1);
	}
	else {
		//m_model.ChangeAnimation(0);
	}
	if (PUSH(CInput::eButton5/*space*/)) {
		if(OnGround == true)m_vec.y += JUMP;
		//m_model.ChangeAnimation(0);
	}
	Task* a = Task::FindObject(EType::eCamera);
	CVector3D c_rot = a->m_rot;//ƒJƒƒ‰‚ÌÀ•W
	m_rot.y = c_rot.y;
	m_pos.y += m_vec.y;
	m_vec.y -= GRAVITY;
	if (PublicNum::d_mode == PublicNum::LogOn) {
		std::cout << "m_pos.x : " << m_pos.x << "m_pos.y : " << m_pos.y << "m_pos.z : " << m_pos.z << std::endl;
	}
}
void Player::Collision(Task* a) {
	OnGround = false;
	if (PublicNum::d_mode == PublicNum::LogOn) {
		std::cout << "PlayerCollision" << std::endl;
	}
	//‰Ÿ‚µ–ß‚µ—Ê
	CVector3D v(0, 0, 0);
	switch (a->GetType()) {
	case EType::eField:
	{
		auto tri = a->GetModel()->CollisionSphere(m_pos + CVector3D(0, m_rad, 0), m_rad);
		//ÚG‚µ‚½–Ê‚Ì”ŒJ‚è•Ô‚·
		for (auto& t : tri) {
			if (t.m_normal.y < -0.5f) {
				if (m_vec.y > 0) {
					m_vec.y = 0;
				}
			}
			else if (t.m_normal.y > 0.5f) {
				OnGround = true;
				//std::cout << "OnGround" << std::endl;
				if (m_vec.y < 0)m_vec.y = 0;
			}
			float max_y = max(t.m_vertex[0].y, max(t.m_vertex[1].y, t.m_vertex[2].y));
			//‚ß‚è‚ñ‚¾‚ç‰Ÿ‚µ–ß‚·
			CVector3D nv = t.m_normal * (m_rad - t.m_dist);
			//Å‚à‘å‚«‚ÈˆÚ“®—Ê‚ğ‹‚ß‚é
			v.y = fabs(v.y) > fabs(nv.y) ? v.y : nv.y;
			//zennbu‰Ÿ‚µ–ß‚³‚ê‚é
			v.x = fabs(v.x) > fabs(nv.x) ? v.x : nv.x;
			v.z = fabs(v.z) > fabs(nv.z) ? v.z : nv.z;
		}
	}
		//‰Ÿ‚µ–ß‚·
		m_pos += v;
		break;
	case EType::eEnemy:
		if ((a->m_pos - m_pos).Length() < a->m_rad + m_rad) {
			CVector3D PEVec = a->m_pos - m_pos;
			m_pos += PEVec.GetNormalize() * 0.5f;
			a->m_pos -= PEVec.GetNormalize() * 0.5f;
		}
		break;
	case EType::eObject:
		if ((a->m_pos - m_pos).Length() < a->m_rad + m_rad) {
			CVector3D PEVec = a->m_pos - m_pos;
			m_pos -= PEVec.GetNormalize();
		}
		break;
	default:
		break;
	}
}
CModel* Player::GetModel() {
	return  &m_model;
}