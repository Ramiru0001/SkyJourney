#include "VolcanoStage.h"
VolcanoStage::VolcanoStage() :Task(ETaskPrio::eSystem, EType::eDefault) {
	Task::AddStage(new Volcano());
	std::vector<CVector3D> CandleList={
	//CVector3D CandlePos[] = {
		CVector3D(146.191,120.846,27.3618),
		CVector3D(141.549,120.078,68.3823),
		CVector3D(168.482,84.9726,126.94),
		CVector3D(216.221,61.7886,144.632),
		CVector3D(256.541,36.9894,180.204),
		CVector3D(272.364,19.2575,236.931),
		//CVector3D(253.677,12.2069,291.694),
		CVector3D(228.299,14.637,312.346),
		CVector3D(187.435,28.5426,280.523),
		//CVector3D(134.182,40.8479,275.518),
		CVector3D(99.4131,49.4537,277.735),
		CVector3D(58.9898,44.2527,284.726),
		CVector3D(21.1724,54.7195,259.829),
		//CVector3D(-32.2519,56.8449,299.885),
		CVector3D(-52.0446,55.2062,323.495),
		CVector3D(-76.2635,11.738,403.3),
		CVector3D(-175.969,-19.1057,476.701),
		CVector3D(-253.95,-6.98137,356.171),
		CVector3D(-346.912,-11.3348,293.471),
		CVector3D(-344.49,15.6943,179.993),
		CVector3D(-313.783,42.1727,8.07392),
		CVector3D(-382.775,10.3933,-106.206),
		CVector3D(-324.112,3.07366,-250.247),
		CVector3D(-288.259,66.7533,75.2896),
		CVector3D(- 287.356,66.1894,113.983),
	};
	Task::AddCandles(CandleList);
}