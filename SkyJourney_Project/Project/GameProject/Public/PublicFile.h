#pragma once
class PublicNum {
public:
	enum CMode {
		FixedPoint,//�Œ�J����
		WithPlayer,//�v���C���[�̌��
	};
	static CMode c_mode;//�J�����̃��[�h
};