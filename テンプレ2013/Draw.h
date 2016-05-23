#pragma once

#include <string>
#include <DxLib.h>

class Vector2;

namespace MyDraw{
	//通常の描画・座標は左上を指定
	void normal(int x, int y, int GrHandle, int Alpha = 255, int BlendMode = DX_BLENDMODE_ALPHA);

	//画像の中央の座標を指定して描画
	void center(int x, int y, int GrHandle, int Alpha = 255, int TurnFlag = 0, int BlendMode = DX_BLENDMODE_ALPHA);

	//拡大・回転描画
	void exrot(int x, int y, double ExtRate, double Angle, int GrHandle, int Alpha = 255, int TurnFlag = 0, int BlendMode = DX_BLENDMODE_ALPHA);

	//拡大・回転・中央指定描画
	void exrot3(int x, int y, int cx, int cy, double ExtRateX, double ExtRateY, double Angle, int GrHandle, int Alpha = 255, int TurnFlag = 0, int BlendMode = DX_BLENDMODE_ALPHA);

	//自由変形描画
	void modi(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int GrHandle, int Alpha = 255, int BlendMode = DX_BLENDMODE_ALPHA);

	//左上・右下を指定して描画
	void modi2(int x1, int y1, int x2, int y2, int GrHandle, int Alpha = 255, int BlendMode = DX_BLENDMODE_ALPHA);

	//楕円上にグラフを描画　rで円の半径・rate:縦にrをrateの比の分ひしゃげさせる・angle:回転角
	void modiOval(double x, double y, double r, double rate, double angle, int GrHandle, int Alpha = 255, int BlendMode = DX_BLENDMODE_ALPHA);

	//画像の指定した部分のみ描画　描画座標・左上座標・描画画像サイズ
	void trim(int DestX, int DestY, int SrcX, int SrcY, int Width, int Height, int GrHandle, int Alpha = 255, int TurnFlag = 0, int BlendMode = DX_BLENDMODE_ALPHA);

	//サークルゲージ描画　(dx, dy)分シフト
	void circlegauge(int x, int y, double percent, int GrHandle, int Alpha = 255, int BlendMode = DX_BLENDMODE_ALPHA);

	//サークルゲージ描画（逆方向）　(dx, dy)分シフト
	void circlegauge_rev(int x, int y, double percent, int GrHandle, int Alpha = 255, int BlendMode = DX_BLENDMODE_ALPHA);

	//図形描画関数

	//線を描画
	void line(int sx, int sy, int ex, int ey, int color, int Alpha = 255, int Thickness = 1, int BlendMode = DX_BLENDMODE_ALPHA);

	//独自
	//始点と終点への距離、角度を指定して線を描画
	void lineangle(int sx, int sy, int r, double angle, int color, int Alpha = 255, int Thickness = 1, int BlendMode = DX_BLENDMODE_ALPHA);

	//箱を描画
	void box(int x1, int y1, int x2, int y2, int color, int Alpha = 255, int BlendMode = DX_BLENDMODE_ALPHA);

	//独自
	//中心を指定して箱を描画
	void centerbox(double centerx, double centery, double width, double height, int color, int Alpha = 255, int BlendMode = DX_BLENDMODE_ALPHA);

	//円を描画
	void circle(int x, int y, int r, int color, int Alpha = 255, int BlendMode = DX_BLENDMODE_ALPHA);

	//三角形を描画
	void triangle(int x1, int y1, int x2, int y2, int x3, int y3, int color, int Alpha = 255, int BlendMode = DX_BLENDMODE_ALPHA);


	//文字描画関数

	//文字を描画
	void text(int x, int y, int color, int font_handle, const std::string &str, int Alpha = 255, int BlendMode = DX_BLENDMODE_ALPHA);

	//指定した座標を中心に文字を描画
	void centertext(int x, int y, int color, int font_handle, const std::string &str, int Alpha = 255, int BlendMode = DX_BLENDMODE_ALPHA);

	//文字の右上の座標を指定して文字を描画
	void righttext(int x, int y, int color, int font_handle, const std::string &str, int Alpha = 255, int BlendMode = DX_BLENDMODE_ALPHA);

	//指定した座標を中心に文字を描画 文字の間隔を指定可能
	void centertext_space(int x, int y, int color, int font_handle, int space, const std::string &str, int Alpha = 255, int BlendMode = DX_BLENDMODE_ALPHA);



	//Vector2使用

	//通常の描画・座標は左上を指定
	void normal(const Vector2& pos, int GrHandle, int Alpha = 255, int BlendMode = DX_BLENDMODE_ALPHA);

	//画像の中央の座標を指定して描画
	void center(const Vector2& pos, int GrHandle, int Alpha = 255, int TurnFlag = 0, int BlendMode = DX_BLENDMODE_ALPHA);

	//拡大・回転描画
	void exrot(const Vector2& pos, double ExtRate, double Angle, int GrHandle, int Alpha = 255, int TurnFlag = 0, int BlendMode = DX_BLENDMODE_ALPHA);

