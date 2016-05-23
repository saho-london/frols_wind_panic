#pragma once

#include <vector>
#include <functional>

#include "manager.h"
#include "Vector2.h"
#include "Easing.h"


class IEffect : public IObject{
public:
	virtual void update() = 0;
	virtual void draw() = 0;
};

class IEaseEffect : public IEffect{
public:
	Ease::Pos pos;
	Ease::Pos exRate;
	Ease::Val angle;
	Ease::Val alpha;
	int blendMode;
	int gHandle;
	Vector2 center;
	int turnFlag;
	int eFrame;
	int deleteFrame;

	IEaseEffect();
	IEaseEffect(const Ease::Pos &pos_, const Ease::Pos &exRate_, const Ease::Val &angle_, const Ease::Val &alpha_, int blendMode_, int gHandle_, int turnFlag_, int deleteFrame_);


	//update内で毎フレーム呼ばれる、追加機能のための関数（元は中身なし）
	virtual void additionalFunc();
	//オブジェクト破棄の際に呼ばれる、追加機能のための関数（元は中身なし）
	virtual void dyingFunc();
	virtual void update_();

	//eFrameを更新し、update_() を呼び、適宜他の追加機能関数を呼ぶ
	void update();
	virtual void draw();
};

class ScoreEffect : public IEaseEffect
{
	int color;
	int score;
public:
	ScoreEffect(const Vector2 &pos, int sco);
	void draw() override;
};

class AllowEffect : public IEaseEffect
{
	int hue;
	int number;
public:
	AllowEffect(const Vector2 &pos);
	void draw() override;
};