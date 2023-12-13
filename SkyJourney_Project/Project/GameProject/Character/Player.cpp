#include "Player.h"

Player::Player(CVector3D &pos):Task(ETaskPrio::ePlayer, EType::ePlayer){
	if (PublicNum::Log_passage == true) {
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
	//プレイヤーモデルの描画
	m_model.SetPos(m_pos);
	m_model.SetScale(0.01f,0.01f,0.01f);
	m_model.SetRot(m_rot);;
	glDisable(GL_CULL_FACE);
	m_model.Render();
	glEnable(GL_CULL_FACE);

}
void Player::Update() {
	PublicNum::Player_pos = m_pos;
	if (MapChangeCheck()) {
		PublicNum::Whiteout_flag = true;
		PublicNum::stage_change_flag = true;
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
	if (PublicNum::Log_pos == true) {
		std::cout << "座標：" << m_pos.x << "," << m_pos.y << "," << m_pos.z << std::endl; 
	}
	if (return_whiteout_flag == false && PublicNum::Stage_Num == PublicNum::StageNum::SkyIsland && m_pos.y < -28.2083f ) {
		//ホワイトアウトー＞ステージに戻る
		PublicNum::Whiteout_flag = true;
		Task::AddStage(new Whiteout);
		return_whiteout_flag = true;
	}
	if (return_whiteout_flag) {
		if (whiteout_count == PublicNum::MaxWhite_Count / 2) {
			m_pos = CVector3D(88.5f, 1.7f, 4.37f);
		}
		if(whiteout_count<PublicNum::MaxWhite_Count){
			whiteout_count++;
		}
		else {
			whiteout_count = 0;
			return_whiteout_flag = false;
		}
	}
	m_model.UpdateAnimation();
	//マントへ羽を描画
	FeatherDraw();
}
void Player::FeatherSetDraw(int Count, int LightCount) {
	CVector2D pos[] = { CVector2D(256, 370) ,CVector2D(256, 290) ,CVector2D(256, 210) ,CVector2D(256, 130), CVector2D(256, 50) };
	for (int i = 0; i < 10; i++) {
		if (LightCount > i) {
			if (i>4) {
				for (float x = -40; x <= 40; x++) {
					float Highy;
					float Lowy;
					if (x >= 0) {
						Highy = 0.036 * std::pow(x - 40, 2.0);
						Lowy = 0.04 * std::pow(x - 35, 2.0);
						Utility::DrawLine(CVector2D(x, Highy) + pos[i-5], CVector2D(x, Lowy) + pos[i-5], CVector4D(1.0f, 1.0f, 1.0f, 1.0f));
						Utility::DrawLine(CVector2D(x, -Highy) + pos[i-5], CVector2D(x, -Lowy) + pos[i-5], CVector4D(1.0f, 1.0f, 1.0f, 1.0f));
					}
					else {
						Highy = 0.036 * std::pow(x + 40, 2.0);
						Lowy = 0.04 * std::pow(x + 35, 2.0);
						Utility::DrawLine(CVector2D(x, Highy) + pos[i-5], CVector2D(x, Lowy) + pos[i-5], CVector4D(1.0f, 1.0f, 1.0f, 1.0f));
						Utility::DrawLine(CVector2D(x, -Highy) + pos[i-5], CVector2D(x, -Lowy) + pos[i-5], CVector4D(1.0f, 1.0f, 1.0f, 1.0f));
					}
				}
			}/*
			mant_DesignLight.SetPos(pos[i]);
			mant_DesignLight.Draw();*/
			//Utility::DrawLine(pos[i],)
			for (float x = -20; x<= 20; x++) {
				float Highy;
				float Lowy;
				if (x >= 0) {
					Highy = 0.04 * std::pow(x - 28, 2.0);
					Lowy = -0.04 * std::pow(x - 28, 2.0);
				}
				else {
					Highy = 0.04 * std::pow(x + 28, 2.0);
					Lowy = -0.04 * std::pow(x + 28, 2.0);
				}
				Utility::DrawLine(CVector2D(x, Highy) + pos[i], CVector2D(x, Lowy) + pos[i], CVector4D(1.0f, 1.0f, 1.0f, 1.0f));
			}
		}
		else if (Count > i) {
			/*mant_DesignDark.SetPos(pos[i]);
			mant_DesignDark.Draw();*/
			for (float x = -20; x <= 20; x++) {
				float Highy;
				float Lowy;
				if (x >= 0) {
					Highy = 0.05 * std::pow(x - 20, 2.0);
					Lowy = -0.05 * std::pow(x - 20, 2.0);
				}
				else {
					Highy = 0.05 * std::pow(x + 20, 2.0);
					Lowy = -0.05 * std::pow(x + 20, 2.0);
				}
				Utility::DrawLine(CVector2D(x, Highy) + pos[i], CVector2D(x, Lowy) + pos[i], CVector4D(0.0f, 0.0f, 0.0f, 1.0f));
			}
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
		//OnGround = false;
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
		PublicNum::Player_pos = m_pos;
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
	case eCharacter:
	{
		auto tri = a->GetModel()->CollisionSphere(m_pos + CVector3D(0, m_rad, 0), m_rad);
		for (auto& t : tri) {
			if (t.m_normal.y < -0.5f) {
				if (m_vec.y > 0) {
					m_vec.y = 0;
				}
			}
			else if (t.m_normal.y > 0.5f) {
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
	break;
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
				OnGround = false;
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
			OnGround = false;
			state = Jump;
			m_model.ChangeAnimation(2);//ジャンプアニメーション
			m_vec.y = JUMP;
		}
	};
	//m_rot.y = c_rot.y;
	if (m_vec.y < -GRAVITY * 5) {
		OnGround = false;
	}
	m_vec.y -= GRAVITY;
	m_pos.y += m_vec.y;
	//m_pos += m_vec;
	}
}
void Player::DebugMove() {
	CVector3D c_rot = PublicNum::Camera_rot;
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
	m_pos.y += m_vec.y;
}
void Player::FeatherDraw() {
	//現在のカメラをコピー
	CCamera back = *CCamera::GetCurrent();

	//画面解像度変更
	CCamera::GetCamera()->SetSize(texture_frame_rader->GetWidth(), texture_frame_rader->GetHeight());
	texture_frame_rader->BeginDraw();
	//羽の表示
	FeatherSetDraw(PublicNum::Feather_Count, PublicNum::LightFeather_Count);
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