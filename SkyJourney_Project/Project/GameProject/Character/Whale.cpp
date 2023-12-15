#include "Whale.h"
Whale::Whale(const std::vector<CVector3D>& MovePos) :Task(ETaskPrio::eCharacter, EType::eCharacter) {
	//m_pos = pos;
	m_model= COPY_RESOURCE("Whale", CModelA3M);
	m_model.ChangeAnimation(0);
	m_pos = DEFAULT_POS;
	MovePos_List = MovePos;
	auto itr = MovePos_List.begin();
}
void Whale::Update() {
	// �T�[�`�͈͂̒��Ƀv���C���[�����邩����
	if (!CheckPlayerInSearchRange(view_angle)) {
		// �v���C���[���T�[�`�͈͓��ɂ��Ȃ��ꍇ�͎���
		Move(DestinationSelection());
	}
	else {
		m_vec = CVector3D(0,0,0);
	}
	Search();
	// �ړ�����
	m_pos += m_vec;
}
void Whale::Render() {
	m_model.SetScale(0.1f,0.1f, 0.1f);
	m_model.SetRot(m_rot+CVector3D(0,DtoR(-90),0));
	m_model.SetPos(m_pos);
	m_model.UpdateAnimation();
	m_model.Render();
}
void Whale::Search() {
	//3.�T�[�`�G���A�̕`��B�X�|�b�g���C�g�ŕ\��
	view_angle = DtoR(10.0f);
	CVector3D ep = PublicNum::Player_pos - eye_pos;
	CVector3D default_dir= CMatrix::MRotation(DtoR(70), m_rot.y, 0).GetFront();;
	/*if (HOLD(CInput::eButton1))
		view_angle += 0.01f;
	if (HOLD(CInput::eButton2))
		view_angle -= 0.01f;*/
	eye_pos = CMatrix::MTranselate(m_pos) * CMatrix::MRotation(m_rot) * CVector4D(0, -10, 20.0f, 1);
	//�O��̊p�x
	//�����v���C���[�����E�ɓ����Ă���ꍇ�A�T�[�`�G���A�����ɂƂ炦��悤�ɃG���A�𓮂���
	CVector3D new_dir;
	float r;
	if (CheckPlayerInSearchRange(view_angle)) {
		new_dir = ep.GetNormalize();
		r = 0.9;
	}
	else{
		//�v���C���[���T�[�`�G���A�O�̏ꍇ
		new_dir = CMatrix::MRotation(DtoR(70), m_rot.y, 0).GetFront();
		r = 0;
	};
	if (CVector3D::Dot(new_dir, default_dir)>cos(DtoR(15))) {
		eye_dir = (eye_dir * r + new_dir * (1.0-r)).GetNormalize();
	}
	float a = CVector3D::Dot(new_dir, default_dir);
	std::cout << "Dot : " << a << std::endl;
	std::cout << "cos : " << cos(DtoR(60)) << std::endl;
	//else {
	//	//�v���C���[���T�[�`�G���A���̏ꍇ
	//	CVector3D ep = PublicNum::Player_pos - eye_pos;
	//	CVector3D EpNormalize = ep.GetNormalize();
	//	float d = CVector3D::Dot(eye_dir, ep.GetNormalize());
	//	float angle = acos(d);
	//	float MaxView_Angle;
	//	eye_dir = ep.GetNormalize();
	//	//���_����v���C���[�̃x�N�g���A���_����T�[�`�̒����ւ̃x�N�g�������
	//	//�����Ƃ��v���C���[��Y���W�̍����Ōv�Z���āA�v���C���[���璆���ւ̃x�N�g��������o��
	//	//���̕����փT�[�`�G���A�𓮂���
	//}
	{//�����炳��̖ڂ���v���C���[�̊p�x�����߂�
		float d = CVector3D::Dot(eye_dir, ep.GetNormalize());
		d = min(max(d, 0), 1);
		//�v���C���[�̊p�x
		player_angle = acos(d); }
	CLight::SetType(1, CLight::eLight_Spot);
	//�v���C���[�����E�ɓ����Ă�����
	if (CheckPlayerInSearchRange(view_angle)) {
		// ���E�ɓ��������̃T�[�`���C�g�̐F��ύX
		CLight::SetColor(1, CVector3D(1, 0, 0), CVector3D(1, 0, 0));
	}
	else {
		// ���E�ɓ����Ă��Ȃ��ꍇ�̃T�[�`���C�g�̐F
		CLight::SetColor(1, CVector3D(1, 1, 1), CVector3D(1, 1, 1));
	}
	CLight::SetAttenuation(1, 0.01f);
	CLight::SetRadiationAngle(1, view_angle);
	CLight::SetDir(1, eye_dir);
	CLight::SetPos(1, eye_pos);
}
void Whale::Move(CVector3D pos) {
	//������ւ̃x�N�g���Ɗp�x�����
	CVector3D Allive_vec = CVector3D((pos.x - m_pos.x), 160.0f - m_pos.y, (pos.z - m_pos.z)).GetNormalize();
	float Alive_rot = Utility::NormalizeAngle(std::atan2(Allive_vec.x, Allive_vec.z));
	//���݂̊p�x�ɁA��]�\�p�x�𑫂�
	//�E���ƍ����ǂ������߂����B�߂��ق��ŉ��
	float angleDifference = Alive_rot - m_rot.y;
	float shortestRotation = atan2(sin(angleDifference), cos(angleDifference));
	if (shortestRotation > 0) {
		m_rot.y += (RotationalSpeed < shortestRotation) ? RotationalSpeed : shortestRotation;
	}
	else if (shortestRotation < 0) {
		m_rot.y -= (RotationalSpeed < -shortestRotation) ? RotationalSpeed : -shortestRotation;
	}
	//�O�i����
	m_vec = CVector3D(sin(m_rot.y), 160.0f - m_pos.y, cos(m_rot.y)).GetNormalize();
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
void Whale::SearchAreaChange() {
	//��莞�Ԍo������ˌ�
	// �ˌ����͎��珄��H�֖߂�
	//�T�[�`�͈͂���O�ꂽ�炵�΂炭����������n���āA�͈͂ɓ���Ȃ���Ύ��_��߂����H��i��
}
CVector3D Whale::DestinationSelection() {
	/*CVector3D point_pos[] = {
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
	};*/
	if (Point_num >= MovePos_List.size()) {
		Point_num = 0;
	}
	CVector3D pos = MovePos_List.at(Point_num);
	if (pos.x - m_pos.x < 1.0f && pos.z - m_pos.z < 1.0f) {
		Point_num++;
	}
	return pos;
}
bool Whale::CheckPlayerInSearchRange(float View_Angle) {
	// �T�[�`�G���A�̊p�x�ƃv���C���[�̊p�x���r���Ĕ���
	//eye_pos = CMatrix::MTranselate(m_pos) * CMatrix::MRotation(m_rot) * CVector4D(0, -10, 20.0f, 1);
	//eye_dir = CMatrix::MRotation(DtoR(70), m_rot.y, 0).GetFront();
	CVector3D ep = PublicNum::Player_pos - eye_pos;
	float d = CVector3D::Dot(eye_dir, ep.GetNormalize());
	float angle = acos(d);

	// �T�[�`�͈͓��Ƀv���C���[������ꍇ��true��Ԃ�
	return angle <= View_Angle;
}