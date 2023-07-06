#pragma once
std::list<Task*> m_TaskList;
class Task {
	enum eTaskPrio {
		eSky,
		eField,
		eObject,
		eDefault,
		ePlayer,
		eEnemy,
	};
private:
	//std::list<Task*> m_DrawList;
	bool m_kill = false;
	int m_Prio = eDefault;//�^�X�N�̗D��x
	CVector3D m_pos = CVector3D(0, 0, 0);//���W
	CVector3D m_rot = CVector3D(0, 0, 0);//�����Ă������
	CVector3D m_Ang = CVector3D(0, 0, 0);//�p�x
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="m_Prio">�^�X�N�̗D��x</param>
	Task(int m_Prio = eDefault);
	/// <summary>
	/// �^�X�N�̒ǉ�
	/// </summary>
	/// <param name="">Task�N���X�̃|�C���^</param>
	void Add(Task*);
	/// <summary>
	/// �`�揈��
	/// </summary>
	virtual void Render();
	/// <summary>
	/// Update����
	/// </summary>
	virtual void Update();
	/// <summary>
	/// �����蔻��̏���
	/// </summary>
	virtual void Collision();
	/// <summary>
	/// �폜�t���O�𗧂Ă�
	/// </summary>
	virtual void SetKill();
	/// <summary>
	/// �L���t���O��on��off�����m�F
	/// </summary>
	/// <returns>�L���t���O�̒l</returns>
	bool CheckKill();
	/// <summary>
	/// ���ׂĕ`�揈��
	/// </summary>
	static void RenderAll();
	/// <summary>
	/// ���ׂ�Update
	/// </summary>
	static void UpdateAll();
	/// <summary>
	/// ���ׂĂ̓����蔻�菈��
	/// </summary>
	static void CollisionAll();
	/// <summary>
	/// �폜�t���OON�̃^�X�N�����ׂč폜
	/// </summary>
	static void DeleteAll();
};