#include "TaskManager.h"
TaskManager::TaskManager() :Task() {

	}
void TaskManager::AddTask(Task* b) {
	m_TaskList.push_back(b);
};
void TaskManager::DeleteAll() {
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
void TaskManager::RenderAll() {
	for (auto& b : m_TaskList) {
		b->Render();
	}
}
void TaskManager::UpdateAll() {
	for (auto& b : m_TaskList) {
		b->Update();
	}
}
void TaskManager::CollisionAll() {
	for (auto& b : m_TaskList) {
		//b->Collision();
	}
}
void TaskManager::SetKillAll() {
	for (auto& b : m_TaskList) {
		b->SetKill();
	}
}