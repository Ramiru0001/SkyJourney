#include "UI.h"
Whiteout::Whiteout():Task(ETaskPrio::eUI, EType::eUI) {
	White_count = 0;
	MaxWhite_count = PublicNum::MaxWhite_Count;
}
void Whiteout::Render() {
	if (PublicNum::Whiteout_flag == true) {
		Utility::DrawQuad(CVector2D(0, 0), CVector2D(SCREEN_WIDTH, SCREEN_HEIGHT), Whiteout_ColorSet());
	}
}
void Whiteout::Update() {
	if (White_count <= MaxWhite_count) {
		White_count++;
	}
	else {
		White_count = 0;
		PublicNum::Whiteout_flag = false;
		Task::SetKill();
	}
}
CVector4D Whiteout::Whiteout_ColorSet() {
	//”Z“x
	int Whiteout_step = White_count - (MaxWhite_count / 2);
	float Consistency = 1.0f - (std::abs(Whiteout_step) / (MaxWhite_count / 2.0f));
	return CVector4D(1.0f, 1.0f, 1.0f, Consistency);
}