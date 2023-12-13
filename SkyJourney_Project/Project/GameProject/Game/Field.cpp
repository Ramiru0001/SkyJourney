#include"Field.h"
SkyIsland::SkyIsland():Task(ETaskPrio::eField, EType::eField) {
	m_Field = COPY_RESOURCE("SkyIsland", CModelObj);
}
void SkyIsland::Render() {
	m_Field.SetScale(0.25f, 0.25f, 0.25f);
	m_Field.SetPos(80, 0, 0);
	glDisable(GL_CULL_FACE);
	m_Field.Render();
	glEnable(GL_CULL_FACE);
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
CModel* Desert::GetModel() {
	return  &m_Field;
}
Volcano::Volcano() :Task(ETaskPrio::eField, EType::eField) {
	m_Field = COPY_RESOURCE("Volcano", CModelObj);
}
void Volcano::Render() {
	m_Field.SetScale(1000.5f, 1500.5f, 1000.5f);
	m_Field.SetPos(0, -50, 0);
	glDisable(GL_CULL_FACE);
	m_Field.Render();
	glEnable(GL_CULL_FACE);
}
CModel* Volcano::GetModel() {
	return  &m_Field;
}