#include "SkyIsland.h"
SkyIsland::SkyIsland():Task(ETaskPrio::eSystem, EType::eDefault) {
	Task::AddStage(new Feather(CVector3D(64.16f, 9.1f, 21.0f)));
	Task::AddStage(new Feather(CVector3D(74.16f, 1.09f, -14.4f)));
	Task::AddStage(new Feather(CVector3D(-16.0f, 14.3f, 27.4f)));
	Task::AddStage(new Candle(CVector3D(61.5f, 1.04f, 13.4f), DtoR(180)));
	Task::AddStage(new Candle(CVector3D(24.5f, -5.54f, 3.28f), DtoR(270)));
	Task::AddStage(new Candle(CVector3D(33.3f, 0.84f, -6.5f), DtoR(45)));
	Task::AddStage(new Candle(CVector3D(-15.49f, 8.07f, 1.24f), DtoR(135)));
	Task::AddStage(new Candle(CVector3D(-86.7567f, 16.7766f, 13.9631f), DtoR(90)));
	Task::AddStage(new Field());
}
SkyIsland::~SkyIsland() {
	//コンストラクタで出したすべてを消す
	Task::DeleteAllStage();
}
