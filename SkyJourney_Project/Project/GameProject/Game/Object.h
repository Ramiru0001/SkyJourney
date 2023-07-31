#pragma once
class Feather :public Task {
private:
	/// <summary>
	/// ‰H‚Ì”
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
