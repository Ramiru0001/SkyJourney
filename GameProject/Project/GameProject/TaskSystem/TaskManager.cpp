#include "TaskManager.h"
TaskManager::TaskManager() :Task() {

	}
void TaskManager::AddTask(Task* b) {
	m_TaskList.push_back(b);
};
void TaskManager::DeleteTask(Task* b) {
	auto itr = m_TaskList.begin();
	//�����܂ŌJ��Ԃ�
	while (itr != m_TaskList.end()) {
		//�폜�`�F�b�N
		if ((*itr)->GetKill()) {
			//�폜
			delete* itr;
			//���X�g���珜�O����
			//���̃I�u�W�F�N�g���󂯎��
			itr = m_TaskList.erase(itr);
			continue;
		}
	}
		//���̃I�u�W�F�N�g
		itr++;
	}
}