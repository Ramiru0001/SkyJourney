#pragma once
enum class ETaskPrio : int {
	eSystem,
	eSky,
	eField,
	eObject,
	eFeather,
	eDefault,
	eCharacter,
	ePlayer,
	eEnemy,
	eCamera,
	eEffectUnderUI,
	eUI,
	eEffect,
};
class Task {
private:
	/// <summary>
	/// ���݂̂��ׂẴ^�X�N���X�g
	/// </summary>
	static std::list<Task*> m_TaskList;
	/// <summary>
	/// ���݂̃X�e�[�W�Ŏg�p���Ă���^�X�N���X�g
	/// </summary>
	static std::list<Task*> m_StageTaskList;
public:
	enum EType{
		eDefault,
		eSky,
		eField,
		eObject,
		eFeather,
		eCharacter,
		ePlayer,
		eEnemy,
		eCamera,
		eEffectUnderUI,
		eUI,
		eEffect,
	};
	ETaskPrio m_prio;//�^�X�N�̗D��x
	EType m_type;//�^�X�N�̃^�C�v
	bool m_kill = false;//�폜�t���O
	CVector3D m_pos = CVector3D(0, 0, 0);//���W
	CVector3D m_vec = CVector3D(0, 0, 0);//�O�����x�N�g��
	CVector3D m_rot = CVector3D(0, 0, 0);//�����Ă������
	CVector3D m_ang = CVector3D(0, 0, 0);//�p�x
	float m_rad =0.5f;//���a
	bool m_collision;//�����蔻�肪���邩�Ȃ����B����Ȃ�true
public:
	ETaskPrio GetPrio();
	EType GetType();
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="m_Prio">�^�X�N�̗D��x</param>
	Task(ETaskPrio prio,EType type);
	/// <summary>�^�X�N���X�g�ɒǉ�
	/// </summary>
	/// <param name="">Task�N���X�̃|�C���^</param>
	static void Add(Task* a); 
	/// <summary>
	/// stage�ŗL�̃^�X�N���X�g�ɒǉ�
	/// </summary>
	/// <param name="a"></param>
	static void AddStage(Task* a);
	static void AddFeathers(CVector3D[]);
	static void AddCandles(CVector3D[]);
	/// <summary>
	/// �폜�t���Otrue
	/// </summary>
	virtual void SetKill();
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
	virtual CModel* GetModel();
	//virtual Task* FindObject(EType type);
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
	/// �X�e�[�W�ŗL�̃^�X�N�����ׂč폜
	/// </summary>
	static void DeleteAllStage();
	/// <summary>
	/// �폜�t���OON�̃^�X�N�����ׂč폜
	/// </summary>
	static void DeleteAll();
	/// <summary>
	/// �����蔻��̗L�������
	/// </summary>
	/// <returns>true�̏ꍇ���肠��B�f�t�H���g��true</returns>
	virtual bool GetCollision() {
		return true;
	}
};