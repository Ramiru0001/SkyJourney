#include "Player.h"

Player::Player(CVector3D &pos):Task(ETaskPrio::ePlayer, EType::ePlayer){
	if (PublicNum::d_mode == PublicNum::LogOn) {
		std::cout << "Player" << std::endl;
	}
	m_rad = 0.5f;
	m_model = COPY_RESOURCE("Player", CModelA3M);
	m_pos = pos;
	//元のマテリアルを複製
	//このキャラクターは1番がボディのマテリアル
	mat1 = *m_model.GetMaterial(1);
	mat2 = *m_model.GetMaterial(1);
	//テクスチャを新規作成
	mat2.mp_texture = new CTexture();
	//テクスチャを読み込み
	mat2.mp_texture->Load("Charactor/Vanguard/textures/vanguard_specular.png");
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
	//マテリアルの切り替え
	if (PUSH(CInput::eButton1))
		m_model.SetMaterial(1, &mat1);
	if (PUSH(CInput::eButton2))
		m_model.SetMaterial(1, &mat2);

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
			state = Walk;
			m_pos += dir * move_speed;
			m_model.ChangeAnimation(1);
		}
		else {
			m_pos += dir * fly_speed;
		}
	}
	else {
		if (OnGround == true) {
			state = Idle;
			m_model.ChangeAnimation(0);
		}
	}
	if (PUSH(CInput::eButton5/*space*/)) {
		//if(OnGround == true)
		m_vec.y = JUMP;
		state = Fly;
		m_model.ChangeAnimation(2);
	}
	Task* a = Task::FindObject(EType::eCamera);
	CVector3D c_rot = a->m_rot;//カメラの座標
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
	//押し戻し量
	CVector3D v(0, 0, 0);
	switch (a->GetType()) {
	case EType::eField:
	{
		if (PublicNum::d_mode == PublicNum::LogOn) {
			std::cout << "PlayerCollisionField" << std::endl;
		}
		auto tri = a->GetModel()->CollisionSphere(m_pos + CVector3D(0, m_rad, 0), m_rad);
		//接触した面の数繰り返す
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
			//めり込んだら押し戻す
			CVector3D nv = t.m_normal * (m_rad - t.m_dist);
			//最も大きな移動量を求める
			v.y = fabs(v.y) > fabs(nv.y) ? v.y : nv.y;
			//zennbu押し戻される
			v.x = fabs(v.x) > fabs(nv.x) ? v.x : nv.x;
			v.z = fabs(v.z) > fabs(nv.z) ? v.z : nv.z;
		}
	}
		//押し戻す
		m_pos += v;
		break;
	case EType::eEnemy:
		if (PublicNum::d_mode == PublicNum::LogOn) {
			std::cout << "PlayerCollisionEnemy" << std::endl;
		}
		if ((a->m_pos - m_pos).Length() < a->m_rad + m_rad) {
			CVector3D PEVec = a->m_pos - m_pos;
			m_pos += PEVec.GetNormalize() * 0.5f;
			a->m_pos -= PEVec.GetNormalize() * 0.5f;
		}
		break;
	case EType::eObject:
		if (PublicNum::d_mode == PublicNum::LogOn) {
			std::cout << "PlayerCollisionObject" << std::endl;
		}
		if (a->GetCollision() == true) {
			if ((a->m_pos - m_pos).Length() < a->m_rad + m_rad) {
				CVector3D PEVec = a->m_pos - m_pos;
				m_pos -= PEVec.GetNormalize();
			}
		}
		break;
	default:
		if (PublicNum::d_mode == PublicNum::LogOn) {
		std::cout << "PlayerCollisionDefault" << std::endl;
	}
		break;
	}
}
CModel* Player::GetModel() {
	return  &m_model;
}