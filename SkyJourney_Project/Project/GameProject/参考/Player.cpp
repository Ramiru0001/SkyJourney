#include "Player.h"
Player::Player(const CVector3D& pos) :Base(BaseType::ePlayer) {
	m_model = COPY_RESOURCE("Girl", CModelA3M);
	m_pos = pos;
	m_rot = CVector3D(0, 0, 0);
	m_vec = CVector3D(0, 0, 0);
	m_rad = 0.5f;
}
void Player::Update() {
	PushToMove();
	//�d�͗���
	//m_pos.y -= GRAVITY;
	//�G�ƃX�e�[�W�̓����蔻��
}
void Player::Render() {
	m_model.UpdateAnimation();
	m_model.SetPos(m_pos);
	m_model.SetRot(0, cam_rot.y, 0);
	m_model.SetScale(0.01f, 0.01f, 0.01f);
	m_model.Render();
}
void Player::PushToMove() {
	Base* Camera = Base::FindObject(BaseType::eCamera);
	cam_rot = Camera->m_rot;
	CVector3D key_dir = CVector3D(0, 0, 0);
	if (HOLD(CInput::eUp))key_dir.z = 1;
	if (HOLD(CInput::eDown))key_dir.z = -1;
	if (HOLD(CInput::eLeft))key_dir.x = 1;
	if (HOLD(CInput::eRight))key_dir.x = -1;
	if (key_dir.LengthSq() > 0) {
		CVector3D dir = CMatrix::MRotationY(cam_rot.y) * key_dir;
		m_pos += dir * move_speed;
		m_model.ChangeAnimation(1);
	}
	else {
		m_model.ChangeAnimation(0);
	}
}
void Player::Collision(Base* b) {
	//�����߂���
	CVector3D v(0, 0, 0);
	switch (b->GetType()) {
	case BaseType::eField:
		auto tri = b->GetModel()->CollisionSphere(m_pos + CVector3D(0, m_rad, 0), m_rad);
		//�ڐG�����ʂ̐��J��Ԃ�
		for (auto& t : tri) {
			if (t.m_normal.y < -0.5f) {
				//std::cout << "0" ;
				if (m_vec.y > 0) {
					m_vec.y = 0;
				}
			}
			else if(t.m_normal.y>0.5f) {
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
	case BaseType::eEnemy:
		if ((b->m_pos - m_pos).Length() < b->m_rad + m_rad) {
			CVector3D PEVec = b->m_pos - m_pos;
			m_pos += PEVec.GetNormalize() * 0.5f;
			b->m_pos -= PEVec.GetNormalize() * 0.5f;
		}
	}
}
