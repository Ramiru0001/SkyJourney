#pragma once
class PublicNum {
public:
	enum CMode {
		FixedPoint,//固定カメラ
		WithPlayer,//プレイヤーの後方
	};
	static CMode c_mode;//カメラのモード
};