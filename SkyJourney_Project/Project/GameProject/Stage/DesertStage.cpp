#include "DesertStage.h"
DesertStage::DesertStage() :Task(ETaskPrio::eSystem, EType::eDefault) {
	Task::AddStage(new Desert());
}
/*DesertSgate::~DesertSgate() {
	//�R���X�g���N�^�ŏo�������ׂĂ�����
	Task::DeleteAllStage();
}*/
