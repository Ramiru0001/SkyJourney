#pragma once

class Ending :public Task {
	//�摜�I�u�W�F�N�g
	CImage m_img;
	//�����\���I�u�W�F�N�g
	CFont m_title_text;
public:
	Ending();
	void Update();
	void Render();
};