#include "Effect.h"
Whiteout::Whiteout() :Task(ETaskPrio::eEffect, EType::eEffect) {
	White_count = 0;
	MaxWhite_count = PublicNum::MaxWhite_Count;
}
void Whiteout::Render() {
	if (CShadow::GetInstance()->GetState() == CShadow::eShadow)return;
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
Sandstorm::Sandstorm() :Task(ETaskPrio::eEffectUnderUI, EType::eEffectUnderUI) {
}
void Sandstorm::Render() {
	if (CShadow::GetInstance()->GetState() == CShadow::eShadow)return;
	Utility::DrawQuad(CVector2D(0, 0), CVector2D(SCREEN_WIDTH, SCREEN_HEIGHT), ColorSet());
}
void Sandstorm::Update() {
}
CVector4D Sandstorm::ColorSet() {
	return CVector4D(0.91f, 0.56f, 0.36f, 0.3f);
}