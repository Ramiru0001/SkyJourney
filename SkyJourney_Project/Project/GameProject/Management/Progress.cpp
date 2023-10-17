#include "progress.h"
#include "../Stage/SkyIslandStage.h"
#include "../Stage/DesertStage.h"
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
	//ステージリストのアイテムをすべて破棄して、変更後の進捗のアイテムを追加
	Task::DeleteAllStage();
	switch (Progress) {
	case ProgressNum::eTytle:
		//１つしかないので、stageを作らずに直接追加
		Task::AddStage(new Title());
		break;
	case ProgressNum::eSkyIsland:
		//カメラがない場合、召喚
		if (PublicNum::Camera_On == false) {
			Task::Add(new Camera());
		}
		//プレイヤーがいない場合召喚
		if (PublicNum::Player_On == false) {
			Task::Add(new Player(CVector3D(468.5f, 0.07f, -11.7f)));
		}
		{
			//SkyIslandStageのコンストラクタを呼んでstageタスクリストに追加
			SkyIslandStage* SkyIslandStage_Instance = new SkyIslandStage;
			//呼んだクラスは必要ないので即破棄
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
			//DesertStageのコンストラクタを呼んでstageタスクリストに追加
			DesertStage* DesertStage_Instance = new DesertStage;
			//呼んだクラスは必要ないので即破棄
			delete DesertStage_Instance; 
		}
		break;
	}
}