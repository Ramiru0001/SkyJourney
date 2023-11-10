#pragma once
class Whale :public Task{
public:
	CModelA3M m_model;
	Whale(CVector3D& pos);
	void Update();
	void Render();
	void Search();
	void Move();
};

