#pragma once
#include "../TaskSystem/TaskManager.h"
#include "../TaskSystem/Task.h"
class Player :Task {
public:
	CModelA3M m_model;
public:
	Player(CVector3D &pos);
	void Render();
	void Update();
};