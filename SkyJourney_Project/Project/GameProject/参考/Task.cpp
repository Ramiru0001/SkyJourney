#include "Task.h"
#include "TaskManager.h"

// �R���X�g���N�^
Task::Task(int prio)
	: m_priority(prio)
{
	// �^�X�N�Ǘ��N���X�Ɏ��g��ǉ�
	TaskManager::Instance()->AddTask(this);
}

// �f�X�g���N�^
Task::~Task()
{
	// �^�X�N�Ǘ��N���X���玩�g����菜��
	TaskManager::Instance()->RemoveTask(this);
}

// �D��x���擾
int Task::GetPriority() const
{
	return m_priority;
}

// �D��x��ݒ�
void Task::SetPriority(int prio)
{
	// �V�����D��x�ɕύX���Ă���A
	// �^�X�N�����X�g�����菜���A�ēx���X�g�ɒǉ����邱�ƂŁA
	// �V�����D��x�̈ʒu�Ƀ^�X�N��z�u
	m_priority = prio;
	TaskManager::Instance()->RemoveTask(this);
	TaskManager::Instance()->AddTask(this);
}

// �^�X�N���폜
void Task::Delete()
{
	TaskManager::Instance()->DeleteTask(this);
}