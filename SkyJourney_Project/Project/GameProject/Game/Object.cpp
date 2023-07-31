#include"Object.h"
Feather::Feather(CVector3D& pos) :Task(ETaskPrio::eFeather, EType::eFeather) {
	if (PublicNum::d_mode == PublicNum::LogOn) {
		std::cout << "Feather" << std::endl;
	}
	m_model = COPY_RESOURCE("Feather", CModelObj);
	m_pos = pos;
	m_rad = 2.0f;
	m_collision = false;
}
void Feather::Render() {
	if (PublicNum::d_mode == PublicNum::LogOn) {
		std::cout << "FeatherRender" << std::endl;
	}
	m_model.SetPos(m_pos.x,m_pos.y+1.5f,m_pos.z);
	m_model.SetRot(m_rot);
	m_model.SetScale(1.5f,1.5f,1.5f);
	CLight::SetLighting(false);
	m_model.Render();
	CLight::SetLighting(true);
}
void Feather::Update() {
	if (PublicNum::d_mode == PublicNum::LogOn) {
		std::cout << "FeatherUpdate" << std::endl;
	}
	//Task* a = Task::FindObject(EType::ePlayer);
	//CVector3D FPvec = a->m_pos - m_pos;
	m_rot.y +=0.02f;
	m_rot.y = Utility::NormalizeAngle(m_rot.y);
}
bool Feather::GetCollision() {
	return m_collision;
}
void Feather::Collision(Task* a) {
	if (PublicNum::d_mode == PublicNum::LogOn) {
		std::cout << "FeatherCollision" << std::endl;
	}
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