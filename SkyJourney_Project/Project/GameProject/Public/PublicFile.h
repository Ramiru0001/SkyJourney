#pragma once
class PublicNum {
public:
	enum CMode {
		FixedPoint,//�Œ�J����
		WithPlayer,//�v���C���[�̌��
	};
	enum DMode {
		LogOn,
		LogOff,
	};
	enum StageNum {
		Tytle,
		SkyIsland,
		Desert,
	};
	static bool Player_On;//�v���C���[�����邩���Ȃ����B������true
	static bool Camera_On;//�J���������邩�Ȃ����B��������true
	static CMode c_mode;//�J�����̃��[�h
	//static DMode d_mode;//���O�I��or�I�t
	static bool log_passage;
	static bool log_pos;
	static bool Whiteout_flag;//true�ɂȂ�����z���C�g�A�E�g����
	static bool Stage_Change;//�ʏ��false�Bstage���ς��������true�ɂȂ�B
	static bool Debug_mode;
	static int Feather_Count;//���H�̐�
	static int LightFeather_Count;//�g����H�̐�
	static int Stage_Num;//���݂̃X�e�[�Wnumber
	static CVector3D Player_pos;
	static CVector3D Camera_rot;
};
class PublicFunction {
public:
};