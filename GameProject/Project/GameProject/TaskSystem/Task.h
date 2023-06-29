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
	bool m_kill;
	/// <summary>
	/// �^�X�N�̗D��x
	/// </summary>
	int m_prio;
	/// <summary>
	/// ���W
	/// </summary>
	CVector3D m_pos;
	/// <summary>
	/// �����Ă������
	/// </summary>
	CVector3D m_rot;
	/// <summary>
	/// �p�x
	/// </summary>
	CVector3D m_ang;
public:
	Task(int prio=ETaskPrio::eTaskDefault);
	/// <summary>
	/// �폜�t���O�̒l�����
	/// </summary>
	/// <returns></returns>
	virtual bool GetKill();
};