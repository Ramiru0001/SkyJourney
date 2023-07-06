#include"Field.h"
Field::Field() {
	m_Field =COPY_RESOURCE("FirstIsland",CModelObj);
}
void Field::Render() {
	m_Sky.SetScale(0.1f, 0.1f, 0.1f);
	m_Field.SetScale(0.1f, 0.1f, 0.1f);
	m_Sky.Render();
	m_Field.Render();
}