#include "VolcanoStage.h"
VolcanoStage::VolcanoStage() :Task(ETaskPrio::eSystem, EType::eDefault) {
	Task::AddStage(new Volcano());
}