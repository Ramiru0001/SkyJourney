#pragma once
class Feather :public Task {
private:
	/// <summary>
	/// âHÇÃêî
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
public:
	CModelObj candle_model;
	CModelObj fire_model;
public:
	Candle(const CVector3D& pos);
	~Candle();
	void Render();
	void Update();
	bool GetCollision();
	void Collision(Task* a);
};
class Signpost :public Task {
public:
	CModelObj Signpost_model;
public:
	Signpost(const CVector3D& pos);
	~Signpost();
	void Render();
	void Update();
	bool GetCollision();
	void Collision(Task* a);
};
