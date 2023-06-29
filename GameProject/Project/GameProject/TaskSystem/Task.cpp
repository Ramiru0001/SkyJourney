#include "Task.h"
#include "TaskController.h"
Task::Task(int prio=ETaskPrio::eTaskDefault) : m_prio(prio){

}
bool Task::GetKill() {
	return m_kill;
}