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
	int space_count=0;//�X�y�[�X�L�[�������Ă鎞�Ԃ��J�E���g
	CImage mant_DesignLight;//���邢�}���g�̖͗l
	CImage mant_DesignDark;//�Â��}���g�̖͗l
	CTextureFrame* texture_frame_rader;
	CVector3D Stage_Pos[5];
	CVector3D SkyIslandPos = CVector3D(88.5f, 1.7f, 4.37f);
	CVector3D DesertPos = CVector3D(468.5f, 0.07f, -11.7f);
	CVector3D VolcanoPos = CVector3D(-334.372, 3.34898, -260.065);
	CVector3D Goalpos = CVector3D(146.191, 120.846, 27.3618);
public:
	CModelA3M m_model;
	float debug_speed = 0.5f;
	float move_speed = 0.2f;
	float fly_speed = 0.25f;
	float jump_speed = 0.21f;
	bool return_whiteout_flag=false;
	bool OnGround = true;
	int whiteout_count = 0;
	bool Whale_attack_now=false;
public:
	Player(CVector3D &pos);
	~Player();
	/// <summary>
	/// �H��z�u����B
	/// </summary>
	/// <param name="Count">�H�̐�</param>
	/// <param name="LightCount">�g�p�ł���H�̐�</param>
	void FeatherSetDraw(int Count,int LightCount);
	/// <summary>
	/// �H���}���g�ɕ`�悷��B
	/// </summary>
	void FeatherDraw();
	void Render();
	void Update();
	void Collision(Task* a);
	void Move();
	void DebugMove();//debugmode�̈ړ�����
	/// <summary>
	/// �}�b�v�`�F���W������G���A�ɓ�������true
	/// </summary>
	bool MapChangeCheck();
	void Return_Whiteout();
	void AttackMove();
	CModel* GetModel();
};