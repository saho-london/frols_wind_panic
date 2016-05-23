#include "MyFunc.h"
#include "Draw.h"
#include "effect.h"
#include "graph.h"
#include "myglobal.h"


IEaseEffect::IEaseEffect()
{
}

IEaseEffect::IEaseEffect(const Ease::Pos &pos_, const Ease::Pos &exRate_, const Ease::Val &angle_, const Ease::Val &alpha_, int blendMode_, int gHandle_, int turnFlag_, int deleteFrame_) :
pos(pos_),
exRate(exRate_),
angle(angle_),
alpha(alpha_),
blendMode(blendMode_),
gHandle(gHandle_),
center(Func::getGraphSizeV2(gHandle_) * 0.5),
turnFlag(turnFlag_),
eFrame(0),
deleteFrame(deleteFrame_)
{

}

void IEaseEffect::update(){
	eFrame++;
	update_();
	additionalFunc();
	if (eFrame > deleteFrame){
		dyingFunc();
		IsDead = true;
	}
}

void IEaseEffect::additionalFunc(){
}

void IEaseEffect::dyingFunc(){
}

void IEaseEffect::update_(){
	pos.update();
	exRate.update();
	angle.update();
	alpha.update();
}

void IEaseEffect::draw(){
	MyDraw::exrot3(pos(), center, exRate(), angle(), gHandle, alpha(), turnFlag, blendMode);
}

ScoreEffect::ScoreEffect(const Vector2 &pos, int sco):
IEaseEffect(Ease::Pos(90, pos, (Vector2)pos + Vector2(0, -50), Ease::sinOut), Ease::Pos(), Ease::Val(), Ease::Val(90, 255.0, 0.0, Ease::linear), DX_BLENDMODE_ALPHA, -1, 0, 90),
color(0xFFFFFF),
score(sco)
{

}

void ScoreEffect::draw()
{
	SetDrawBlendMode(blendMode, alpha());
	int wd = GetDrawFormatStringWidthToHandle(MARU_GOTHIC_S, "+%d", score);
	DrawFormatStringToHandle(pos().x - wd / 2, pos().y, color, MARU_GOTHIC_S, "+%d", score);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

AllowEffect::AllowEffect(const Vector2 &pos) :
IEaseEffect(Ease::Pos(45, pos, (Vector2)pos + Vector2::GetPolar(Random::Rand(150, 80), Random::FRadRand()), Ease::sinOut), Ease::Pos(45, Vector2(1.0, 1.0), Vector2(1.0, 1.0), Ease::sinIn), Ease::Val(45, 0.0, Random::posneg(0.5) * Random::FRand(1.0, 2.0)*PI, Ease::linear), Ease::Val(45, 255.0, 0.0, Ease::linear), DX_BLENDMODE_ALPHA, Graph::get().handle("effect"), 0, 45),
hue(Random::Rand(30, 60))
{
}

void AllowEffect::draw()
{
	Func::SetDrawBrightHSV(hue, 80, 255);
	MyDraw::exrot3(pos(), center, exRate(), angle(), gHandle, alpha(), turnFlag, blendMode);
	Func::SetDrawBrightInt(0xFFFFFF);
}