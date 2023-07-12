#include "Player.h"
Player::Player(CVector3D &pos):Task(ETaskPrio::ePlayer, EType::ePlayer){
	if (PublicNum::d_mode == PublicNum::LogOn) {
		std::cout << "Player" << std::endl;
	}
	m_rad = 0.5f;
	m_model = COPY_RESOURCE("Player", CModelA3M);
	m_pos = pos;
}
void Player::Render() {
	if (PublicNum::d_mode == PublicNum::LogOn) {
		std::cout << "PlayerRender" << std::endl;
	}
	m_model.SetPos(m_pos);
	m_model.SetScale(0.01f,0.01f,0.01f);
	m_model.SetRot(m_rot);;
	m_model.UpdateAnimation();
	m_model.Render();
}
void Player::Update() {
	if (PublicNum::d_mode == PublicNum::LogOn) {
		std::cout << "PlayerUpdate" << std::endl;
	}
	CVector2D mouse_vec = CInput::GetMouseVec();
	CVector3D key_dir = CVector3D(0, 0, 0);
	if (HOLD(CInput::eUp))key_dir.z = 1;
	if (HOLD(CInput::eDown))key_dir.z = -1;
	if (HOLD(CInput::eLeft))key_dir.x = 1;
	if (HOLD(CInput::eRight))key_dir.x = -1;
	if (key_dir.LengthSq() > 0) {
		m_vec = CMatrix::MRotationY(m_rot.y) * key_dir;
		m_pos += m_vec * move_speed;
		//m_model.ChangeAnimation(1);
	}
	else {
		//m_model.ChangeAnimation(0);
	}
	Task* a = Task::FindObject(EType::eCamera);
	CVector3D c_rot = a->m_rot;//�J�����̍��W
	m_rot.y = c_rot.y;
	m_pos.y -= GRAVITY;

}
void Player::Collision(Task* a) {
	if (PublicNum::d_mode == PublicNum::LogOn) {
		std::cout << "PlayerCollision" << std::endl;
	}
	//�����߂���
	CVector3D v(0, 0, 0);
	switch (a->GetType()) {
	case EType::eField:
		auto tri = a->GetModel()->CollisionSphere(m_pos + CVector3D(0, m_rad, 0), m_rad);
		//�ڐG�����ʂ̐��J��Ԃ�
		for (auto& t : tri) {
			if (t.m_normal.y < -0.5f) {
				//std::cout << "0" ;
				if (m_vec.y > 0) {
					m_vec.y = 0;
				}
			}
			else if (t.m_normal.y > 0.5f) {
				//std::cout << "1" ;
				if (m_vec.y < 0)m_vec.y = 0;
			}
			float max_y = max(t.m_vertex[0].y, max(t.m_vertex[1].y, t.m_vertex[2].y));
			//�߂荞�񂾂牟���߂�
			CVector3D nv = t.m_normal * (m_rad - t.m_dist);
			//�ł��傫�Ȉړ��ʂ����߂�
			v.y - fabs(v.y) > fabs(nv.y) ? v.y : nv.y;
			//zennbu�����߂����
			v.x = fabs(v.x) > fabs(nv.x) ? v.x : nv.x;
			v.z = fabs(v.z) > fabs(nv.z) ? v.z : nv.z;
		}
		//�����߂�
		m_pos += v;
		break;
	/*case EType::eEnemy:
		if ((b->m_pos - m_pos).Length() < b->m_rad + m_rad) {
			CVector3D PEVec = b->m_pos - m_pos;
			m_pos += PEVec.GetNormalize() * 0.5f;
			b->m_pos -= PEVec.GetNormalize() * 0.5f;
			break;
		}*/
	}
}
CModel* Player::GetModel() {
	return  &m_model;
}