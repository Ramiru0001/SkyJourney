#include "PublicFile.h"
PublicNum::CMode PublicNum::c_mode = CMode::WithPlayer;//CPP�ōēx��`���Ȃ��ƃG���[
//PublicNum::DMode PublicNum::d_mode = DMode::LogOff;
int PublicNum::LightFeather_Count = 0;
int PublicNum::Feather_Count = 0;
int PublicNum::Stage_Num = StageNum::Tytle;
int PublicNum::MaxWhite_Count = 120;
int PublicNum::FeatherDetail_Count = 0;
int PublicNum::FeatherDetail_CountMax = 300;
bool PublicNum::Log_passage = false;
bool PublicNum::Log_pos = false;
bool PublicNum::Player_On = false;
bool PublicNum::Camera_On = false;
bool PublicNum::Stage_Change = false;
bool PublicNum::Debug_mode = true;
bool PublicNum::Whiteout_flag = false;
bool PublicNum::stage_change_flag = false;
bool PublicNum::WhaleAttack = false;
CVector3D PublicNum::WhaleVec=CVector3D(0,0,0);
CVector3D PublicNum::Player_pos = CVector3D(0, 0, 0);
CVector3D PublicNum::Camera_pos = CVector3D(0, 0, 0);
CVector3D PublicNum::Camera_rot = CVector3D(0, 0, 0);
bool PublicFunction::Observer(int old,int now) {
	if (old < now) {
		return true;
	}
	return false;
}
CVector3D PublicFunction::DoubleToVector3D(double part[]) {
	int PosCount = sizeof(part);
	if (PosCount % 3 != 0) {
		return CVector3D(0,0,0);
	}
	int num = 0;
	CVector3D list[100];
	for (int i = 0; i < PosCount; i+=3) {
		list[num] = CVector3D(part[i],part[i+1],part[i+2]);
		num++;
		list[num];
	}
}