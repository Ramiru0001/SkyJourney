#pragma once
#include "Task.h"
std::list<Task*> m_TaskList;
class TaskManager :Task {
public:
	TaskManager();
	/// <summary>
	/// タスクリストに追加
	/// </summary>
	/// <param name="b">newインスタンスをタスクポインタで入れる</param>
	virtual void AddTask(Task* b);
	/// <summary>
	/// すべてのkillフラグをtrueにする
	/// </summary>
	virtual void SetKillAll();
	/// <summary>
	/// killフラグがtrueの場合削除
	/// </summary>
	static void DeleteAll();
	/// <summary>
	/// すべて画面に表示
	/// </summary>
	static void RenderAll();
	/// <summary>
	/// すべてUpdate
	/// </summary>
	static void UpdateAll();
	/// <summary>
	/// すべての当たり判定の処理をする
	/// </summary>
	static void CollisionAll();
};