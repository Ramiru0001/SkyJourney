#include "Task.h"
Task::Task(int prio):m_Prio(prio) {

}
void Task::Add(Task* a) {
	for (auto& b : m_TaskList) {
		if (a->m_Prio <= b->m_Prio) {
			//m_TaskList.push
		}
	}
}
void Task::Render(){}
void Task::Update(){}
void Task::Collision(){}
void Task::SetKill() {
	m_kill = true;
}
void Task::RenderAll() {
	for (auto& b: m_TaskList){
		b->Render();
	}
}
void Task::UpdateAll() {
	for (auto& b : m_TaskList) {
		b->Update();
	}

}
void Task::CollisionAll() {

}
void Task::DeleteAll() {
	auto itr = m_TaskList.begin();
	//�����܂ŌJ��Ԃ�
	while (itr != m_TaskList.end()) {
		//�폜�`�F�b�N
		if ((*itr)->m_kill) {
			if (--(*itr)->m_kill == 0) {
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
bool Task::CheckKill() {
	if (m_kill = true) {
		return true;
	}
	else {
		return false;
	}
}