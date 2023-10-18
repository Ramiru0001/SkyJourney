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
	/// �H��z�u����B
	/// </summary>
	/// <param name="Count">�H�̐�</param>
	/// <param name="LightCount">�g�p�ł���H�̐�</param>
	void FeatherSetPos(int Count,int LightCount);
	/// <summary>
	/// �H���}���g�ɕ`�悷��B
	/// </summary>
	void FeatherDraw();
	void Render();
	void Update();
	void Collision(Task* a);
	void Move();
	CModel* GetModel();
};