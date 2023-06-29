#include "TaskManager.h"
TaskManager* TaskManager::mn_instance = nullptr;
TaskManager::TaskManager() {

}
TaskManager::~TaskManager() {
	for (int i = 0; i < m_TaskList.size(); i++) {
		Task* Task = m_TaskList[i];
		delete Task;
	}
}
void TaskManager::AddTask() {
	m_TaskList.push_back();
}
void TaskManager::RemoveTask() {/*
	std::list <Task*>::iterator it = std::find(m_TaskList.begin(), m_TaskList.end(), p_task);
	if (it != m_TaskList.end()) {
		delete* it;
		m_TaskList.erase(it);
	}*/
}
void TaskManager::Update(void) {
	for (std::list<Task*>::iterator it = m_TaskList.begin(); it != m_TaskList.end(); ++it) {
		Task* p_task = *it;
		p_task->Update();
	}
}
void TaskManager::Draw(void) {/*
	for (std::list<Task*>::iterator it = m_TaskList.begin(); it != m_TaskList.end(); ++it) {
		Task* p_task = *it;
		p_task->Draw();
	}*/
}