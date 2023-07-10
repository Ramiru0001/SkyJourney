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
	////末尾まで繰り返す
	//while (itr != m_TaskList.end()) {
	//	//削除チェック
	//	if ((*itr)->m_kill) {
	//		if (--(*itr)->m_kill == 0) {
	//			//削除
	//			delete* itr;
	//			//リストから除外する
	//			//次のオブジェクトを受け取る
	//			itr = m_TaskList.erase(itr);
	//			continue;
	//		}
	//	}
	//	//次のオブジェクト
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