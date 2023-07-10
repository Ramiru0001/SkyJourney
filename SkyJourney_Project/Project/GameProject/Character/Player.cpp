#include "Player.h"
Player::Player(CVector3D &pos):Task(ETaskPrio::ePlayer){
	std::cout << "Player" << std::endl;
	m_model = COPY_RESOURCE("Player", CModelA3M);
	m_pos = pos;
}
void Player::Render() {
	std::cout << "PlayerRender" << std::endl;
	m_model.SetPos(m_pos);
	m_model.SetScale(0.01f,0.01f,0.01f);
	m_model.SetRot(m_rot);
	m_model.Render();
}
void Player::Update() {
	std::cout << "PlayerUpdate" << std::endl;
}