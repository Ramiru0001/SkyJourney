#pragma once
class Field :public Task {
public:
	CModelObj m_Field;
	CModelObj m_Sky;
public:
	Field();
	void Render();
	void Update();
};
