#pragma once
#include "Task.h"
//�^�X�N�Ǘ��N���X
class TaskManager {
private:
	static TaskManager* mn_instance;//TaskManager
	std::vector <Task*>m_TaskList;//�������ꂽ�^�X�N�̃��X�g
	std::vector <Task*>m_AddList;//���X�g�ɒǉ�����^�X�N�̃��X�g
	std::vector <Task*>m_RemoveList;//���X�g���珜�O����^�X�N�̃��X�g
	std::vector <Task*>m_DeletekList;//���X�g����폜����^�X�N�̃��X�g
	void AddTaskList();//�ǉ�����^�X�N�𔽉f
	void RemoveTaskList();//���O����^�X�N�𔽉f
	void DeleteTaskList();//�폜����^�X�N�𔽉f
public:
	static TaskManager* Inatance();//�^�X�N�}�l�[�W���̃C���X�^���X���擾
	static void ClearInstance();//�^�X�N�}�l�[�W���̃C���X�^���X��j��
	~TaskManager();
	TaskManager();
	void AddTask(Task* task);//�^�X�N�����X�g�ɒǉ�
	void RemoveTask(Task* task);//�^�X�N�����X�g���珜�O
	void DeleteTask(Task* task);//�^�X�N���폜���ă��X�g���珜�O
	void Update(void);//�X�V
	void Draw(void);//�`��
};