#pragma once
#include "Task.h"
//タスク管理クラス
class TaskManager {
private:
	static TaskManager* mn_instance;//TaskManager
	std::vector <Task*>m_TaskList;//生成されたタスクのリスト
	std::vector <Task*>m_AddList;//リストに追加するタスクのリスト
	std::vector <Task*>m_RemoveList;//リストから除外するタスクのリスト
	std::vector <Task*>m_DeletekList;//リストから削除するタスクのリスト
	void AddTaskList();//追加するタスクを反映
	void RemoveTaskList();//除外するタスクを反映
	void DeleteTaskList();//削除するタスクを反映
public:
	static TaskManager* Inatance();//タスクマネージャのインスタンスを取得
	static void ClearInstance();//タスクマネージャのインスタンスを破棄
	~TaskManager();
	TaskManager();
	void AddTask(Task* task);//タスクをリストに追加
	void RemoveTask(Task* task);//タスクをリストから除外
	void DeleteTask(Task* task);//タスクを削除してリストから除外
	void Update(void);//更新
	void Draw(void);//描画
};