	//拡大・回転・中央指定描画
	void exrot3(const Vector2& pos, const Vector2& center_pos, const Vector2& Exrate_vec, double Angle, int GrHandle, int Alpha = 255, int TurnFlag = 0, int BlendMode = DX_BLENDMODE_ALPHA);

	//自由変形描画
	void modi(const Vector2& pos1, const Vector2& pos2, const Vector2& pos3, const Vector2& pos4, int GrHandle, int Alpha = 255, int BlendMode = DX_BLENDMODE_ALPHA);

	//左上・右下を指定して描画
	void modi2(const Vector2& pos1, const Vector2& pos2, int GrHandle, int Alpha = 255, int BlendMode = DX_BLENDMODE_ALPHA);

	//楕円上にグラフを描画　rで円の半径・rate:縦にrをrateの比の分ひしゃげさせる・angle:回転角
	void modiOval(const Vector2& pos, double r, double rate, double angle, int GrHandle, int Alpha = 255, int BlendMode = DX_BLENDMODE_ALPHA);

	//画像の指定した部分のみ描画　描画座標・左上座標・描画画像サイズ
	void trim(const Vector2& pos, const Vector2& graph_ul_pos, const Vector2& size, int GrHandle, int Alpha = 255, int TurnFlag = 0, int BlendMode = DX_BLENDMODE_ALPHA);

	//サークルゲージ描画　(dx, dy)分シフト
	void circlegauge(const Vector2& pos, double percent, int GrHandle, int Alpha = 255, int BlendMode = DX_BLENDMODE_ALPHA);

	//サークルゲージ描画（逆方向）　(dx, dy)分シフト
	void circlegauge_rev(const Vector2& pos, double percent, int GrHandle, int Alpha = 255, int BlendMode = DX_BLENDMODE_ALPHA);

	//図形描画関数

	//線を描画
	void line(const Vector2& start_pos, const Vector2& end_pos, int color, int Alpha = 255, int Thickness = 1, int BlendMode = DX_BLENDMODE_ALPHA);

	//独自
	//始点と終点への距離、角度を指定して線を描画
	void lineangle(const Vector2& start_pos, int r, double angle, int color, int Alpha = 255, int Thickness = 1, int BlendMode = DX_BLENDMODE_ALPHA);

	//箱を描画
	void box(const Vector2& pos1, const Vector2& pos2, int color, int Alpha = 255, int BlendMode = DX_BLENDMODE_ALPHA);

	//独自
	//中心を指定して箱を描画
	void centerbox(const Vector2& center_pos, const Vector2& size, int color, int Alpha = 255, int BlendMode = DX_BLENDMODE_ALPHA);

	//円を描画
	void circle(const Vector2& pos, int r, int color, int Alpha = 255, int BlendMode = DX_BLENDMODE_ALPHA);

	//三角形を描画
	void triangle(const Vector2& pos1, const Vector2& pos2, const Vector2& pos3, int color, int Alpha = 255, int BlendMode = DX_BLENDMODE_ALPHA);


	//文字描画関数

	//文字を描画
	void text(const Vector2& pos, int color, int font_handle, const std::string &str, int Alpha = 255, int BlendMode = DX_BLENDMODE_ALPHA);

	//指定した座標を中心に文字を描画
	void centertext(const Vector2& pos, int color, int font_handle, const std::string &str, int Alpha = 255, int BlendMode = DX_BLENDMODE_ALPHA);
	void centertext(const Vector2& pos, int color, int font_handle, int fontSize, const std::string &str, int Alpha = 255, int BlendMode = DX_BLENDMODE_ALPHA);

	//文字の右上の座標を指定して文字を描画
	void righttext(const Vector2& pos, int color, int font_handle, const std::string &str, int Alpha = 255, int BlendMode = DX_BLENDMODE_ALPHA);

	//指定した座標を中心に文字を描画 文字の間隔を指定可能
	void centertext_space(const Vector2& pos, int color, int font_handle, int space, const std::string &str, int Alpha = 255, int BlendMode = DX_BLENDMODE_ALPHA);

	void fade(const Vector2 &pos, int gHandle1, int gHandle2, int nowFrame, int maxFrame, bool turnFlag = false, int BlendMode = DX_BLENDMODE_ALPHA);
	void fade_popin(const Vector2 &pos, int gHandle1, int gHandle2, int nowFrame, int maxFrame, int popinTime, bool turnFlag = false, int BlendMode = DX_BLENDMODE_ALPHA);
	void fade_fadeout(const Vector2 &pos, int gHandle1, int gHandle2, int nowFrame, int maxFrame, int fadeStartTime, int fadeEndTime, bool turnFlag = false, int BlendMode = DX_BLENDMODE_ALPHA);

	void animation(const Vector2 &pos, int gHandle1, int gHandle2, int nowFrame, int intervalFrame, bool turnFlag = false, int BlendMode = DX_BLENDMODE_ALPHA);
}