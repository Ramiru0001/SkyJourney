#include "Task.h"
#include "TaskManager.h"
Task::Task(int prio=ETaskPrio::eTaskDefault) : m_prio(prio){

}
bool Task::GetKill() {
	return m_kill;
}
void Task::Render(){}
void Task::Update(){}
void Task::SetKill() {
	m_kill = true;
}
void Task::Collision(Task* b) {

}