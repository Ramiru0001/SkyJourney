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
	static CMode c_mode;//�J�����̃��[�h
	//static DMode d_mode;//���O�I��or�I�t
	static bool log_passage;
	static bool log_pos;
	static int Feather_Count;//���H�̐�
	static int LightFeather_Count;//�g����H�̐�
};
class PublicFunction {
public:
};