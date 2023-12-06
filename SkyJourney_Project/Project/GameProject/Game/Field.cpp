#include"Field.h"
SkyIsland::SkyIsland():Task(ETaskPrio::eField, EType::eField) {
	if (PublicNum::Log_passage == true) {
		std::cout << "Field" << std::endl;
	}
	m_Field = COPY_RESOURCE("SkyIsland", CModelObj);
	//m_Sky = COPY_RESOURCE("Sky", CModelObj);
}
void SkyIsland::Render() {
	m_Field.SetScale(0.25f, 0.25f, 0.25f);
	m_Field.SetPos(80, 0, 0);
	glDisable(GL_CULL_FACE);
	m_Field.Render();
	glEnable(GL_CULL_FACE);
}
void SkyIsland::Update() {
}
CModel* SkyIsland::GetModel() {
	return  &m_Field;
}
Desert::Desert() :Task(ETaskPrio::eField, EType::eField) {
	m_Field = COPY_RESOURCE("Desert", CModelObj);
}
void Desert::Render() {
	m_Field.SetScale(2.5f, 2.5f, 2.5f);
	m_Field.SetPos(80, 0, 0);
	glDisable(GL_CULL_FACE);
	m_Field.Render();
	glEnable(GL_CULL_FACE);
}
void Desert::Update() {
}
CModel* Desert::GetModel() {
	return  &m_Field;
}