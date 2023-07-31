#include "PublicFile.h"
PublicNum::CMode PublicNum::c_mode = CMode::FixedPoint;//CPPで再度定義しないとエラー
PublicNum::DMode PublicNum::d_mode = DMode::LogOff;
int PublicNum::LightFeather_Count = 0;
int PublicNum::Feather_Count = 0;