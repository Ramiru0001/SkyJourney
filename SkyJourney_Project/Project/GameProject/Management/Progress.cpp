#include "progress.h"
Progress::Progress():Task(ETaskPrio::eSystem, EType::eDefault) {
}
void Progress::Update() {
	switch (prog_num) {
	case ProgressNum::eTytle:
	{
		Title* TitleStage = new Title;
		if (PUSH(CInput::eButton1)) {
			delete TitleStage;
			prog_num = ProgressNum::eSkyIsland;
		}
	}
		break;
	case ProgressNum::eSkyIsland:
		Task::Add(new Player(CVector3D(88.5f, 1.7f, 4.37f)));
		Task::Add(new Camera());
		SkyIsland* SkyIslandStage = new SkyIsland;
		/*if (ステージをクリアした場合) {
			delete SkyIslandStage;
		}*/
		break;
	}
}