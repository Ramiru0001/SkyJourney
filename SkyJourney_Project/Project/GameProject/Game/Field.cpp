#include"Field.h"
Field::Field():Task(ETaskPrio::eField, EType::eField) {
	if (PublicNum::d_mode == PublicNum::LogOn) {
		std::cout << "Field" << std::endl;
	}
	m_Field = COPY_RESOURCE("FirstIsland", CModelObj);
	m_Sky = COPY_RESOURCE("Sky", CModelObj);
}
void Field::Render() {
	if (PublicNum::d_mode == PublicNum::LogOn) {
		std::cout << "FieldRender" << std::endl;
	}
	m_Sky.SetScale(800.0f, 800.0f, 800.0f);
	m_Field.SetScale(0.25f, 0.25f, 0.25f);
	m_Sky.SetPos(0, -30, 0);
	m_Field.SetPos(80, 0, 0);
	glDisable(GL_CULL_FACE);
	CLight::SetLighting(false);
	m_Sky.Render();
	glEnable(GL_CULL_FACE);
	CLight::SetLighting(true);
	m_Field.Render();
}
void Field::Update() {
}
CModel* Field::GetModel() {
	return  &m_Field;
}