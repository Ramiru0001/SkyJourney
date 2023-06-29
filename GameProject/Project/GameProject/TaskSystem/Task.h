#pragma once
#include <stdio.h>
#include <list>
#include <algorithm>
//�^�X�N�̗D��x
enum class ETaskPrio {
	eTypeSky,//��
	eTypeStage,//�X�e�[�W
	eDefault,//�f�t�H���g
	eTypeCamera,//�J����
	eTypePlayer,//�v���C���[�L�����N�^�[
	eTypeEnemy,//�G�L�����N�^�[
};
class Task {
protected:
	int m_priority;//�D��x
public:
	Task(int Prio=(int)ETaskPrio::eDefault);
	int GetPriority()const;//�D��x���擾
	void SetPriority(int prio);//�D��x��ݒ�
	void Delete();//�^�X�N���폜
	virtual ~Task();
	virtual void Update(float deltatTime);//�X�V
	virtual void LateUpdate(float deltaTime) {};//��X�V
	virtual void Draw()=0;
};