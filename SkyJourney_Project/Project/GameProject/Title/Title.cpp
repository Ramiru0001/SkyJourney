#include "Title.h"
Title::Title() :Task(ETaskPrio::eSystem, EType::eDefault) ,
m_title_text("C:\\Windows\\Fonts\\msgothic.ttc", 64)
{
	m_img = COPY_RESOURCE("TitleImage",CImage);
	m_img.SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
}

Title::~Title()
{
	//�^�C�g���j�����ɃQ�[���V�[���ֈڍs
	//Base::Add(new Play(0));
	//Base::Add(new SelectScene());
}

void Title::Update()
{
	//�{�^���P�Ń^�C�g���j��
	//if (PUSH(CInput::eButton1)) {
		//m_kill = true;
}

void Title::Render()
{
	m_img.Draw();
	//�����\��
	m_title_text.Draw(SCREEN_WIDTH*64/1280, SCREEN_HEIGHT*256/720, 0, 0, 0, "PUSH Z To Start GAME");
	//m_title_text.Draw(64, 512, 0, 0, 0, "Push Z");
}
