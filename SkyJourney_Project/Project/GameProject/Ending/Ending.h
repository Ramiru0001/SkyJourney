#pragma once

class Ending :public Task {
	//画像オブジェクト
	CImage m_img;
	//文字表示オブジェクト
	CFont m_title_text;
public:
	Ending();
	void Update();
	void Render();
};