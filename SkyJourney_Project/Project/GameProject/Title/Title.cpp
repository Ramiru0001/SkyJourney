#include "Title.h"
Title::Title() :Task(ETaskPrio::eSystem, EType::eDefault) ,
m_title_text("C:\\Windows\\Fonts\\msgothic.ttc", 64)
{
	//m_img = COPY_RESOURCE("Tap To Start",CImage);
}

Title::~Title()
{
	//タイトル破棄時にゲームシーンへ移行
	//Base::Add(new Play(0));
	//Base::Add(new SelectScene());
}

void Title::Update()
{
	//ボタン１でタイトル破棄
	//if (PUSH(CInput::eButton1)) {
		//m_kill = true;
}

void Title::Draw()
{
	//m_img.Draw();
	//文字表示
	m_title_text.Draw(64, 256, 1, 1, 1, "PUSH D To Start GAME");
	//m_title_text.Draw(64, 512, 0, 0, 0, "Push Z");
}
