#include "TaskManager.h"
TaskManager::TaskManager() :Task() {

	}
void TaskManager::AddTask(Task* b) {
	m_TaskList.push_back(b);
};
void TaskManager::DeleteTask(Task* b) {
	auto itr = m_TaskList.begin();
	//末尾まで繰り返す
	while (itr != m_TaskList.end()) {
		//削除チェック
		if ((*itr)->GetKill()) {
			//削除
			delete* itr;
			//リストから除外する
			//次のオブジェクトを受け取る
			itr = m_TaskList.erase(itr);
			continue;
		}
	}
		//次のオブジェクト
		itr++;
	}
}