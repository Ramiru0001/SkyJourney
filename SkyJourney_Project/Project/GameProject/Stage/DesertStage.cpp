#include "DesertStage.h"
DesertStage::DesertStage() :Task(ETaskPrio::eSystem, EType::eDefault) {
	Task::AddStage(new Desert());
}
/*DesertSgate::~DesertSgate() {
	//コンストラクタで出したすべてを消す
	Task::DeleteAllStage();
}*/
