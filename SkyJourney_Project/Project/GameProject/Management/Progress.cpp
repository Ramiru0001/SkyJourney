#include "progress.h"
#include "../Stage/SkyIslandStage.h"
#include "../Stage/DesertStage.h"
Progress::Progress():Task(ETaskPrio::eSystem, EType::eDefault) {
	ProgressChange(prog_num = ProgressNum::eTytle);
}
void Progress::Update() {
	//�i����ς���g���K�[
	switch (prog_num) {
	case ProgressNum::eTytle:
	{
		if (PUSH(CInput::eButton1)) {
			prog_num = ProgressNum::eSkyIsland;
			ProgressChange(prog_num);
		}
	}
	break;
	case ProgressNum::eSkyIsland:
		/*if (�X�e�[�W���N���A�����ꍇ) {
			prog_num = ProgressNum::eDesert;
			ProgressChange(prog_num);
		}*/
		if (PUSH(CInput::eButton1)) {
			prog_num = ProgressNum::eDesert;
			ProgressChange(prog_num);
		}
		break;
	case ProgressNum::eDesert:
		break;
	}
}
void Progress::ProgressChange(int Progress) {
	//�X�e�[�W���X�g�̃A�C�e�������ׂĔj�����āA�ύX��̐i���̃A�C�e����ǉ�
	Task::DeleteAllStage();
	switch (Progress) {
	case ProgressNum::eTytle:
		//�P�����Ȃ��̂ŁAstage����炸�ɒ��ڒǉ�
		Task::AddStage(new Title());
		break;
	case ProgressNum::eSkyIsland:
		//�J�������Ȃ��ꍇ�A����
		if (PublicNum::Camera_On == false) {
			Task::Add(new Camera());
		}
		//�v���C���[�����Ȃ��ꍇ����
		if (PublicNum::Player_On == false) {
			Task::Add(new Player(CVector3D(468.5f, 0.07f, -11.7f)));
		}
		{
			//SkyIslandStage�̃R���X�g���N�^���Ă��stage�^�X�N���X�g�ɒǉ�
			SkyIslandStage* SkyIslandStage_Instance = new SkyIslandStage;
			//�Ă񂾃N���X�͕K�v�Ȃ��̂ő��j��
			delete SkyIslandStage_Instance;
		}
		break;
	case ProgressNum::eDesert:
		if (PublicNum::Camera_On == false) {
			Task::Add(new Camera());
		}
		if (PublicNum::Player_On == false) {
			Task::Add(new Player(CVector3D(88.5f, 1.7f, 4.37f)));
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