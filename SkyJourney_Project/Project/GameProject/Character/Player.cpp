#include "Player.h"

Player::Player(CVector3D &pos):Task(ETaskPrio::ePlayer, EType::ePlayer){
	if (PublicNum::log_passage == true) {
		std::cout << "Player" << std::endl;
	}
	m_rad = 0.5f;
	m_model = COPY_RESOURCE("Player", CModelA3M);
	mant_DesignLight = COPY_RESOURCE("Mant_DesignL", CImage);
	mant_DesignDark = COPY_RESOURCE("Mant_DesignD", CImage);
	mant_DesignLight.SetSize(50, 50);
	mant_DesignDark.SetSize(50, 50);
	m_pos = pos;
	//レンダーターゲット生成
	texture_frame_rader = new CTextureFrame(512, 512, CVector4D(1, 0, 0, 1)/*マントを赤に塗りつぶし*/);
	//レンダーターゲットのテクスチャーと差し替え
	m_model.GetMaterial(12)->mp_texture = texture_frame_rader->GetTexture();

}
void Player::Render() {
	if (PublicNum::log_passage == true) {
		std::cout << "PlayerRender" << std::endl;
	}
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
	if (PublicNum::log_passage == true) {
		std::cout << "PlayerUpdate" << std::endl;
	}

	// --■モデルのテクスチャーへ書き込み----
	//現在のカメラをコピー
	CCamera back = *CCamera::GetCurrent();

	//画面解像度変更
	CCamera::GetCamera()->SetSize(texture_frame_rader->GetWidth(), texture_frame_rader->GetHeight());
	texture_frame_rader->BeginDraw();
	
	FeatherRender(PublicNum::Feather_Count, PublicNum::LightFeather_Count);
	texture_frame_rader->EndDraw();
	if (PublicNum::log_passage == true) {
		std::cout << "羽の数" << PublicNum::Feather_Count << " : " << PublicNum::LightFeather_Count << std::endl;
	}
	//カメラを元の状態に戻す
	*CCamera::GetCurrent() = back;
	Task* a = Task::FindObject(EType::eCamera);
	CVector3D c_rot = a->m_rot;//カメラの座標
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
		else if(state == Jump){
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
	if (HOLD(CInput::eButton5/*space*/ )) {
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
	m_vec.y -= GRAVITY;
	if (PublicNum::log_pos == true) {
		std::cout << "座標：" << m_pos.x << "," << m_pos.y << "," << m_pos.z << std::endl;
	}
}
void Player::FeatherRender(int Count, int LightCount) {
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
	OnGround = false;
	if (PublicNum::log_passage == true) {
		std::cout << "PlayerCollision" << std::endl;
	}
	//押し戻し量
	CVector3D v(0, 0, 0);
	switch (a->GetType()) {
	case EType::eField:
	{
		if (PublicNum::log_passage == true) {
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
		//押し戻す
		m_pos += v; 
	}
		break;
	case EType::eEnemy:
		if (PublicNum::log_passage == true) {
			std::cout << "PlayerCollisionEnemy" << std::endl;
		}
		if ((a->m_pos - m_pos).Length() < a->m_rad + m_rad) {
			CVector3D PEVec = a->m_pos - m_pos;
			m_pos += PEVec.GetNormalize() * 0.5f* move_speed;
			a->m_pos -= PEVec.GetNormalize() * 0.5f* move_speed;
		}
		break;
	case EType::eObject:
		if (PublicNum::log_passage == true) {
			std::cout << "PlayerCollisionObject" << std::endl;
		}
		if (a->GetCollision() == true) {
			if ((a->m_pos - m_pos).Length() < a->m_rad + m_rad) {
				CVector3D PEVec = a->m_pos - m_pos;
				m_pos -= PEVec.GetNormalize()* move_speed;
			}
		}
		break;
	default:
		if (PublicNum::log_passage == true) {
		std::cout << "PlayerCollisionDefault" << std::endl;
	}
		break;
	}
}
CModel* Player::GetModel() {
	return  &m_model;
}