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
	static DMode d_mode;//���O�I��or�I�t
};
class PublicFunction {
public:
};