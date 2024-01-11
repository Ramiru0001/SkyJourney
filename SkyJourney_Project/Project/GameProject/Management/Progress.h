#pragma once
//進捗の管理、ゲームの主な進行をするクラスである
class Progress :public Task{
private:
	enum ProgressNum {
		Tytle,
		SkyIsland,
		Desert,
		Volcano,
		Ending,
	};
	/// <summary>
	/// 進捗を数字で管理。タイトル＝0。最初のステージ＝１
	/// </summary>
	int Whiteout_count;
	bool Whiteout_flag_old=false;
	int prog_num;
	bool TimerOn;
public:
	Progress();
	int GetProgNum();
	void Update();
	/// <summary>
	/// 進捗が変化した場合のみ呼ばれる。
	/// ステージリストのアイテムをすべて破棄して、変更後の進捗のアイテムを追加
	/// </summary>
	void ProgressChange(int Progress);
	//ステージチェンジのタイマー。チェンジする時にtrue
	void TimerStart();
	bool StageChangeTimer(bool);
	//bool WhiteoutFinishTrigger();
};