#include"Field.h"
Field::Field():Task(ETaskPrio::eField, EType::eField) {
	if (PublicNum::log_passage == true) {
		std::cout << "Field" << std::endl;
	}
	m_Field = COPY_RESOURCE("FirstIsland", CModelObj);
	m_Sky = COPY_RESOURCE("Sky", CModelObj);
}
void Field::Render() {
	if (PublicNum::log_passage == true) {
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
	//glEnable(GL_AMBIENT);
	//glEnable(GL_POSITION);
	//CLight::SetLighting(true);
	//glBegin();
	CLight::SetColor(0, CVector3D(0.8f, 0.8f, 0.8f/*1.0f,1.0f,1.0f*/), CVector3D(0.6f, 0.6f, 0.6f)); 
	m_Field.Render();
	CLight::SetLighting(true);
	//glEnd();
	//glDisable(GL_AMBIENT);
	//glDisable(GL_POSITION);
}
void Field::Update() {
}
CModel* Field::GetModel() {
	return  &m_Field;
}