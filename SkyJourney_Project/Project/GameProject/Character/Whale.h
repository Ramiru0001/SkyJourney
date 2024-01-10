#pragma once
class Whale :public Task{
	enum state {
		eGoAround,
		eChaseSearch,
		eAttack,
		eAfterAttack,
		eReturnToRoute,
	};
private:
	state StateNow;
	int SearchCount=0;
	int Point_num = 0;
	bool SearchFlag = false;
	float ChaseSpeed = 0.02;
	float view_angle = DtoR(10.0f);
	float player_angle=0;
	CVector2D m_vec2D;
	CVector3D WhaleRotationMatrix = CVector3D(0, 0, 0);
	CVector3D eye_pos;
	CVector3D eye_dir=(CVector3D(0,-1,0));
	std::vector<CVector3D> MovePos_List;
public:
	CModelA3M m_model;
	Whale(const std::vector<CVector3D>& MovePos);
	void Update();
	void Render();
	void Search();
	void Move(CVector3D pos);
	void Attack();
	void AfterAttack();
	void ReturnToRoute();
	void SearchAreaChange();
	void DrawCone(const GLfloat& radius, const GLfloat& height, const GLint& slices, const GLint& stacks);
	/*�T�[�`�ƃv���C���[�̊ԂɃI�u�W�F�N�g�����邩�ǂ����̔���
		true:�I�u�W�F�N�g�ڐG
	*/
	bool LightObjectPlayer();
	//�ړI�n�I��
	CVector3D DestinationSelection();
	CModel* GetModel();
	bool CheckPlayerInSearchRange(float View_Angle);
};

