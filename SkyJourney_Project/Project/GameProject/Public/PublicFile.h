#pragma once
#define RotationalSpeed DtoR(1.0f)
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
		Volcano,
	};
	static bool Player_On;//�v���C���[�����邩���Ȃ����B������true
	static bool Camera_On;//�J���������邩�Ȃ����B��������true
	static CMode c_mode;//�J�����̃��[�h
	//static DMode d_mode;//���O�I��or�I�t
	static bool Log_passage;
	static bool Log_pos;
	static bool Whiteout_flag;//true�ɂȂ�����z���C�g�A�E�g����
	static bool Stage_Change;//�ʏ��false�Bstage���ς��������true�ɂȂ�B
	static bool Debug_mode;
	static bool stage_change_flag;//stageChange������z���C�g�A�E�g�̂Ƃ���on
	static bool WhaleAttack;//�����炳�񂪃A�^�b�N������true;
	static int Feather_Count;//���H�̐�
	static int LightFeather_Count;//�g����H�̐�
	static int Stage_Num;//���݂̃X�e�[�Wnumber
	static int MaxWhite_Count;//�z���C�g�A�E�g�̎���
	static int FeatherDetail_Count;//�H�̏ڍׂȐ���
	static int FeatherDetail_CountMax;//�H�̏ڍׂȐ����̍ő�l
	static CVector3D Player_pos;
	static CVector3D Camera_pos;
	static CVector3D Camera_rot;
	static CVector3D WhaleVec;
};
class PublicFunction {
public:
	/// <summary>
	/// �ȑO�̒l�ƍ��̒l���ׂđ����Ă�����true�B����ȊO��false
	/// </summary>
	/// <returns></returns>
	static bool Observer(int old,int now);
	static CVector3D DoubleToVector3D(double[]);
};