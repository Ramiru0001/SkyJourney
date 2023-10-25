#include "Task.h"
std::list<Task*> Task::m_TaskList;
std::list<Task*> Task::m_StageTaskList;
Task::Task(ETaskPrio prio, EType type) :m_prio(prio), m_type(type) {

}
void Task::Add(Task* a) {
	auto itr = m_TaskList.begin();
	while (itr != m_TaskList.end()) {
		if ((*itr)->GetPrio() >= a->GetPrio()) {
			m_TaskList.insert(itr, a);
			return;
		}
		itr++;
	}
	m_TaskList.push_front(a);
}
void Task::AddStage(Task* a) {
	auto itr = m_StageTaskList.begin();
	while (itr != m_StageTaskList.end()) {
		if ((*itr)->GetPrio() >= a->GetPrio()) {
			m_StageTaskList.insert(itr, a);
			return;
		}
		itr++;
	}
	m_StageTaskList.push_front(a);
}
void Task::Render() {}
void Task::Update() {}
void Task::Collision(Task* a) {

}
void Task::SetKill() {
	m_kill = true;
}
void Task::RenderAll() {
	auto itr = m_TaskList.begin();
	auto Stageitr = m_StageTaskList.begin();
	while (itr != m_TaskList.end()&& Stageitr != m_StageTaskList.end()) {
		if ((*itr)->GetPrio() >= (*Stageitr)->GetPrio()) {
			(*Stageitr)->Render();
			Stageitr++;
		}
		else if ((*itr)->GetPrio() <= (*Stageitr)->GetPrio()) {
			(*itr)->Render();
			itr++;

		}
	}
	while (itr != m_TaskList.end()) {
		(*itr)->Render();
		itr++;
	}
	while (Stageitr != m_StageTaskList.end()) {
		(*Stageitr)->Render();
		Stageitr++;
	}
}
void Task::UpdateAll() {
	for (auto& b : m_TaskList) {
		b->Update();
	}
	for (auto& b : m_StageTaskList) {
		b->Update();
	}
}
void Task::CollisionAll() {
	auto itr = m_TaskList.begin();
	while (itr != m_TaskList.end()) {
		if (!(*itr)->m_kill) {
			auto ct = itr;
			ct++;
			while (ct != m_TaskList.end()) {
				if (!(*ct)->m_kill) {
					(*itr)->Collision(*ct);
					(*ct)->Collision(*itr);
					/*if (PublicNum::log_passage == true) {
						std::cout << (*itr)->m_type << " : " << (*ct)->m_type << std::endl;
					}*/
				}
				ct++;
			}
		}
		itr++;
	}
	auto itr2 = m_StageTaskList.begin();
	while (itr2 != m_StageTaskList.end()) {
		if (!(*itr2)->m_kill) {
			auto ct2 = itr2;
			ct2++;
			while (ct2 != m_StageTaskList.end()) {
				if (!(*ct2)->m_kill) {
					(*itr2)->Collision(*ct2);
					(*ct2)->Collision(*itr2);
				}
				ct2++;
			}
		}
		itr2++;
	}
	auto itr3 = m_TaskList.begin();
	while (itr3 != m_TaskList.end()) {
		if (!(*itr3)->m_kill) {
			auto itr4 = m_StageTaskList.begin();
			while (itr4 != m_StageTaskList.end()) {
				if (!(*itr4)->m_kill) {
					(*itr3)->Collision(*itr4);
					(*itr4)->Collision(*itr3);
				}
				itr4++;
			}
		}
		itr3++;
	}
}
void Task::DeleteAll() {
	auto itr = m_TaskList.begin();
	//末尾まで繰り返す
	while (itr != m_TaskList.end()) {
		//削除チェック
		if ((*itr)->m_kill == true) {
			//if (--(*itr)->m_kill == true) {
				//削除
			delete* itr;
			//リストから除外する
			//次のオブジェクトを受け取る
			itr = m_TaskList.erase(itr);
			continue;
			//}
		}
		//次のオブジェクト
		itr++;
	}
	{auto itr = m_StageTaskList.begin();
	//末尾まで繰り返す
	while (itr != m_StageTaskList.end()) {
		//削除チェック
		if ((*itr)->m_kill == true) {
			//if (--(*itr)->m_kill == true) {
				//削除
			delete* itr;
			//リストから除外する
			//次のオブジェクトを受け取る
			itr = m_StageTaskList.erase(itr);
			continue;
			//}
		}
		//次のオブジェクト
		itr++;
	}}
}
void Task::DeleteAllStage() {
	auto itr = m_StageTaskList.begin();
	//末尾まで繰り返す
	while (itr != m_StageTaskList.end()) {
		//削除
		delete* itr;
		//リストから除外する
		//次のオブジェクトを受け取る
		itr = m_StageTaskList.erase(itr);
		continue;
		//次のオブジェクト
		itr++;
	}
}
bool Task::CheckKill() {
	if (m_kill = true) {
		return true;
	}
	else {
		return false;
	}
}
ETaskPrio Task::GetPrio() {
	return m_prio;
}
Task::EType Task::GetType() {
	return m_type;
}
//Task* Task::FindObject(EType type) {
//	{auto itr = m_TaskList.begin();
//	while (itr != m_TaskList.end()) {
//		if ((*itr)->GetType() == type) {
//			return *itr;
//		}
//		itr++;
//	}}
//	{auto itr = m_StageTaskList.begin();
//	while (itr != m_StageTaskList.end()) {
//		if ((*itr)->GetType() == type) {
//			return *itr;
//		}
//		itr++;
//	}}
//	return nullptr;
//}
CModel* Task::GetModel() {
	return nullptr;
}