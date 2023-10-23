#pragma once
//進捗の管理、ゲームの主な進行をするクラスである
class Progress :public Task{
private:
	enum ProgressNum {
	Tytle,
	SkyIsland,
	Desert,
	};
	/// <summary>
	/// 進捗を数字で管理。タイトル＝0。最初のステージ＝１
	/// </summary>
	int prog_num;
public:
	Progress();
	int GetProgNum();
	void Update();
	/// <summary>
	/// 進捗が変化した場合のみ呼ばれる。
	/// ステージリストのアイテムをすべて破棄して、変更後の進捗のアイテムを追加
	/// </summary>
	void ProgressChange(int Progress);
};