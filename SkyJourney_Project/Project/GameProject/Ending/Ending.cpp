#include "Ending.h"
Ending::Ending() :Task(ETaskPrio::eUI, EType::eDefault)
{
	m_img = COPY_RESOURCE("EndingImage", CImage);
	//m_img.SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	m_img.SetSize(1110.91,608);
	m_img.SetPos(130,216);
}

void Ending::Update()
{
}

void Ending::Render()
{
	m_img.Draw();
}
