#pragma once
//進捗の管理、ゲームの主な進行をするクラスである
class Progress :public Task{
private:
	enum ProgressNum{
		eTytle,
		eSkyIsland,
	};
	/// <summary>
	/// 進捗を数字で管理。タイトル＝0。最初のステージ＝１
	/// </summary>
	int prog_num = ProgressNum::eTytle;
public:
	Progress();
	void Update();
	/// <summary>
	/// 進捗が変化した場合のみ呼ばれる
	/// </summary>
	void ProgressChange(int Progress);
};