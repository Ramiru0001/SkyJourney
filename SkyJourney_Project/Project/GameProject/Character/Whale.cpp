#include "Whale.h"
Whale::Whale(/*CVector3D& pos*/) :Task(ETaskPrio::eCharacter, EType::eCharacter) {
	//m_pos = pos;
	m_model= COPY_RESOURCE("Whale", CModelA3M);
	m_model.ChangeAnimation(0);
	m_pos = DEFAULT_POS;
}
void Whale::Update() {
	Move();
	m_pos += m_vec;
	Search();
}
void Whale::Render() {
	m_model.SetScale(0.1f,0.1f, 0.1f);
	m_model.SetRot(m_rot);;
	m_model.SetPos(m_pos);
	m_model.UpdateAnimation();
	m_model.Render();
}
void Whale::Search() {

}
void Whale::Move() {
	CVector3D point_pos[] = {
		CVector3D(344.873,53.0718,-8.48718),
		CVector3D(248.225,53.0718,-58.3277),
		CVector3D(117.756,53.0718,-1.22288),
		CVector3D(-14.4411,53.0718,-97.8118),
		CVector3D(45.2624,53.0718,-270.918),
		CVector3D(-218.738,53.0718,-277.225),
		CVector3D(-273.647,53.0718,-64.9262),
		CVector3D(-251.047,53.0718,173.825),
		CVector3D(-81.6449,53.0718,133.62),
		CVector3D(39.7592,53.0718,84.0604),
		CVector3D(175.759,53.0718,144.18),
		CVector3D(342.818,53.0718,217.323),
	};
		if (point_pos[Point_num].x - m_pos.x < 1.0f && point_pos[Point_num].z - m_pos.z < 1.0f) {
			if (Point_num < 12) {
				Point_num++;
			}
			else {
				Point_num = 0;
			}
		}
		//m_vec2D = CVector2D((point_pos[Point_num].x - m_pos.x), (point_pos[Point_num].z - m_pos.z)).GetNormalize();
		//到着先へのベクトルと角度を入手
		CVector3D Allive_vec= CVector3D((point_pos[Point_num].x - m_pos.x), 160.0f - m_pos.y, (point_pos[Point_num].z - m_pos.z)).GetNormalize();
		float Alive_rot= Utility::NormalizeAngle(std::atan2(-Allive_vec.z, Allive_vec.x));
		//現在の角度に、回転可能角度を足す
		if (Alive_rot-m_rot.y> 0) {
			if(Alive_rot - m_rot.y > RotationalSpeed)
			m_rot.y += RotationalSpeed;
			else {
				m_rot.y += (Alive_rot - m_rot.y);
			}
		}
		else if (Alive_rot - m_rot.y < 0) {
			if(Alive_rot - m_rot.y < -RotationalSpeed)
			m_rot.y -= RotationalSpeed;
			else {
				m_rot.y -= (Alive_rot - m_rot.y);
			}
		}
		std::cout << RtoD(Alive_rot - m_rot.y) << std::endl;
		//前進する
		m_vec = CVector3D(cos(m_rot.y), 160.0f - m_pos.y, sin(-m_rot.y)).GetNormalize();
		//float rot=std::atan2(-m_vec.z, m_vec.x);
		m_rot.y = Utility::NormalizeAngle(m_rot.y);

}
CModel* Whale::GetModel() {
	return  &m_model;
}
