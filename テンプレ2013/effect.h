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


	//update���Ŗ��t���[���Ă΂��A�ǉ��@�\�̂��߂̊֐��i���͒��g�Ȃ��j
	virtual void additionalFunc();
	//�I�u�W�F�N�g�j���̍ۂɌĂ΂��A�ǉ��@�\�̂��߂̊֐��i���͒��g�Ȃ��j
	virtual void dyingFunc();
	virtual void update_();

	//eFrame���X�V���Aupdate_() ���ĂсA�K�X���̒ǉ��@�\�֐����Ă�
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