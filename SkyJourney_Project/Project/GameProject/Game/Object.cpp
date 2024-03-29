#include"Object.h"
Feather::Feather(CVector3D& pos) :Task(ETaskPrio::eFeather, EType::eFeather) {
	if (PublicNum::Log_passage == true) {
		std::cout << "Feather" << std::endl;
	}
	m_model = COPY_RESOURCE("Feather", CModelObj);
	m_pos = pos;
	m_rad = 2.0f;
	m_collision = false;
}
void Feather::Render() {
	m_model.SetPos(m_pos.x,m_pos.y+1.5f,m_pos.z);
	m_model.SetRot(m_rot);
	m_model.SetScale(1.5f,1.5f,1.5f);
	CLight::SetLighting(false);
	m_model.Render();
	CLight::SetLighting(true);
}
void Feather::Update() {
	m_rot.y +=0.02f;
	m_rot.y = Utility::NormalizeAngle(m_rot.y);
}
bool Feather::GetCollision() {
	return m_collision;
}
void Feather::Collision(Task* a) {
	/*if (PublicNum::log_passage == true) {
		std::cout << "FeatherCollision" << std::endl;
	}*/
	switch (a->GetType()) {
	case EType::ePlayer:
		if ((a->m_pos - m_pos).Length() < a->m_rad + m_rad) {
			m_featherCount++;
			SetKill();
			PublicNum::Feather_Count++;
			PublicNum::LightFeather_Count = PublicNum::Feather_Count;
			if (PublicNum::FeatherDetail_Count != 0) {
				PublicNum::FeatherDetail_Count = 0;
			}
		}
		break;
	}
}
Feather::~Feather() {
}
Candle::Candle(const CVector3D& pos/*, float rotY*/) :Task(ETaskPrio::eObject, EType::eObject) {
	candle_model = COPY_RESOURCE("Glass1", CModelObj); 
	fire_model = COPY_RESOURCE("Hinokon", CModelObj);
	m_pos = pos;
	m_rad = 1.0f;
	m_collision = true;
	//m_rot.y = rotY;
}
void Candle::Render() {
	candle_model.SetPos(m_pos.x, m_pos.y + 0.35f, m_pos.z);
	fire_model.SetPos(m_pos.x, m_pos.y + 0.75f, m_pos.z);
	fire_model.SetRot(m_rot);
	candle_model.SetScale(1.5f, 1.5f, 1.5f);
	fire_model.SetScale(4.5f, 4.5f, 4.5f);
	//CLight::SetLighting(false);
	candle_model.Render();
	fire_model.Render();
	//CLight::SetLighting(true);
}
void Candle::Update() {
	m_rot.y += 0.015f;
	m_rot.y = Utility::NormalizeAngle(m_rot.y);
}
bool Candle::GetCollision() {
	return m_collision;
}
void Candle::Collision(Task* a) {
	switch (a->GetType()) {
	case EType::ePlayer:
		if ((a->m_pos - m_pos).Length() < a->m_rad + m_rad+0.5f && PublicNum::Feather_Count > PublicNum::LightFeather_Count) {
			PublicNum::FeatherDetail_Count+= PublicNum::FeatherDetail_CountMax/60;
			if (PublicNum::FeatherDetail_Count > PublicNum::FeatherDetail_CountMax && PublicNum::Feather_Count>PublicNum::LightFeather_Count) {
				PublicNum::FeatherDetail_Count = 0;
				PublicNum::LightFeather_Count++;
			}
		}
		break;
	}
}
Candle::~Candle() {
}

Signpost::Signpost(const CVector3D& pos) :Task(ETaskPrio::eObject, EType::eObject) {
	Signpost_model = COPY_RESOURCE("Signpost", CModelObj);
	m_pos = pos;
	m_rad = 1.0f;
	m_collision = true;
	//m_rot.y = rotY;
}
void Signpost::Render() {
	Signpost_model.SetPos(m_pos.x, m_pos.y + 0.35f, m_pos.z);
	Signpost_model.SetRot(m_rot);
	Signpost_model.SetScale(4.5f, 4.5f, 4.5f);
	Signpost_model.Render();
}
void Signpost::Update() {
	//m_rot.y += 0.015f;
	m_rot.y = Utility::NormalizeAngle(m_rot.y);
}
bool Signpost::GetCollision() {
	return m_collision;
}
void Signpost::Collision(Task* a) {
	switch (a->GetType()) {
	case EType::ePlayer:
		if ((a->m_pos - m_pos).Length() < a->m_rad + m_rad + 0.5f && PublicNum::Feather_Count > PublicNum::LightFeather_Count) {
			PublicNum::FeatherDetail_Count += PublicNum::FeatherDetail_CountMax / 60;
			if (PublicNum::FeatherDetail_Count > PublicNum::FeatherDetail_CountMax && PublicNum::Feather_Count > PublicNum::LightFeather_Count) {
				PublicNum::FeatherDetail_Count = 0;
				PublicNum::LightFeather_Count++;
			}
		}
		break;
	}
}
Candle::~Candle() {
}