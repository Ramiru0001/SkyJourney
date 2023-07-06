#pragma once
#include "../TaskSystem/TaskManager.h"
#include "../TaskSystem/Task.h"
class Field :Task {
public:
	CModelObj m_Field;
	CModelObj m_Sky;
public:
	Field();
	void Render();
	void Update();
};
