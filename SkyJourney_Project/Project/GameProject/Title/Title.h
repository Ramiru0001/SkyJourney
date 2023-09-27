#pragma once

class Title:public Task {
	//画像オブジェクト
	CImage m_img;
	//文字表示オブジェクト
	CFont m_title_text;
public:
	Title();
	~Title();
	void Update();
	void Draw();
};