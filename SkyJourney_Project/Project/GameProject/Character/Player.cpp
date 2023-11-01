#include "Player.h"

Player::Player(CVector3D &pos):Task(ETaskPrio::ePlayer, EType::ePlayer){
	if (PublicNum::log_passage == true) {
		std::cout << "Player" << std::endl;
	}
	PublicNum::Player_On = true;
	m_rad = 0.5f;
	m_model = COPY_RESOURCE("Player", CModelA3M);
	mant_DesignLight = COPY_RESOURCE("Mant_DesignL", CImage);
	mant_DesignDark = COPY_RESOURCE("Mant_DesignD", CImage);
	mant_DesignLight.SetSize(50, 50);
	mant_DesignDark.SetSize(50, 50);
	m_pos = pos;
	Stage_Pos[PublicNum::StageNum::Tytle] = CVector3D(0, 0, 0);
	Stage_Pos[PublicNum::StageNum::SkyIsland] = SkyIslandPos;
	Stage_Pos[PublicNum::StageNum::Desert] = DesertPos;
	//レンダーターゲット生成
	texture_frame_rader = new CTextureFrame(512, 512, CVector4D(1, 0, 0, 1)/*マントを赤に塗りつぶし*/);
	//レンダーターゲットのテクスチャーと差し替え
	m_model.GetMaterial(12)->mp_texture = texture_frame_rader->GetTexture();
	//std::cout << "座標ss：" << Stage_Pos[0].x << "," << Stage_Pos[0].y << "," << Stage_Pos[0].z << std::endl;
}
Player::~Player() {
	PublicNum::Player_On = false;
}
void Player::Render() {
	//マントへ羽を描画
	FeatherDraw();
	//プレイヤーモデルの描画
	m_model.SetPos(m_pos);
	m_model.SetScale(0.01f,0.01f,0.01f);
	m_model.SetRot(m_rot);;
	m_model.UpdateAnimation();
	CLight::SetColor(0, CVector3D(.9f, .9f, .9f), CVector3D(0.3f, 0.3f, 0.3f));
	glDisable(GL_CULL_FACE);
	m_model.Render();
	glEnable(GL_CULL_FACE);
}
void Player::Update() {
	PublicNum::Player_pos = m_pos;
	if (MapChangeCheck()) {
		PublicNum::Whiteout_flag = true;
	}
	if (PublicNum::Stage_Change == false) {
		if (PublicNum::Debug_mode) {
			DebugMove();
		}
		else {
			Move();
		}
	}
	else {
		m_pos = Stage_Pos[PublicNum::Stage_Num];
	}
	if (PublicNum::log_pos == true) {
		std::cout << "座標：" << m_pos.x << "," << m_pos.y << "," << m_pos.z << std::endl; 
	}
}
void Player::FeatherSetPos(int Count, int LightCount) {
	CVector2D pos[] = { CVector2D(226, 370) ,CVector2D(226, 290) ,CVector2D(226, 210) ,CVector2D(226, 130), CVector2D(226, 50) };
	for (int i = 0; i < 5; i++) {
		if (LightCount > i) {
			mant_DesignLight.SetPos(pos[i]);
			mant_DesignLight.Draw();
		}
		else if (Count > i) {
			mant_DesignDark.SetPos(pos[i]);
			mant_DesignDark.Draw();
		}
		else {
			break;
		}
	}
}
void Player::Collision(Task* a) {
	CVector3D v(0, 0, 0);
	switch (a->GetType()) {
	case EType::eField:
	{
		OnGround = false;
		auto tri = a->GetModel()->CollisionSphere(m_pos + CVector3D(0, m_rad, 0), m_rad);
		for (auto& t : tri) {
			if (t.m_normal.y < -0.5f) {
				if (m_vec.y > 0) {
					m_vec.y = 0;
				}
			}
			else if (t.m_normal.y > 0.5f) {
				OnGround = true; /*
				if (PublicNum::log_passage == true) {
					std::cout << "OnGround" << std::endl;
				}*/
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
		//押し戻す
		m_pos += v; 
	}
	//std::cout << "OffGround1" << std::endl;
		break;
	case EType::eEnemy:
		if ((a->m_pos - m_pos).Length() < a->m_rad + m_rad) {
			CVector3D PEVec = a->m_pos - m_pos;
			m_pos += PEVec.GetNormalize() * 0.5f* move_speed;
			a->m_pos -= PEVec.GetNormalize() * 0.5f* move_speed;
		}
		break;
	case EType::eObject:
		if (a->GetCollision() == true) {
			if ((a->m_pos - m_pos).Length() < a->m_rad + m_rad) {
				CVector3D PEVec = a->m_pos - m_pos;
				m_pos -= PEVec.GetNormalize()* move_speed;
			}
		}
		break;
	default:
		break;
	}
}
void Player::Move() {
	{CVector3D c_rot = PublicNum::Camera_rot;
	CVector2D mouse_vec = CInput::GetMouseVec();
	CVector3D key_dir = CVector3D(0, 0, 0);
	if (HOLD(CInput::eUp))key_dir.z = 1;
	if (HOLD(CInput::eDown))key_dir.z = -1;
	if (HOLD(CInput::eLeft))key_dir.x = 1;
	if (HOLD(CInput::eRight))key_dir.x = -1;
	if (key_dir.LengthSq() > 0) {
		CVector3D dir = CMatrix::MRotationY(m_rot.y).GetFront();
		m_rot.y = Utility::NormalizeAngle(c_rot.y + atan2(key_dir.x, key_dir.z));
		if (OnGround == true) {
			state = Walk;
			m_pos += dir * move_speed;
			m_model.ChangeAnimation(1);
		}
		else if (state == Jump) {
			m_pos += dir * jump_speed;
		}
		else if (state == Fly) {
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
		space_count = 0;
	}
	if (HOLD(CInput::eButton5/*space*/)) {
		if (space_count == 10) {
			if (PublicNum::LightFeather_Count > 0) {
				//if(OnGround == true)
				m_vec.y = FLY;
				state = Fly;
				m_model.ChangeAnimation(2);
				PublicNum::LightFeather_Count--;
			}
		}
		space_count++;
	}
	if (PULL(CInput::eButton5/*space*/)) {
		if (space_count < 10 && state != Jump && state != Fly) {
			state = Jump;
			m_model.ChangeAnimation(2);//ジャンプアニメーション
			m_vec.y = JUMP;
		}
	};
	//m_rot.y = c_rot.y;
	m_pos.y += m_vec.y;
	//m_pos += m_vec;
	m_vec.y -= GRAVITY; }
}
void Player::DebugMove() {
	{CVector3D c_rot = PublicNum::Camera_rot;
	CVector2D mouse_vec = CInput::GetMouseVec();
	CVector3D key_dir = CVector3D(0, 0, 0);
	if (HOLD(CInput::eUp))key_dir.z = 1;
	if (HOLD(CInput::eDown))key_dir.z = -1;
	if (HOLD(CInput::eLeft))key_dir.x = 1;
	if (HOLD(CInput::eRight))key_dir.x = -1;
	if (key_dir.LengthSq() > 0) {
		CVector3D dir = CMatrix::MRotationY(m_rot.y).GetFront();
		m_rot.y = Utility::NormalizeAngle(c_rot.y + atan2(key_dir.x, key_dir.z));
		//if (OnGround == true) {
			state = Walk;
			m_pos += dir * debug_speed;
			m_model.ChangeAnimation(1);
	}
	else {
		if (OnGround == true) {
			state = Idle;
			m_model.ChangeAnimation(0);
		}
	}
	if (HOLD(CInput::eSpace)) {
		m_pos.y += 0.5f;
	}
	if (HOLD(CInput::eShift)) {
		m_pos.y -= 0.5f;
	}
	//	space_count = 0;
	//}
	//飛ぶ処理
	//if (HOLD(CInput::eButton5/*space*/)) {
	//	if (space_count == 10) {
	//		if (PublicNum::LightFeather_Count > 0) {
	//			//if(OnGround == true)
	//			m_vec.y = FLY;
	//			state = Fly;
	//			m_model.ChangeAnimation(2);
	//			PublicNum::LightFeather_Count--;
	//		}
	//	}
	//	space_count++;
	//}
	//ジャンプ処理
	//if (PULL(CInput::eButton5/*space*/)) {
	//	if (space_count < 10 && state != Jump && state != Fly) {
	//		state = Jump;
	//		m_model.ChangeAnimation(2);//ジャンプアニメーション
	//		m_vec.y = JUMP;
	//	}
	//};
	//m_rot.y = c_rot.y;
	m_pos.y += m_vec.y;
	//m_pos += m_vec;
	//m_vec.y -= GRAVITY; 
	}
}
void Player::FeatherDraw() {
	//現在のカメラをコピー
	CCamera back = *CCamera::GetCurrent();

	//画面解像度変更
	CCamera::GetCamera()->SetSize(texture_frame_rader->GetWidth(), texture_frame_rader->GetHeight());
	texture_frame_rader->BeginDraw();
	//羽の表示
	FeatherSetPos(PublicNum::Feather_Count, PublicNum::LightFeather_Count);
	texture_frame_rader->EndDraw();
	//カメラを元の状態に戻す
	*CCamera::GetCurrent() = back;
}
bool Player::MapChangeCheck() {
	switch (PublicNum::Stage_Num) {
	case PublicNum::StageNum::SkyIsland:
		if (m_pos.x>-120.0f&&m_pos.x < -107.3f && m_pos.y > 29.0f && m_pos.y < 40.0f && m_pos.z < 11.0f && 5.0f < m_pos.z) {
			return true;
		}
		break;
	case PublicNum::StageNum::Desert:
		if (m_pos.z<8.6 && m_pos.z>-17.0 && m_pos.y > 1.7 && m_pos.y < 57.2 && m_pos.x < -313&& m_pos.x > -323) {
			return true;
		}
		break;
	}
	return false;
}
CModel* Player::GetModel() {
	return  &m_model;
}