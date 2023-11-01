#include"Object.h"
Feather::Feather(CVector3D& pos) :Task(ETaskPrio::eFeather, EType::eFeather) {
	if (PublicNum::log_passage == true) {
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
		}
		break;
	}
}
Feather::~Feather() {
}
Candle::Candle(CVector3D& pos/*, float rotY*/) :Task(ETaskPrio::eObject, EType::eObject) {
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
		if ((a->m_pos - m_pos).Length() < a->m_rad + m_rad+0.5f) {
			recovery_count++;
			if (recovery_count > 60 && PublicNum::Feather_Count>PublicNum::LightFeather_Count) {
				PublicNum::LightFeather_Count++;
				recovery_count = 0;
			}
		}
		break;
	}
}
Candle::~Candle() {
}