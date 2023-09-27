#include "progress.h"
Progress::Progress():Task(ETaskPrio::eSystem, EType::eDefault) {
	ProgressChange();
}
void Progress::Update() {
	//�i����ς���g���K�[
	switch (prog_num) {
	case ProgressNum::eTytle:
	{
		if (PUSH(CInput::eButton1)) {
			prog_num = ProgressNum::eSkyIsland;
			ProgressChange();
		}
	}
	break;
	case ProgressNum::eSkyIsland:
		/*if (�X�e�[�W���N���A�����ꍇ) {
			delete SkyIslandStage;
		}*/
		break;
	}
}
void Progress::ProgressChange() {
	//�X�e�[�W���X�g�̃A�C�e�������ׂĔj�����āA�ύX��̐i���̃A�C�e����ǉ�
	Task::DeleteAllStage();
	switch (prog_num) {
	case ProgressNum::eTytle:
		Task::AddStage(new Title());
		break;
	case ProgressNum::eSkyIsland:
		if (PublicNum::Camera_On == false) {
			Task::Add(new Camera());
		}
		if (PublicNum::Player_On == false) {
			Task::Add(new Player(CVector3D(88.5f, 1.7f, 4.37f)));
		}
		SkyIsland* SkyIslandStage = new SkyIsland;
		break;
	}
}