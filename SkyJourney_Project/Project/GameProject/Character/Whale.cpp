#include "Whale.h"
Whale::Whale(const std::vector<CVector3D>& MovePos) :Task(ETaskPrio::eCharacter, EType::eCharacter) {
	//m_pos = pos;
	m_model= COPY_RESOURCE("Whale", CModelA3M);
	m_model.ChangeAnimation(0);
	m_pos = DEFAULT_POS;
	MovePos_List = MovePos;
	auto itr = MovePos_List.begin();
	StateNow = eGoAround;
}
void Whale::Update() {
	bool oldSearchFlag = SearchFlag;
	switch (StateNow) {
	case eGoAround:
	case eChaseSearch:
		//�v���C���[���T�[�`�̊O���ɂ���ꍇ
		if (!CheckPlayerInSearchRange(view_angle)) {
			// �v���C���[���T�[�`�͈͓��ɂ��Ȃ��ꍇ�͎���
			Move(DestinationSelection());
			SearchFlag = false;
			StateNow = eGoAround;
			std::cout << "�T�[�`�̊O" << std::endl;
		}
		else if (LightObjectPlayer()) {
			//�v���C���[�Ƃ̊Ԃɏ�Q��������ꍇ
			Move(DestinationSelection());
			SearchFlag = false;
			StateNow = eGoAround;
			std::cout << "�I�u�W�F�N�g����" << std::endl;
		}
		else {
			//�v���C���[���T�[�`���ɂ��āA��Q���ɂ�����Ă��Ȃ��ꍇ
			m_vec = CVector3D(0, 0, 0);
			SearchFlag = true;
			StateNow = eChaseSearch;
			if (PublicFunction::Observer(oldSearchFlag, SearchFlag)) {
				SearchCount = 0;
			}
			SearchCount++;
			std::cout << "�T�[�`��" << std::endl;
		}
		Search();
		break;
	case eAttack:
		std::cout << "Attack" << std::endl;
		Attack();
		break;
	case eAfterAttack:
		std::cout << "AfterAttack" << std::endl;
		AfterAttack();
		break;
	case eReturnToRoute:
		std::cout << "ReturnToRoute" << std::endl;
		ReturnToRoute();
		break;
	default:
		break;
	}
	// �ړ�����
	m_pos += m_vec;
	if (SearchCount >= 180) {
		StateNow = eAttack;
		SearchCount = 0;
	}
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
	if (CheckPlayerInSearchRange(view_angle)&& !LightObjectPlayer()) {
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
	//std::cout << "Dot : " << a << std::endl;
	//std::cout << "cos : " << cos(DtoR(60)) << std::endl;
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
	m_rot.z = 0;
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
bool Whale::LightObjectPlayer() {
	auto tri = m_model.CollisionRay(eye_pos, PublicNum::Player_pos);
	if (tri.empty()) {
		std::cout << "NoObject" << std::endl;
		return false;
	}
	return true;
}
void Whale::Attack() {
	//�����炪�L�����N�^�[�ɓˌ�����
	//�L�����N�^�[�̂ق��ɉ��~���ēˌ�
	//������ւ̃x�N�g���Ɗp�x�����
	m_vec = CVector3D((PublicNum::Player_pos.x - m_pos.x), PublicNum::Player_pos.y + 10.0f - m_pos.y, (PublicNum::Player_pos.z - m_pos.z)).GetNormalize()*2.0f;
	m_rot.y = Utility::NormalizeAngle(std::atan2(m_vec.x, m_vec.z));
	m_rot.z = m_vec.y;
	if ((m_pos - PublicNum::Player_pos).Length() <= 15.0f) {
		StateNow = eAfterAttack;
		PublicNum::WhaleAttack = true;
		PublicNum::WhaleVec = m_vec;
	}
}
void Whale::AfterAttack() {
	//�������̂܂܂ŁA�{���̍����܂ŏ㏸����
	m_vec = CVector3D(m_vec.x, 160.0f-m_vec.y, m_vec.z).GetNormalize() * 2.0f;
	m_rot.y = Utility::NormalizeAngle(std::atan2(m_vec.x, m_vec.z));
	m_rot.z = m_vec.y;
	if (m_pos.y >= 158.0f) {
		StateNow = eReturnToRoute;
	}
}
void Whale::ReturnToRoute(){
	//moveposlist����Ŋ��̂��̂�T���āA	pointnum���X�V�B���[�g�֖߂�
	int size=MovePos_List.size();
	float MinDistance = (MovePos_List.front() - m_pos).Length();
	int count = 0;
	Point_num = 0;
	for (auto b: MovePos_List) {
		float distance = (m_pos - b).Length();
		if (MinDistance > distance) {
			MinDistance = distance;
			Point_num = count;
		}
		count++;
	}
	StateNow = eGoAround;
}