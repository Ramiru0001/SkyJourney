#include "PublicFile.h"
PublicNum::CMode PublicNum::c_mode = CMode::FixedPoint;//CPPで再度定義しないとエラー
//PublicNum::DMode PublicNum::d_mode = DMode::LogOff;
int PublicNum::LightFeather_Count = 0;
int PublicNum::Feather_Count = 0;
int PublicNum::Stage_Num = StageNum::Tytle;
bool PublicNum::log_passage = false;
bool PublicNum::log_pos = false;
bool PublicNum::Player_On = false;
bool PublicNum::Camera_On = false;
bool PublicNum::Stage_Change = false;
CVector3D PublicNum::Player_pos = CVector3D(0, 0, 0);
CVector3D PublicNum::Camera_rot = CVector3D(0, 0, 0);