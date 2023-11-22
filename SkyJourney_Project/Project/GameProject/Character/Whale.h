#pragma once
class Whale :public Task{
private:
	int Point_num = 0;
	CVector2D m_vec2D;
public:
	CModelA3M m_model;
	Whale(/*CVector3D& pos*/);
	void Update();
	void Render();
	void Search();
	void Move();
	void DrawCone(const GLfloat& radius, const GLfloat& height, const GLint& slices, const GLint& stacks);
	CModel* GetModel();
};

