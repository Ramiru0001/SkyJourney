#pragma once
class SkyIsland :public Task {
public:
	CModelObj m_Field;
	CModelObj m_Sky;
public:
	SkyIsland();
	void Render();
	CModel* GetModel();
};
class Desert :public Task {
public:
	CModelObj m_Field;
	CModelObj m_Sky;
public:
	Desert();
	void Render();
	CModel* GetModel();
};
class Volcano :public Task {
public:
	CModelObj m_Field;
	CModelObj m_Sky;
public:
	Volcano();
	void Render();
	CModel* GetModel();
};