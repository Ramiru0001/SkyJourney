#pragma once
class Feather :public Task {
private:
	/// <summary>
	/// �H�̐�
	/// </summary>
	int m_featherCount = 0;
public:
	CModelObj m_model;
public:
	Feather(CVector3D& pos);
	~Feather();
	void Render();
	void Update();
	bool GetCollision();
	void Collision(Task* a);
};
class Candle :public Task {
private:
	int recovery_count = 0;//�H�񕜂̂��߂̃J�E���g
public:
	CModelObj candle_model;
	CModelObj fire_model;
public:
	Candle(CVector3D& pos);
	~Candle();
	void Render();
	void Update();
	bool GetCollision();
	void Collision(Task* a);
};
