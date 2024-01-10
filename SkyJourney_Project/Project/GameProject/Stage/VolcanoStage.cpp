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
	std::vector<CVector3D> WhalePoslist = {
		CVector3D(420.124,90.5641,-196.478),
		CVector3D(338.392,90.5641,-338.073),
		CVector3D(209.375,90.5641,-404.957),
		CVector3D(-55.065,71.5641,-392.891),
		CVector3D(-250.93,72.0641,-409.96),
		CVector3D(-332.751,84.0641,-285.898),
		CVector3D(-394.88,59.5641,-185.572),
		CVector3D(-388.091,119.064,-52.0549),
		CVector3D(-408.449,87.0641,119.092),
		CVector3D(-348.671,101.064,205.243),
		CVector3D(-333.03,83.0641,345.425),
		CVector3D(-202.04,68.5641,423.033),
		CVector3D(-54.6453,139.564,367.798),
		CVector3D(64.686,145.564,352.254),
		CVector3D(259.505,123.564,315.348),
		CVector3D(436.49,138.564,178.923),
		CVector3D(422.397,118.564,22.5089),
		CVector3D(441.887,104.064,-124.237),
	};
	Task::AddStage(new Whale(WhalePoslist));
};