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
	//末尾まで繰り返す
	while (itr != m_TaskList.end()) {
		//削除チェック
		if ((*itr)->m_kill) {
			if (--(*itr)->m_kill == 0) {
				//削除
				delete* itr;
				//リストから除外する
				//次のオブジェクトを受け取る
				itr = m_TaskList.erase(itr);
				continue;
			}
		}
		//次のオブジェクト
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