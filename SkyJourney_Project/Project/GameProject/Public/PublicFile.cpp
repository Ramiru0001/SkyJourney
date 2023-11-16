#include "PublicFile.h"
PublicNum::CMode PublicNum::c_mode = CMode::WithPlayer;//CPPで再度定義しないとエラー
//PublicNum::DMode PublicNum::d_mode = DMode::LogOff;
int PublicNum::LightFeather_Count = 0;
int PublicNum::Feather_Count = 0;
int PublicNum::Stage_Num = StageNum::Tytle;
int PublicNum::MaxWhite_Count = 120;
int PublicNum::FeatherDetail_Count = 0;
int PublicNum::FeatherDetail_CountMax = 300;
bool PublicNum::log_passage = false;
bool PublicNum::log_pos = false;
bool PublicNum::Player_On = false;
bool PublicNum::Camera_On = false;
bool PublicNum::Stage_Change = false;
bool PublicNum::Debug_mode = true;
bool PublicNum::Whiteout_flag = false;
CVector3D PublicNum::Player_pos = CVector3D(0, 0, 0);
CVector3D PublicNum::Camera_rot = CVector3D(0, 0, 0);
bool PublicFunction::Observer(int old,int now) {
	if (old < now) {
		return true;
	}
	return false;
}