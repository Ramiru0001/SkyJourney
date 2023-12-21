#include "progress.h"
#include "../Stage/SkyIslandStage.h"
#include "../Stage/DesertStage.h"
#include "../Stage/VolcanoStage.h"
Progress::Progress():Task(ETaskPrio::eSystem, EType::eDefault) {
	ProgressChange(prog_num = ProgressNum::Tytle);
	prog_num = ProgressNum::Tytle;
}
void Progress::Update() {
	if (PublicFunction::Observer(Whiteout_flag_old, PublicNum::Whiteout_flag) && PublicNum::stage_change_flag) {
		Task::Add(new Whiteout);
		TimerStart();
		PublicNum::stage_change_flag = false;
	}
	Whiteout_flag_old = PublicNum::Whiteout_flag;
	PublicNum::Stage_Change=StageChangeTimer(TimerOn);
	//進捗を変えるトリガー
	switch (prog_num) {
	case ProgressNum::Tytle:
	{
		if (PUSH(CInput::eButton1)) {
			prog_num = ProgressNum::Desert;
			PublicNum::Stage_Num=PublicNum::StageNum::Volcano;
			ProgressChange(prog_num);
		}
	}
	break;
	case ProgressNum::SkyIsland:
		if (PublicNum::Stage_Change) {
			prog_num = ProgressNum::Desert;
			PublicNum::Stage_Num = PublicNum::StageNum::Desert;
			ProgressChange(prog_num);
		}
		break;
	case ProgressNum::Desert:
		if (PublicNum::Stage_Change) {
			prog_num = ProgressNum::Volcano;
			PublicNum::Stage_Num = PublicNum::StageNum::Volcano;
			ProgressChange(prog_num);
		}
		break;
	}
}
void Progress::ProgressChange(int Progress) {
	Task::DeleteAllStage();
	switch (Progress) {
	case ProgressNum::Tytle:
		//１つしかないので、stageを作らずに直接追加
		Task::AddStage(new Title());
		break;
	case ProgressNum::SkyIsland:
		//カメラがない場合、召喚
		if (PublicNum::Camera_On == false) {
			Task::Add(new Camera());
		}
		//プレイヤーがいない場合召喚
		if (PublicNum::Player_On == false) {
			Task::Add(new Player(CVector3D(88.5f, 1.7f, 4.37f)));
		}
		Task::Add(new SkyBox());
		Task::AddStage(new Whiteout());
		{
			//SkyIslandStageのコンストラクタを呼んでstageタスクリストに追加
			SkyIslandStage* SkyIslandStage_Instance = new SkyIslandStage;
			//呼んだクラスは必要ないので即破棄
			delete SkyIslandStage_Instance;
		}
		Task::Add(new UI);
		break;
	case ProgressNum::Desert:
		if (PublicNum::Camera_On == false) {
			Task::Add(new Camera());
		}
		if (PublicNum::Player_On == false) {
			Task::Add(new Player(CVector3D(468.5f, 0.07f, -11.7f)));
		}
		{
			//DesertStageのコンストラクタを呼んでstageタスクリストに追加
			DesertStage* DesertStage_Instance = new DesertStage;
			//呼んだクラスは必要ないので即破棄
			delete DesertStage_Instance; 
		}
		break;
	case ProgressNum::Volcano:
		if (PublicNum::Camera_On == false) {
			Task::Add(new Camera());
		}
		if (PublicNum::Player_On == false) {
			Task::Add(new Player(CVector3D(468.5f, 0.07f, -11.7f)));
		}
		//Task::Add(new SkyBox());
		{
			//VolcanoStageのコンストラクタを呼んでstageタスクリストに追加
			VolcanoStage* VolcanoStage_Instance = new VolcanoStage;
			//呼んだクラスは必要ないので即破棄
			delete VolcanoStage_Instance;
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