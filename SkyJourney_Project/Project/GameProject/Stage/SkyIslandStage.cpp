#include "SkyIslandStage.h"
SkyIslandStage::SkyIslandStage():Task(ETaskPrio::eSystem, EType::eDefault) {
	Task::AddStage(new SkyIsland()); 
	CVector3D FeatherPos[] = {
		CVector3D(64.16f, 9.1f, 21.0f),
		CVector3D(74.16f, 1.09f, -14.4f),
		CVector3D(-16.0f, 14.3f, 27.4f)
	};
	CVector3D CandlePos[] = {
		CVector3D(-86.7567f, 16.7766f, 13.9631f),
		CVector3D(-15.49f, 8.07f, 1.24f),
		CVector3D(33.3f, 0.84f, -6.5f),
		CVector3D(24.5f, -5.54f, 3.28f),
		CVector3D(61.5f, 1.04f, 13.4f)
	};
	Task::AddFeathers(FeatherPos);
	Task::AddCandles(CandlePos);
}
/*SkyIsland::~SkyIsland() {
	//コンストラクタで出したすべてを消す
	Task::DeleteAllStage();
}*/
