#pragma once
#include <GLLibrary.h>

// �^�X�N�̗D��x
enum class ETaskPrio
{
	eBackground,// �w�i
	eDefault,	// �f�t�H���g
	ePlayer,	// �v���C���[

	Num
};

// �^�X�N�N���X
class Task
{
protected:
	int m_priority;	// �D��x

public:
	// �R���X�g���N�^
	Task(int prio = (int)ETaskPrio::eDefault);
	// �f�X�g���N�^
	// �i�p����ł��f�X�g���N�^���g�p���邽��virtual���j
	virtual ~Task();

	// �D��x���擾
	int GetPriority() const;
	// �D��x��ݒ�
	void SetPriority(int prio);

	// �^�X�N���폜
	void Delete();

	// �X�V�i�������͌p����Ŏ����j
	virtual void Update(float deltaTime) = 0;
	// ��X�V
	virtual void LateUpdate(float deltaTime) {};
	// �`��i�������͌p����Ŏ����j
	virtual void Draw() = 0;
};