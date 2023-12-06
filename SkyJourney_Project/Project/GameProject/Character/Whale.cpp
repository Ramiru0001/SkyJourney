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
	Search();
}
void Whale::Search() {
	//3.サーチエリアの描画。スポットライトで表現
	static float view_angle = DtoR(10.0f);
	if (HOLD(CInput::eButton1))
		view_angle += 0.01f;
	if (HOLD(CInput::eButton2))
		view_angle -= 0.01f;
	CVector3D eye_pos = CMatrix::MTranselate(m_pos) * CMatrix::MRotation(m_rot) * CVector4D(0, -10, 20.0f, 1);
	CVector3D eye_dir = CMatrix::MRotation(DtoR(80), m_rot.y, 0).GetFront();
	CVector3D ep = PublicNum::Player_pos - eye_pos;
	float d = CVector3D::Dot(eye_dir, ep.GetNormalize());
	d = min(max(d, 0), 1);
	float angle = acos(d);
	CLight::SetType(1, CLight::eLight_Spot);
	CLight::SetColor(1, CVector3D(1, 0, 0), CVector3D(1, 0, 0));
	CLight::SetAttenuation(1, 0.01f);
	CLight::SetRadiationAngle(1, view_angle);
	CLight::SetDir(1, eye_dir);
	CLight::SetPos(1, eye_pos);
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
	Search();
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
		//右回りと左回りどっちが近いか。近いほうで回る
		/*if (Alive_rot-m_rot.y> 0) {
			if(Alive_rot - m_rot.y >= RotationalSpeed)
			m_rot.y += RotationalSpeed;
			else {
				m_rot.y += (Alive_rot - m_rot.y);
			}
		}
		else if (Alive_rot - m_rot.y < 0) {
			if(Alive_rot - m_rot.y <= -RotationalSpeed)
			m_rot.y -= RotationalSpeed;
			else {
				m_rot.y -= (Alive_rot - m_rot.y);
			}
		}*/
		// Calculate the shortest rotation direction
		float angleDifference = Alive_rot - m_rot.y;
		float shortestRotation = atan2(sin(angleDifference), cos(angleDifference));

		// Rotate towards the shortest direction
		if (shortestRotation > 0) {
			m_rot.y += (RotationalSpeed < shortestRotation) ? RotationalSpeed : shortestRotation;
		}
		else if (shortestRotation < 0) {
			m_rot.y -= (RotationalSpeed < -shortestRotation) ? RotationalSpeed : -shortestRotation;
		}

		//std::cout << RtoD(Alive_rot - m_rot.y) << std::endl; 
		//std::cout << "Point_num: " << Point_num << std::endl;
		//std::cout << "Alive_rot: " << Alive_rot << std::endl;
		//前進する
		m_vec = CVector3D(cos(m_rot.y), 160.0f - m_pos.y, sin(-m_rot.y)).GetNormalize();
		//float rot=std::atan2(-m_vec.z, m_vec.x);
		m_rot.y = Utility::NormalizeAngle(m_rot.y);

}
CModel* Whale::GetModel() {
	return  &m_model;
}
void Whale::DrawCone(const GLfloat& radius, const GLfloat& height, const GLint& slices, const GLint& stacks) {
	const GLfloat PI = 3.14159265358979323846;

	glBegin(GL_TRIANGLES);

	for (int i = 0; i < slices; ++i) {
		GLfloat theta1 = (GLfloat)i * 2.0f * PI / slices;
		GLfloat theta2 = (GLfloat)(i + 1) * 2.0f * PI / slices;

		for (int j = 0; j < stacks; ++j) {
			GLfloat phi1 = (GLfloat)j * PI / stacks;
			GLfloat phi2 = (GLfloat)(j + 1) * PI / stacks;

			GLfloat x1 = radius * sin(phi1) * cos(theta1);
			GLfloat y1 = radius * cos(phi1);
			GLfloat z1 = radius * sin(phi1) * sin(theta1);

			GLfloat x2 = radius * sin(phi1) * cos(theta2);
			GLfloat y2 = radius * cos(phi1);
			GLfloat z2 = radius * sin(phi1) * sin(theta2);

			GLfloat x3 = radius * sin(phi2) * cos(theta2);
			GLfloat y3 = radius * cos(phi2);
			GLfloat z3 = radius * sin(phi2) * sin(theta2);

			GLfloat x4 = radius * sin(phi2) * cos(theta1);
			GLfloat y4 = radius * cos(phi2);
			GLfloat z4 = radius * sin(phi2) * sin(theta1);

			// Draw the triangles
			glVertex3f(x1, y1, z1);
			glVertex3f(x2, y2, z2);
			glVertex3f(x3, y3, z3);

			glVertex3f(x3, y3, z3);
			glVertex3f(x4, y4, z4);
			glVertex3f(x1, y1, z1);
		}
	}

	glEnd();
}
