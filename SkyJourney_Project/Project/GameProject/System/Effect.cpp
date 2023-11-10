#include "Effect.h"
Whiteout::Whiteout() :Task(ETaskPrio::eEffect, EType::eEffect) {
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
Sandstorm::Sandstorm() :Task(ETaskPrio::eEffectUnderUI, EType::eEffectUnderUI) {
}
void Sandstorm::Render() {
	Utility::DrawQuad(CVector2D(0, 0), CVector2D(SCREEN_WIDTH, SCREEN_HEIGHT), ColorSet());
}
void Sandstorm::Update() {
	/*if (White_count <= MaxWhite_count) {
		White_count++;
	}
	else {
		White_count = 0;
		PublicNum::Whiteout_flag = false;
		Task::SetKill();
	}*/
	//Damage();
}
//void Sandstorm::Damage() {
//	if (PublicNum::FeatherDetail_Count != 0) {
//		PublicNum::FeatherDetail_Count -= PublicNum::FeatherDetail_CountMax / 300;
//		FeatherBrake_flag = false;
//	}
//	else if(PublicNum::LightFeather_Count>0){
//		PublicNum::LightFeather_Count--;
//		PublicNum::FeatherDetail_Count = PublicNum::FeatherDetail_CountMax;
//		FeatherBrake_flag = false;
//	}
//	else {
//		if (!FeatherBrake_flag) {
//			FeatherBrake_flag = true;
//			FeatherBrake_CountDown = 120;
//		}
//		else {
//			FeatherBrake_CountDown--;
//		}
//		if (FeatherBrake_CountDown == 0) {
//			PublicNum::Feather_Count--;
//			FeatherBrake_CountDown = 120;
//		}
//	}
//}
CVector4D Sandstorm::ColorSet() {
	return CVector4D(0.91f, 0.56f, 0.36f, 0.3f);
}