#pragma once
#include "Task.h"
std::list<Task*> m_TaskList;
class TaskManager :Task {
public:
	TaskManager();
	/// <summary>
	/// �^�X�N���X�g�ɒǉ�
	/// </summary>
	/// <param name="b">new�C���X�^���X���^�X�N�|�C���^�œ����</param>
	virtual void AddTask(Task* b);
	virtual void DeleteTask(Task* b);
};