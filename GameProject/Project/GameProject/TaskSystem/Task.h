#pragma once
#include <stdio.h>
#include <list>
#include <algorithm>
//タスクの優先度
enum class ETaskPrio {
	eTypeSky,//空
	eTypeStage,//ステージ
	eDefault,//デフォルト
	eTypeCamera,//カメラ
	eTypePlayer,//プレイヤーキャラクター
	eTypeEnemy,//敵キャラクター
};
class Task {
protected:
	int m_priority;//優先度
public:
	Task(int Prio=(int)ETaskPrio::eDefault);
	int GetPriority()const;//優先度を取得
	void SetPriority(int prio);//優先度を設定
	void Delete();//タスクを削除
	virtual ~Task();
	virtual void Update(float deltatTime);//更新
	virtual void LateUpdate(float deltaTime) {};//後更新
	virtual void Draw()=0;
};