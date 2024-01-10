#pragma once
#define RotationalSpeed DtoR(1.0f)
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
		Volcano,
	};
	static bool Player_On;//プレイヤーがいるかいないか。いたらtrue
	static bool Camera_On;//カメラがあるかないか。あったらtrue
	static CMode c_mode;//カメラのモード
	//static DMode d_mode;//ログオンorオフ
	static bool Log_passage;
	static bool Log_pos;
	static bool Whiteout_flag;//trueになったらホワイトアウト処理
	static bool Stage_Change;//通常はfalse。stageが変わった時にtrueになる。
	static bool Debug_mode;
	static bool stage_change_flag;//stageChangeをするホワイトアウトのときにon
	static bool WhaleAttack;//くじらさんがアタックしたらtrue;
	static int Feather_Count;//総羽の数
	static int LightFeather_Count;//使える羽の数
	static int Stage_Num;//現在のステージnumber
	static int MaxWhite_Count;//ホワイトアウトの時間
	static int FeatherDetail_Count;//羽の詳細な数字
	static int FeatherDetail_CountMax;//羽の詳細な数字の最大値
	static CVector3D Player_pos;
	static CVector3D Camera_pos;
	static CVector3D Camera_rot;
	static CVector3D WhaleVec;
};
class PublicFunction {
public:
	/// <summary>
	/// 以前の値と今の値を比べて増えていたらtrue。それ以外はfalse
	/// </summary>
	/// <returns></returns>
	static bool Observer(int old,int now);
	static CVector3D DoubleToVector3D(double[]);
};