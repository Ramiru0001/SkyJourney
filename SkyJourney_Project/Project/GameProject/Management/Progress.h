#pragma once
//�i���̊Ǘ��A�Q�[���̎�Ȑi�s������N���X�ł���
class Progress :public Task{
private:
	enum ProgressNum {
		Tytle,
		SkyIsland,
		Desert,
		Volcano,
		Ending,
	};
	/// <summary>
	/// �i���𐔎��ŊǗ��B�^�C�g����0�B�ŏ��̃X�e�[�W���P
	/// </summary>
	int Whiteout_count;
	bool Whiteout_flag_old=false;
	int prog_num;
	bool TimerOn;
public:
	Progress();
	int GetProgNum();
	void Update();
	/// <summary>
	/// �i�����ω������ꍇ�̂݌Ă΂��B
	/// �X�e�[�W���X�g�̃A�C�e�������ׂĔj�����āA�ύX��̐i���̃A�C�e����ǉ�
	/// </summary>
	void ProgressChange(int Progress);
	//�X�e�[�W�`�F���W�̃^�C�}�[�B�`�F���W���鎞��true
	void TimerStart();
	bool StageChangeTimer(bool);
	//bool WhiteoutFinishTrigger();
};