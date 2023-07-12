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
	static DMode d_mode;//ログオンorオフ
};
class PublicFunction {
public:
};