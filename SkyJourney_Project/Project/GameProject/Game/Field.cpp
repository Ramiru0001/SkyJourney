#include"Field.h"
Field::Field():Task(ETaskPrio::eField) {
	m_Field =COPY_RESOURCE("FirstIsland",CModelObj);
	m_Sky = COPY_RESOURCE("Sky", CModelObj);
}
void Field::Render() {
	m_Sky.SetScale(0.1f, 0.1f, 0.1f);
	m_Field.SetScale(0.1f, 0.1f, 0.1f);
	m_Sky.Render();
	m_Field.Render();
}
void Field::Update() {}