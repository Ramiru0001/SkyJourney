#pragma once
//�i���̊Ǘ��A�Q�[���̎�Ȑi�s������N���X�ł���
class Progress :public Task{
private:
	enum ProgressNum {
	Tytle,
	SkyIsland,
	Desert,
	};
	/// <summary>
	/// �i���𐔎��ŊǗ��B�^�C�g����0�B�ŏ��̃X�e�[�W���P
	/// </summary>
	int prog_num;
public:
	Progress();
	int GetProgNum();
	void Update();
	/// <summary>
	/// �i�����ω������ꍇ�̂݌Ă΂��B
	/// �X�e�[�W���X�g�̃A�C�e�������ׂĔj�����āA�ύX��̐i���̃A�C�e����ǉ�
	/// </summary>
	void ProgressChange(int Progress);
};