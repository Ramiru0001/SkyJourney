#pragma once
class Player :public Task {
public:
	CModelA3M m_model;
	float move_speed = 0.1f;
	float fly_speed = 0.15f;
public:
	bool OnGround = true;;
	Player(CVector3D &pos);
	void Render();
	void Update();
	void Collision(Task* a);
	CModel* GetModel();
};