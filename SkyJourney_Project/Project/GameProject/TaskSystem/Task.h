#pragma once
/// <summary>
/// タスクの優先順位
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
	/// 削除フラグ
	/// </summary>
	bool m_kill = false;
	/// <summary>
	/// タスクの優先度
	/// </summary>
	int m_prio= eTaskDefault;
	/// <summary>
	/// 座標
	/// </summary>
	CVector3D m_pos = CVector3D(0, 0, 0);
	/// <summary>
	/// 向いている方向
	/// </summary>
	CVector3D m_rot= CVector3D(0, 0, 0);;
	/// <summary>
	/// 角度
	/// </summary>
	CVector3D m_ang = CVector3D(0, 0, 0);
public:
	Task(int prio=ETaskPrio::eTaskDefault);
	/// <summary>
	/// 削除フラグの値を入手
	/// </summary>
	/// <returns></returns>
	virtual bool GetKill();
	virtual void Render();
	virtual void Update();
	virtual void SetKill();
	virtual void Collision(Task* b);
};