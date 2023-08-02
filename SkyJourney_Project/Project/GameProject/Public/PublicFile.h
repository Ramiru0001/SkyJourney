#pragma once
class PublicNum {
public:
	enum CMode {
		FixedPoint,//固定カメラ
		WithPlayer,//プレイヤーの後方
	};
	enum DMode {
		LogOn,
		LogOff,
	};
	static CMode c_mode;//カメラのモード
	//static DMode d_mode;//ログオンorオフ
	static bool log_passage;
	static bool log_pos;
	static int Feather_Count;//総羽の数
	static int LightFeather_Count;//使える羽の数
};
class PublicFunction {
public:
};