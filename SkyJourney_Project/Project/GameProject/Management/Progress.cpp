#include "progress.h"
#include "../Stage/SkyIslandStage.h"
#include "../Stage/DesertStage.h"
Progress::Progress():Task(ETaskPrio::eSystem, EType::eDefault) {
	ProgressChange(prog_num = ProgressNum::Tytle);
	prog_num = ProgressNum::Tytle;
}
void Progress::Update() {
	//std::cout << "Update" << std::endl;
	if (PublicFunction::Observer(Whiteout_flag_old,PublicNum::Whiteout_flag)) {
		Task::Add(new Whiteout);
		TimerStart();
		std::cout << "TimeStart" << std::endl;
	}
	Whiteout_flag_old = PublicNum::Whiteout_flag;
	PublicNum::Stage_Change=StageChangeTimer(TimerOn);
	//�i����ς���g���K�[
	switch (prog_num) {
	case ProgressNum::Tytle:
	{
		if (PUSH(CInput::eButton1)) {
			prog_num = ProgressNum::SkyIsland;
			PublicNum::Stage_Num=PublicNum::StageNum::SkyIsland;
			ProgressChange(prog_num);
		}
	}
	break;
	case ProgressNum::SkyIsland:
		/*if (�X�e�[�W���N���A�����ꍇ) {
			prog_num = ProgressNum::eDesert;
			ProgressChange(prog_num);
		}*/
		if (PublicNum::Stage_Change) {
			prog_num = ProgressNum::Desert;
			PublicNum::Stage_Num = PublicNum::StageNum::Desert;
			ProgressChange(prog_num);
		}
		break;
	case ProgressNum::Desert:
		break;
	}
}
void Progress::ProgressChange(int Progress) {
	//�X�e�[�W���X�g�̃A�C�e�������ׂĔj�����āA�ύX��̐i���̃A�C�e����ǉ�
	std::cout << "ProgressChange" << std::endl;
	Task::DeleteAllStage();
	switch (Progress) {
	case ProgressNum::Tytle:
		//�P�����Ȃ��̂ŁAstage����炸�ɒ��ڒǉ�
		Task::AddStage(new Title());
		break;
	case ProgressNum::SkyIsland:
		std::cout << "SkyIsland�����I" << std::endl;
		//�J�������Ȃ��ꍇ�A����
		if (PublicNum::Camera_On == false) {
			Task::Add(new Camera());
		}
		//�v���C���[�����Ȃ��ꍇ����
		if (PublicNum::Player_On == false) {
			Task::Add(new Player(CVector3D(88.5f, 1.7f, 4.37f)));
		}
		Task::AddStage(new Whiteout());
		{
			//SkyIslandStage�̃R���X�g���N�^���Ă��stage�^�X�N���X�g�ɒǉ�
			SkyIslandStage* SkyIslandStage_Instance = new SkyIslandStage;
			//�Ă񂾃N���X�͕K�v�Ȃ��̂ő��j��
			delete SkyIslandStage_Instance;
		}
		break;
	case ProgressNum::Desert:
		std::cout << "Desert�����I" << std::endl;
		if (PublicNum::Camera_On == false) {
			Task::Add(new Camera());
		}
		if (PublicNum::Player_On == false) {
			Task::Add(new Player(CVector3D(468.5f, 0.07f, -11.7f)));
		}
		{
			//DesertStage�̃R���X�g���N�^���Ă��stage�^�X�N���X�g�ɒǉ�
			DesertStage* DesertStage_Instance = new DesertStage;
			//�Ă񂾃N���X�͕K�v�Ȃ��̂ő��j��
			delete DesertStage_Instance; 
		}
		break;
	}
}
int Progress::GetProgNum() {
	return prog_num;
}
void Progress::TimerStart() {
	TimerOn = true;
	Whiteout_count = 0;
}
bool Progress::StageChangeTimer(bool Timer_flag) {
	if (!Timer_flag)return false;
	Whiteout_count++;
	if (Whiteout_count == PublicNum::MaxWhite_Count / 2) {
		return true;
	}
	return false;
}