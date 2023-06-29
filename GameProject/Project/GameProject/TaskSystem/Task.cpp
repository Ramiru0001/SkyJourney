#include "Task.h"
#include "TaskController.h"
Task::Task(int Prio):m_priority(Prio) {
	TaskManager::instance(AddTask());
}