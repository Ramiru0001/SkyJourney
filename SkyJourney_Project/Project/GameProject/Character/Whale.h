#pragma once
class Whale :public Task{
private:
	int Point_num = 0;
	CVector2D m_vec2D;
	float ChaseSpeed = 0.02;
	float view_angle = DtoR(10.0f);
	float player_angle=0;
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
	void SearchAreaChange();
	void DrawCone(const GLfloat& radius, const GLfloat& height, const GLint& slices, const GLint& stacks);
	/*!
		@brief サーチとプレイヤーの間にオブジェクトがあるかどうかの判定
		@retval true:オブジェクト接触
	**/
	bool LightObjectPlayer();
	//目的地選択
	CVector3D DestinationSelection();
	CModel* GetModel();
	bool CheckPlayerInSearchRange(float View_Angle);
};

