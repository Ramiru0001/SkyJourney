#pragma once
#include "Task.h"
std::list<Task*> m_TaskList;
class TaskManager :Task {
public:
	TaskManager();
	/// <summary>
	/// タスクリストに追加
	/// </summary>
	/// <param name="b">newインスタンスをタスクポインタで入れる</param>
	virtual void AddTask(Task* b);
	virtual void DeleteTask(Task* b);
};