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
	int m_Prio = eDefault;//タスクの優先度
	CVector3D m_pos = CVector3D(0, 0, 0);//座標
	CVector3D m_rot = CVector3D(0, 0, 0);//向いている方向
	CVector3D m_Ang = CVector3D(0, 0, 0);//角度
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="m_Prio">タスクの優先度</param>
	Task(int m_Prio = eDefault);
	/// <summary>
	/// タスクの追加
	/// </summary>
	/// <param name="">Taskクラスのポインタ</param>
	void Add(Task*);
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