#pragma once
class SkyIsland :public Task {
public:
	CModelObj m_Field;
	CModelObj m_Sky;
public:
	SkyIsland();
	void Render();
	void Update();
	CModel* GetModel();
};
class Desert :public Task {
public:
	CModelObj m_Field;
	CModelObj m_Sky;
public:
	Desert();
	void Render();
	void Update();
	CModel* GetModel();
};
