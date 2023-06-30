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
	/// <summary>
	/// ���ׂĂ�kill�t���O��true�ɂ���
	/// </summary>
	virtual void SetKillAll();
	/// <summary>
	/// kill�t���O��true�̏ꍇ�폜
	/// </summary>
	static void DeleteAll();
	/// <summary>
	/// ���ׂĉ�ʂɕ\��
	/// </summary>
	static void RenderAll();
	/// <summary>
	/// ���ׂ�Update
	/// </summary>
	static void UpdateAll();
	/// <summary>
	/// ���ׂĂ̓����蔻��̏���������
	/// </summary>
	static void CollisionAll();
};