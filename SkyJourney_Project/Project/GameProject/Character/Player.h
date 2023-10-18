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
	CVector3D Stage_Pos[5];
	CVector3D SkyIslandPos = CVector3D(88.5f, 1.7f, 4.37f);
	CVector3D DesertPos = CVector3D(468.5f, 0.07f, -11.7f);

public:
	CModelA3M m_model;
	float move_speed = 0.13f;
	float fly_speed = 0.15f;
	float jump_speed = 0.15f;
public:
	bool OnGround = true;
	Player(CVector3D &pos);
	~Player();
	/// <summary>
	/// 羽を配置する。
	/// </summary>
	/// <param name="Count">羽の数</param>
	/// <param name="LightCount">使用できる羽の数</param>
	void FeatherSetPos(int Count,int LightCount);
	/// <summary>
	/// 羽をマントに描画する。
	/// </summary>
	void FeatherDraw();
	void Render();
	void Update();
	void Collision(Task* a);
	void Move();
	CModel* GetModel();
};