#include "progress.h"
Progress::Progress():Task(ETaskPrio::eSystem, EType::eDefault) {
	ProgressChange(prog_num = ProgressNum::eTytle);
}
void Progress::Update() {
	//進捗を変えるトリガー
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
		/*if (ステージをクリアした場合) {
			delete SkyIslandStage;
		}*/
		break;
	}
}
void Progress::ProgressChange(int Progress) {
	//ステージリストのアイテムをすべて破棄して、変更後の進捗のアイテムを追加
	Task::DeleteAllStage();
	switch (Progress) {
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