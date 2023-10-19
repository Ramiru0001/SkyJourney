#include "UI.h"
UI::UI():Task(ETaskPrio::eUI, EType::eUI) {
}
void UI::Render() {
	if (Whiteout_Flag == true) {
		std::cout << "DrawQuad" << std::endl;
		Utility::DrawQuad(CVector2D(0, 0), CVector2D(SCREEN_WIDTH, SCREEN_HEIGHT), Whiteout_ColorSet());
	}
}
void UI::Update() {
	if (Whiteout_Flag == true) {
		Whiteout_Timer--;
	}
	if (Whiteout_Timer <= 0) {
		Whiteout_Timer = 30;
		Whiteout_Flag = false;
	}
	
}
CVector4D UI::Whiteout_ColorSet() {
	//”Z“x
	int Consistency=1.0f - Whiteout_Timer / 30.0f;
	return CVector4D(0, 0, 0, Consistency);
}