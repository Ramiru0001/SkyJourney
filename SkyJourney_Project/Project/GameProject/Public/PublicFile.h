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
	enum StageNum {
		Tytle,
		SkyIsland,
		Desert,
	};
	static bool Player_On;//プレイヤーがいるかいないか。いたらtrue
	static bool Camera_On;//カメラがあるかないか。あったらtrue
	static CMode c_mode;//カメラのモード
	//static DMode d_mode;//ログオンorオフ
	static bool log_passage;
	static bool log_pos;
	static bool Whiteout_flag;//trueになったらホワイトアウト処理
	static bool Stage_Change;//通常はfalse。stageが変わった時にtrueになる。
	static bool Debug_mode;
	static int Feather_Count;//総羽の数
	static int LightFeather_Count;//使える羽の数
	static int Stage_Num;//現在のステージnumber
	static CVector3D Player_pos;
	static CVector3D Camera_rot;
};
class PublicFunction {
public:
};