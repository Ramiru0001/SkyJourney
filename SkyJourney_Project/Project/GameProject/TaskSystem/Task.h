#pragma once
enum class ETaskPrio   {
	eSky,
	eField,
	eObject,
	eFeather,
	eDefault,
	ePlayer,
	eEnemy,
	eCamera,
};
class Task {
private:
	static std::list<Task*> m_TaskList;
public:
	enum EType{
		eDefault,
		eSky,
		eField,
		eObject,
		eFeather,
		ePlayer,
		eEnemy,
		eCamera,
	};
	ETaskPrio m_prio;//�^�X�N�̗D��x
	EType m_type;//�^�X�N�̃^�C�v
	bool m_kill = false;
	CVector3D m_pos = CVector3D(0, 0, 0);//���W
	CVector3D m_vec = CVector3D(0, 0, 0);//�O�����x�N�g��
	CVector3D m_rot = CVector3D(0, 0, 0);//�����Ă������
	CVector3D m_ang = CVector3D(0, 0, 0);//�p�x
	float m_rad =0.5f;//���a
public:
	ETaskPrio GetPrio();
	EType GetType();
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="m_Prio">�^�X�N�̗D��x</param>
	Task(ETaskPrio prio,EType type);
	/// <summary>
	/// </summary>
	/// <param name="">Task�N���X�̃|�C���^</param>
	static void Add(Task* a);
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
	virtual void Collision(Task* a);
	/// <summary>
	/// �폜�t���O�𗧂Ă�
	/// </summary>
	virtual void SetKill();
	virtual CModel* GetModel();
	virtual Task* FindObject(EType type);
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