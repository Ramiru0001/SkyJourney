#pragma once
class Player :public Task {
public:
	CModelA3M m_model;
public:
	Player(CVector3D &pos);
	void Render();
	void Update();
};