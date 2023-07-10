#pragma once
enum class ETaskPrio   {
	eSky,
	eField,
	eObject,
	eDefault,
	ePlayer,
	eEnemy,
	eCamera,
};
class Task {
private:
	static std::list<Task*> m_TaskList;
public:
	ETaskPrio m_prio;
	bool m_kill = false;
	CVector3D m_pos = CVector3D(0, 0, 0);//座標
	CVector3D m_rot = CVector3D(0, 0, 0);//向いている方向
	CVector3D m_ang = CVector3D(0, 0, 0);//角度
public:
	ETaskPrio GetPrio();
	/// コンストラクタ
	/// </summary>
	/// <param name="m_Prio">タスクの優先度</param>
	Task(ETaskPrio prio);
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
	virtual void Collision();
	/// <summary>
	/// 削除フラグを立てる
	/// </summary>
	virtual void SetKill();
	virtual Task* FindObject(ETaskPrio prio);
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