#include "DesertStage.h"
DesertStage::DesertStage() :Task(ETaskPrio::eSystem, EType::eDefault) {
	Task::AddStage(new Desert());
	CVector3D FeatherPos[] = { 
		CVector3D(392.228f, 0.0718331f, -68.0385f),
		CVector3D(248.269, 28.2336, -58.8655),
		CVector3D(192.021, 27.9128, 149.475),
		CVector3D(79.5256, 0.071859, 44.1965),
		CVector3D(-79.4408, 41.0082, 97.8768),
		CVector3D(-195.595, 3.68223, 1.71687),
		CVector3D(-293.881, 0.0719438, -64.9238)
	};
	Task::AddFeathers(FeatherPos);
}
/*DesertSgate::~DesertSgate() {
	//コンストラクタで出したすべてを消す
	Task::DeleteAllStage();
}*/
