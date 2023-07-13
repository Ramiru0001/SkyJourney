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
	ETaskPrio m_prio;//タスクの優先度
	EType m_type;//タスクのタイプ
	bool m_kill = false;
	CVector3D m_pos = CVector3D(0, 0, 0);//座標
	CVector3D m_vec = CVector3D(0, 0, 0);//前方向ベクトル
	CVector3D m_rot = CVector3D(0, 0, 0);//向いている方向
	CVector3D m_ang = CVector3D(0, 0, 0);//角度
	float m_rad =0.5f;//半径
public:
	ETaskPrio GetPrio();
	EType GetType();
	/// コンストラクタ
	/// </summary>
	/// <param name="m_Prio">タスクの優先度</param>
	Task(ETaskPrio prio,EType type);
	/// <summary>
	/// </summary>
	/// <param name="">Taskクラスのポインタ</param>
	static void Add(Task* a);
	/// <summary>
	/// 描画処理
	/// </summary>
	virtual void Render();
	/// <summary>
	/// Update処理
	/// </summary>
	virtual void Update();
	/// <summary>
	/// 当たり判定の処理
	/// </summary>
	virtual void Collision(Task* a);
	/// <summary>
	/// 削除フラグを立てる
	/// </summary>
	virtual void SetKill();
	virtual CModel* GetModel();
	virtual Task* FindObject(EType type);
	/// <summary>
	/// キルフラグがonかoffかを確認
	/// </summary>
	/// <returns>キルフラグの値</returns>
	bool CheckKill();
	/// <summary>
	/// すべて描画処理
	/// </summary>
	static void RenderAll();
	/// <summary>
	/// すべてUpdate
	/// </summary>
	static void UpdateAll();
	/// <summary>
	/// すべての当たり判定処理
	/// </summary>
	static void CollisionAll();
	/// <summary>
	/// 削除フラグONのタスクをすべて削除
	/// </summary>
	static void DeleteAll();
};