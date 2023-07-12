#include "Task.h"
std::list<Task*> Task::m_TaskList;
Task::Task(ETaskPrio prio,EType type):m_prio(prio),m_type(type) {

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
void Task::Collision(Task* a){

}
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
	auto itr = m_TaskList.begin();
	//�����܂ŌJ��Ԃ�
	while (itr != m_TaskList.end()) {
		if (!(*itr)->m_kill) {
			auto ct = itr;
			ct++;
			while (ct != m_TaskList.end()) {
				if (!(*ct)->m_kill) {
					(*itr)->Collision(*ct);
					(*ct)->Collision(*itr);
				}
				//���̃I�u�W�F�N�g
				ct++;
			}
		}
		//���̃I�u�W�F�N�g
		itr++;
	}
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
Task::EType Task::GetType() {
	return m_type;
}
Task* Task::FindObject(EType type) {
	auto itr = m_TaskList.begin();
	while (itr != m_TaskList.end()) {
		if ((*itr)->GetType() == type) {
			return *itr;
		}
		itr++;
	}
	return nullptr;
}
CModel* Task::GetModel() {
	return nullptr;
}