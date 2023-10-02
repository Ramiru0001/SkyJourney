#pragma once
class Player :public Task {
	enum {
		Idle,
		Walk,
		Fly,
		Jump,
	};
private:
	int state = 0;//Idle=0,Walk=1,Fly=2
	int space_count=0;//スペースキーを押してる時間をカウント
	CImage mant_DesignLight;//明るいマントの模様
	CImage mant_DesignDark;//暗いマントの模様
	CTextureFrame* texture_frame_rader;
public:
	CModelA3M m_model;
	float move_speed = 0.13f;
	float fly_speed = 0.15f;
	float jump_speed = 0.15f;
public:
	bool OnGround = true;
	Player(CVector3D &pos);
	~Player();
	void FeatherRender(int Count,int LightCount);
	void Render();
	void Update();
	void Collision(Task* a);
	CModel* GetModel();
};