#include "Task.h"
std::list<Task*> Task::m_TaskList;
Task::Task(ETaskPrio prio):m_prio(prio) {

}
void Task::Add(Task* a) {
	auto itr = m_TaskList.begin();
	while (itr != m_TaskList.end()){
		if ((*itr)->GetPrio() >= a->GetPrio()) {
			m_TaskList.insert(itr, a);
			return;
		}
		itr++;
	}
	m_TaskList.push_front(a);
}
void Task::Render(){}
void Task::Update(){}
void Task::Collision(){}
void Task::SetKill() {
	m_kill = true;
}
void Task::RenderAll() {
	for (auto& b : m_TaskList){
		b->Render();
	}
}
void Task::UpdateAll(){
	for (auto& b : m_TaskList) {
		b->Update();
	}
	//std::cout << Task::m_TaskList.size() << std::endl;
}
void Task::CollisionAll() {

}
void Task::DeleteAll() {
	//auto itr = m_TaskList.begin();
	////�����܂ŌJ��Ԃ�
	//while (itr != m_TaskList.end()) {
	//	//�폜�`�F�b�N
	//	if ((*itr)->m_kill) {
	//		if (--(*itr)->m_kill == 0) {
	//			//�폜
	//			delete* itr;
	//			//���X�g���珜�O����
	//			//���̃I�u�W�F�N�g���󂯎��
	//			itr = m_TaskList.erase(itr);
	//			continue;
	//		}
	//	}
	//	//���̃I�u�W�F�N�g
	//	itr++;
	//}
}
bool Task::CheckKill() {
	if (m_kill = true) {
		return true;
	}
	else {
		return false;
	}
}
ETaskPrio Task::GetPrio() {
	return m_prio;
}
Task* Task::FindObject(ETaskPrio prio) {
	auto itr = m_TaskList.begin();
	while (itr != m_TaskList.end()) {
		if ((*itr)->GetPrio() == prio) {
			return *itr;
		}
		itr++;
	}
	return nullptr;
}