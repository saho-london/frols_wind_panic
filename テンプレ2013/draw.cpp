#include "draw.h"
#include "Vector2.h"
#include "myglobal.h"

//通常の描画・座標は左上を指定
void MyDraw::normal(int x, int y, int GrHandle, int Alpha, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawGraph(x, y, GrHandle, 1);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

//画像の中央の座標を指定して描画
void MyDraw::center(int x, int y, int GrHandle, int Alpha, int TurnFlag, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawRotaGraph(x, y, 1.0, 0.0, GrHandle, 1, TurnFlag);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

//拡大・回転描画
void MyDraw::exrot(int x, int y, double ExtRate, double Angle, int GrHandle, int Alpha, int TurnFlag, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawRotaGraph(x, y, ExtRate, Angle, GrHandle, 1, TurnFlag);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

//拡大・回転・中央指定描画
void MyDraw::exrot3(int x, int y, int cx, int cy, double ExtRateX, double ExtRateY, double Angle, int GrHandle, int Alpha, int TurnFlag, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawRotaGraph3(x, y, cx, cy, ExtRateX, ExtRateY, Angle, GrHandle, 1, TurnFlag);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

//自由変形描画
void MyDraw::modi(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int GrHandle, int Alpha, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawModiGraph(
		x1, y1, x2, y2,
		x3, y3, x4, y4,
		GrHandle, 1);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

//左上・右下を指定して描画
void MyDraw::modi2(int x1, int y1, int x2, int y2, int GrHandle, int Alpha, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawExtendGraph(x1, y1, x2, y2, GrHandle, 1);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

//楕円上にグラフを描画　rで円の半径・rate:縦にrをrateの比の分ひしゃげさせる・angle:回転角
void MyDraw::modiOval(double x, double y, double r, double rate, double angle, int GrHandle, int Alpha, int BlendMode){
	float gx[4];
	float gy[4];
	float dr = PI * -0.75;
	for (int i = 0; i < 4; i++){
		float dangle = PI * 0.5;
		gx[i] = x + r * cos(angle + i * dangle - dr);
		gy[i] = y + rate * r * sin(angle + i * dangle - dr);
	}

	SetDrawBlendMode(BlendMode, Alpha);
	DrawModiGraphF(
		gx[0], gy[0],
		gx[1], gy[1],
		gx[2], gy[2],
		gx[3], gy[3], GrHandle, 1);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

//画像の指定した部分のみ描画　描画座標・左上座標・描画画像サイズ
void MyDraw::trim(int DestX, int DestY, int SrcX, int SrcY, int Width, int Height, int GrHandle, int Alpha, int TurnFlag, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawRectGraph(DestX, DestY, SrcX, SrcY, Width, Height, GrHandle, 1, TurnFlag);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

//サークルゲージ描画　(dx, dy)分シフト
void MyDraw::circlegauge(int x, int y, double percent, int GrHandle, int Alpha, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawCircleGauge(x, y, 100, GrHandle, 100 - percent);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

//サークルゲージ描画（逆方向）　(dx, dy)分シフト
void MyDraw::circlegauge_rev(int x, int y, double percent, int GrHandle, int Alpha, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawCircleGauge(x, y, percent, GrHandle);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

//図形描画関数

//線を描画
void MyDraw::line(int sx, int sy, int ex, int ey, int color, int Alpha, int Thickness, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawLine(sx, sy, ex, ey, color, Thickness);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

//独自
//始点と終点への距離、角度を指定して線を描画
void MyDraw::lineangle(int sx, int sy, int r, double angle, int color, int Alpha, int Thickness, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawLine(sx, sy, sx + r * cos(angle), sy + r * sin(angle), color, Thickness);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

//箱を描画
void MyDraw::box(int x1, int y1, int x2, int y2, int color, int Alpha, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawBox(x1, y1, x2, y2, color, 1);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

//独自
//中心を指定して箱を描画
void MyDraw::centerbox(double centerx, double centery, double width, double height, int color, int Alpha, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawBox(
		centerx - width / 2, centery - height / 2,
		centerx + width / 2, centery + height / 2,
		color, 1);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

//円を描画
void MyDraw::circle(int x, int y, int r, int color, int Alpha, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawCircle(x, y, r, color, 1);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

//三角形を描画
void MyDraw::triangle(int x1, int y1, int x2, int y2, int x3, int y3, int color, int Alpha, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawTriangle(x1, y1, x2, y2, x3, y3, color, 1);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}


//文字描画関数

//文字を描画
void MyDraw::text(int x, int y, int color, int font_handle, const std::string &str, int Alpha, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawFormatStringToHandle(x, y, color, font_handle, "%s", str.c_str());
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

//指定した座標を中心に文字を描画
void MyDraw::centertext(int x, int y, int color, int font_handle, const std::string &str, int Alpha, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	int wd = GetDrawFormatStringWidthToHandle(font_handle, "%s", str.c_str());
	DrawFormatStringToHandle(x - wd / 2, y, color, font_handle, "%s", str.c_str());
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

//文字の右上の座標を指定して文字を描画
void MyDraw::righttext(int x, int y, int color, int font_handle, const std::string &str, int Alpha, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	int wd = GetDrawFormatStringWidthToHandle(font_handle, "%s", str.c_str());
	DrawFormatStringToHandle(x - wd, y, color, font_handle, "%s", str.c_str());
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

//指定した座標を中心に文字を描画 文字の間隔を指定可能
void MyDraw::centertext_space(int x, int y, int color, int font_handle, int space, const std::string &str, int Alpha, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	int str_num = (int)(str.size());
	if ((str_num % 2) == 0){
		for (int i = 0; i < (int)(str_num); i++){
			double basex = -(double)(str_num / 2) * space + space / 2;
			centertext(x + i * space + basex, y, color, font_handle, str.substr(i, 1), Alpha, BlendMode);
		}
	}
	else{
		for (int i = 0; i < (int)(str_num); i++){
			double basex = -(double)(str_num / 2) * space;
			centertext(x + i * space + basex, y, color, font_handle, str.substr(i, 1), Alpha, BlendMode);
		}
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}



//Vector2使用

//通常の描画・座標は左上を指定
void MyDraw::normal(const Vector2& pos, int GrHandle, int Alpha, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawGraph(pos.x, pos.y, GrHandle, 1);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

//画像の中央の座標を指定して描画
void MyDraw::center(const Vector2& pos, int GrHandle, int Alpha, int TurnFlag, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawRotaGraph(pos.x, pos.y, 1.0, 0.0, GrHandle, 1, TurnFlag);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

//拡大・回転描画
void MyDraw::exrot(const Vector2& pos, double ExtRate, double Angle, int GrHandle, int Alpha, int TurnFlag, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawRotaGraph(pos.x, pos.y, ExtRate, Angle, GrHandle, 1, TurnFlag);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

//拡大・回転・中央指定描画
void MyDraw::exrot3(const Vector2& pos, const Vector2& center_pos, const Vector2& Exrate_vec, double Angle, int GrHandle, int Alpha, int TurnFlag, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawRotaGraph3(pos.x, pos.y, center_pos.x, center_pos.y, Exrate_vec.x, Exrate_vec.y, Angle, GrHandle, 1, TurnFlag);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

//自由変形描画
void MyDraw::modi(const Vector2& pos1, const Vector2& pos2, const Vector2& pos3, const Vector2& pos4, int GrHandle, int Alpha, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawModiGraph(
		pos1.x, pos1.y, pos2.x, pos2.y,
		pos3.x, pos3.y, pos4.x, pos4.y,
		GrHandle, 1);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

//左上・右下を指定して描画
void MyDraw::modi2(const Vector2& pos1, const Vector2& pos2, int GrHandle, int Alpha, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawExtendGraph(pos1.x, pos1.y, pos2.x, pos2.y, GrHandle, 1);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

//楕円上にグラフを描画　rで円の半径・rate:縦にrをrateの比の分ひしゃげさせる・angle:回転角
void MyDraw::modiOval(const Vector2& pos, double r, double rate, double angle, int GrHandle, int Alpha, int BlendMode){
	float gx[4];
	float gy[4];
	float dr = PI * -0.75;
	for (int i = 0; i < 4; i++){
		float dangle = PI * 0.5;
		gx[i] = pos.x + r * cos(angle + i * dangle - dr);
		gy[i] = pos.y + rate * r * sin(angle + i * dangle - dr);
	}

	SetDrawBlendMode(BlendMode, Alpha);
	DrawModiGraphF(
		gx[0], gy[0],
		gx[1], gy[1],
		gx[2], gy[2],
		gx[3], gy[3], GrHandle, 1);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

//画像の指定した部分のみ描画　描画座標・左上座標・描画画像サイズ
void MyDraw::trim(const Vector2& pos, const Vector2& graph_ul_pos, const Vector2& size, int GrHandle, int Alpha, int TurnFlag, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawRectGraph(pos.x, pos.y, graph_ul_pos.x, graph_ul_pos.y, size.x, size.y, GrHandle, 1, TurnFlag);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

//サークルゲージ描画　(dx, dy)分シフト
void MyDraw::circlegauge(const Vector2& pos, double percent, int GrHandle, int Alpha, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawCircleGauge(pos.x, pos.y, 100, GrHandle, 100 - percent);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

//サークルゲージ描画（逆方向）　(dx, dy)分シフト
void MyDraw::circlegauge_rev(const Vector2& pos, double percent, int GrHandle, int Alpha, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawCircleGauge(pos.x, pos.y, percent, GrHandle);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

//図形描画関数

//線を描画
void MyDraw::line(const Vector2& start_pos, const Vector2& end_pos, int color, int Alpha, int Thickness, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawLine(start_pos.x, start_pos.y, end_pos.x, end_pos.y, color, Thickness);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

//独自
//始点と終点への距離、角度を指定して線を描画
void MyDraw::lineangle(const Vector2& start_pos, int r, double angle, int color, int Alpha, int Thickness, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawLine(start_pos.x, start_pos.y, start_pos.x + r * cos(angle), start_pos.y + r * sin(angle), color, Thickness);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

//箱を描画
void MyDraw::box(const Vector2& pos1, const Vector2& pos2, int color, int Alpha, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawBox(pos1.x, pos1.y, pos2.x, pos2.y, color, 1);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

//独自
//中心を指定して箱を描画
void MyDraw::centerbox(const Vector2& center_pos, const Vector2& size, int color, int Alpha, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawBox(
		center_pos.x - size.x / 2, center_pos.y - size.y / 2,
		center_pos.x + size.x / 2, center_pos.y + size.y / 2,
		color, 1);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

//円を描画
void MyDraw::circle(const Vector2& pos, int r, int color, int Alpha, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawCircle(pos.x, pos.y, r, color, 1);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

//三角形を描画
void MyDraw::triangle(const Vector2& pos1, const Vector2& pos2, const Vector2& pos3, int color, int Alpha, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawTriangle(pos1.x, pos1.y, pos2.x, pos2.y, pos3.x, pos3.y, color, 1);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}


//文字描画関数

//文字を描画
void MyDraw::text(const Vector2& pos, int color, int font_handle, const std::string &str, int Alpha, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawFormatStringToHandle(pos.x, pos.y, color, font_handle, "%s", str.c_str());
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

//指定した座標を中心に文字を描画
void MyDraw::centertext(const Vector2& pos, int color, int font_handle, const std::string &str, int Alpha, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	int wd = GetDrawFormatStringWidthToHandle(font_handle, "%s", str.c_str());
	DrawFormatStringToHandle(pos.x - wd / 2, pos.y, color, font_handle, "%s", str.c_str());
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

void MyDraw::centertext(const Vector2& pos, int color, int font_handle, int fontSize, const std::string &str, int Alpha, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	int wd = GetDrawFormatStringWidthToHandle(font_handle, "%s", str.c_str());
	DrawFormatStringToHandle(pos.x - wd / 2, pos.y - fontSize / 2, color, font_handle, "%s", str.c_str());
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

//文字の右上の座標を指定して文字を描画
void MyDraw::righttext(const Vector2& pos, int color, int font_handle, const std::string &str, int Alpha, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	int wd = GetDrawFormatStringWidthToHandle(font_handle, "%s", str.c_str());
	DrawFormatStringToHandle(pos.x - wd, pos.y, color, font_handle, "%s", str.c_str());
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

//指定した座標を中心に文字を描画 文字の間隔を指定可能
void MyDraw::centertext_space(const Vector2& pos, int color, int font_handle, int space, const std::string &str, int Alpha, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	int str_num = (int)(str.size());
	if ((str_num % 2) == 0){
		for (int i = 0; i < (int)(str_num); i++){
			double basex = -(double)(str_num / 2) * space + space / 2;
			centertext(pos.x + i * space + basex, pos.y, color, font_handle, str.substr(i, 1), Alpha, BlendMode);
		}
	}
	else{
		for (int i = 0; i < (int)(str_num); i++){
			double basex = -(double)(str_num / 2) * space;
			centertext(pos.x + i * space + basex, pos.y, color, font_handle, str.substr(i, 1), Alpha, BlendMode);
		}
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

void MyDraw::fade(const Vector2 &pos, int gHandle1, int gHandle2, int nowFrame, int maxFrame, bool turnFlag, int BlendMode)
{
	center(pos, gHandle1, 255, turnFlag);
	center(pos, gHandle2, 255 * (double)nowFrame / (double)maxFrame, turnFlag);
}

void MyDraw::fade_popin(const Vector2 &pos, int gHandle1, int gHandle2, int nowFrame, int maxFrame, int popinTime ,bool turnFlag, int BlendMode)
{
	if (nowFrame < popinTime)
	{
		exrot((Vector2)pos, (double)nowFrame / (double)popinTime, 0.0, gHandle1, 255.0, turnFlag, BlendMode);
		exrot((Vector2)pos, (double)nowFrame / (double)popinTime, 0.0, gHandle2, 255.0 * (double)nowFrame / (double)maxFrame, turnFlag, BlendMode);
	}
	else
	{
		center(pos, gHandle1, 255, turnFlag);
		center(pos, gHandle2, 255 * (double)nowFrame / (double)maxFrame, turnFlag);
	}
}

void MyDraw::fade_fadeout(const Vector2 &pos, int gHandle1, int gHandle2, int nowFrame, int maxFrame, int fadeStartTime, int fadeEndTime, bool turnFlag, int BlendMode)
{
	if (nowFrame < fadeStartTime)
	{
		center(pos, gHandle1, 255, turnFlag);
		center(pos, gHandle2, 255 * (double)nowFrame / (double)maxFrame, turnFlag);
	}
	else if (nowFrame < fadeEndTime)
	{
		center(pos, gHandle1, 255.0 * (double)(fadeEndTime - nowFrame) / (double)(fadeEndTime - fadeStartTime), turnFlag);
		center(pos, gHandle2, 255.0 * (double)nowFrame / (double)maxFrame* (double)(fadeEndTime - nowFrame) / (double)(fadeEndTime - fadeStartTime), turnFlag);
	}
}

void MyDraw::animation(const Vector2 &pos, int gHandle1, int gHandle2, int nowFrame, int intervalFrame, bool turnFlag, int BlendMode)
{
	if (nowFrame % (2 * intervalFrame) < intervalFrame)
	{
		center(pos, gHandle1, 255, turnFlag);
	}
	else{ center(pos, gHandle2, 255, turnFlag); }
}