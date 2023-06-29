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
	bool m_kill;
	/// <summary>
	/// タスクの優先度
	/// </summary>
	int m_prio;
	/// <summary>
	/// 座標
	/// </summary>
	CVector3D m_pos;
	/// <summary>
	/// 向いている方向
	/// </summary>
	CVector3D m_rot;
	/// <summary>
	/// 角度
	/// </summary>
	CVector3D m_ang;
public:
	Task(int prio=ETaskPrio::eTaskDefault);
	/// <summary>
	/// 削除フラグの値を入手
	/// </summary>
	/// <returns></returns>
	virtual bool GetKill();
};