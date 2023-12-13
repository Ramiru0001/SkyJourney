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
	CVector3D eye_dir;
public:
	CModelA3M m_model;
	Whale(/*CVector3D& pos*/);
	void Update();
	void Render();
	void Search();
	void Move(CVector3D pos);
	void SearchAreaChange();
	void DrawCone(const GLfloat& radius, const GLfloat& height, const GLint& slices, const GLint& stacks);
	//–Ú“I’n‘I‘ð
	CVector3D DestinationSelection();
	CModel* GetModel();
	bool CheckPlayerInSearchRange();
};

