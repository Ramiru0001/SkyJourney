#pragma once
//�i���̊Ǘ��A�Q�[���̎�Ȑi�s������N���X�ł���
class Progress :public Task{
private:
	enum ProgressNum{
		eTytle,
		eSkyIsland,
	};
	/// <summary>
	/// �i���𐔎��ŊǗ��B�^�C�g����0�B�ŏ��̃X�e�[�W���P
	/// </summary>
	int prog_num = ProgressNum::eTytle;
public:
	Progress();
	void Update();
	/// <summary>
	/// �i�����ω������ꍇ�̂݌Ă΂��
	/// </summary>
	void ProgressChange(int Progress);
};