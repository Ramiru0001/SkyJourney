#include "DesertStage.h"
DesertStage::DesertStage() :Task(ETaskPrio::eSystem, EType::eDefault) {
	Task::AddStage(new Desert());
	Task::AddStage(new Sandstorm());
	CVector3D FeatherPos[] = { 
		CVector3D(392.228f, 0.0718331f, -68.0385f),
		CVector3D(248.269, 28.2336, -58.8655),
		CVector3D(192.021, 27.9128, 149.475),
		CVector3D(79.5256, 0.071859, 44.1965),
		CVector3D(-79.4408, 41.0082, 97.8768),
		CVector3D(-195.595, 3.68223, 1.71687),
		CVector3D(-293.881, 0.0719438, -64.9238)
	};
	CVector3D CandlePos[] = {
		CVector3D(475.18,0.0718109,-28.576),
		CVector3D(475.193,0.0718034,5.33172),
		CVector3D(262.963,0.0718512,-54.8907),
		CVector3D(78.6782,0.0718598,41.3305),
		CVector3D(56.8937,0.0718684,18.4852),
		CVector3D(175.188,0.071826,123.236),
		CVector3D(-58.243,7.54926,91.2771),
		CVector3D(-296.984,0.0719346,-21.0482),
		CVector3D(-296.984,0.0719271,12.8827),
	};
	Task::AddFeathers(FeatherPos);
	Task::AddCandles(CandlePos);
	Task::AddStage(new Whale(/*CVector3D (0,0,180)*/));
}
/*DesertSgate::~DesertSgate() {
	//コンストラクタで出したすべてを消す
	Task::DeleteAllStage();
}*/
