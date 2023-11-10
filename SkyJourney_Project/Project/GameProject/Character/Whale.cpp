#include "Whale.h"
Whale::Whale(CVector3D& pos) :Task(ETaskPrio::eCharacter, EType::eCharacter) {
	m_pos = pos;
	m_model= COPY_RESOURCE("Whale", CModelA3M);
	m_model.ChangeAnimation(0);
}
void Whale::Update() {
	Move();
	Search();
}
void Whale::Render() {
	m_model.SetScale(1.0f,1.0f, 1.0f);
	m_model.SetRot(m_rot);;
	m_model.SetPos(m_pos);
	m_model.UpdateAnimation();
	m_model.Render();
}
void Whale::Search() {

}