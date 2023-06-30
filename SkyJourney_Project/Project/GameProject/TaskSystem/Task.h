#pragma once
/// <summary>
/// �^�X�N�̗D�揇��
/// </summary>
enum ETaskPrio {
	eTaskSky,
	eTaskStage,
	eTaskDefault,
	eTaskEnemy,
	eTaskPlayer,
	eTaskUI,
};
class Task {
private:
	/// <summary>
	/// �폜�t���O
	/// </summary>
	bool m_kill = false;
	/// <summary>
	/// �^�X�N�̗D��x
	/// </summary>
	int m_prio= eTaskDefault;
	/// <summary>
	/// ���W
	/// </summary>
	CVector3D m_pos = CVector3D(0, 0, 0);
	/// <summary>
	/// �����Ă������
	/// </summary>
	CVector3D m_rot= CVector3D(0, 0, 0);;
	/// <summary>
	/// �p�x
	/// </summary>
	CVector3D m_ang = CVector3D(0, 0, 0);
public:
	Task(int prio=ETaskPrio::eTaskDefault);
	/// <summary>
	/// �폜�t���O�̒l�����
	/// </summary>
	/// <returns></returns>
	virtual bool GetKill();
	virtual void Render();
	virtual void Update();
	virtual void SetKill();
	virtual void Collision(Task* b);
};