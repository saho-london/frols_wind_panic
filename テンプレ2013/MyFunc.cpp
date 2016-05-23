#include <iostream>

#include "MyFunc.h"
#include "Vector2.h"
#include "myglobal.h"


//当たり判定

//2乗
template<typename T> T Func::Sqr(T x)
{
	return x*x;
}
//内積計算
template<typename T> T Func::Dot2D(T Ax, T Ay, T Bx, T By)
{
	return Ax*Bx + Ay*By;
}
//外積計算
template<typename T> T Func::Cross2D(T Ax, T Ay, T Bx, T By)
{
	return Ax*By - Bx*Ay;
}


//追加
//点と円
bool Func::PointCircle(const Vector2& point_pos, const Vector2& circle_center, double radius)
{
	return Sqr(circle_center.x - point_pos.x) + Sqr(circle_center.y - point_pos.y) < Sqr(radius);
}

//円形同士
bool Func::Circles(double x1, double y1, double r1, double x2, double y2, double r2)
{
	return Sqr(x2 - x1) + Sqr(y2 - y1) < Sqr(r2 + r1);
}
bool Func::Circles(const Vector2& c1, double r1, const Vector2& c2, double r2)
{
	return Sqr(c2.x - c1.x) + Sqr(c2.y - c1.y) < Sqr(r2 + r1);
}
//矩形同士
bool Func::Boxes(double a1x, double a1y, double a2x, double a2y, double b1x, double b1y, double b2x, double b2y)
{
	return a1x < b2x && a1y < b2y && b1x < a2x && b1y < a2y;
}
bool Func::Boxes(const Vector2& a1, const Vector2& a2, const Vector2& b1, const Vector2& b2)
{
	return a1.x < b2.x && a1.y < b2.y && b1.x < a2.x && b1.y < a2.y;
}
//点と幅のある線 (点の座標、幅のある線の始点・終点)
bool Func::BroadLinePoint(double px, double py, double line_sx, double line_sy, double line_ex, double line_ey, double broad){
	double x, y, ang, width;
	x = px - line_sx;
	y = py - line_sy;
	ang = atan2(line_ey - line_sy, line_ex - line_sx);
	width = dist(line_sx, line_sy, line_ex, line_ey);

	rotateonzero(x, y, -ang);

	if (x > 0 && x < width && y > -broad && y < broad){
		return true;
	}
	else{
		return false;
	}
}

//点と幅のある線 (点の座標、幅のある線の始点・終点までの距離、角度)
bool Func::BroadLinePointAng(double px, double py, double line_sx, double line_sy, double e_r, double e_ang, double broad){
	double x, y;
	x = px - line_sx;
	y = py - line_sy;

	rotateonzero(x, y, -e_ang);

	if (x > 0 && x < e_r && y > -broad && y < broad){
		return true;
	}
	else{
		return false;
	}
}

//点と矩形
bool Func::BoxPoint(int px, int py, int box_cx, int box_cy, int box_width, int box_height){
	return abs(px - box_cx) < box_width / 2
		&& abs(py - box_cy) < box_height / 2;
}

//点と矩形
bool Func::BoxPoint(const Vector2& p_pos, const Vector2& box_pos, const Vector2& box_size){
	return abs(p_pos.x - box_pos.x) < box_size.x / 2
		&& abs(p_pos.y - box_pos.y) < box_size.y / 2;
}
//普通の点と矩形
bool Func::DotAndRect(double px, double py, double b1x, double b1y, double b2x, double b2y)
{
	return  b1x < px  && px < b2x
		&&  b1y < py  && py < b2y;
}

//円(半径cr,(cx,cy))の近似正方形と　長方形(左上(rx1,ry1), 右下(rx2, ry2))の当たり判定
bool Func::CircleAndRect(double cx, double cy, double cr, double rx1, double ry1, double rx2, double ry2){
	double rectx = (rx1 + rx2) / 2.0;
	double recty = (ry1 + ry2) / 2.0;
	return	cx > rx1 - cr && cy > ry1 - cr &&
		cx < rx2 + cr && cy < ry2 + cr;
}
//線分同士(0ならあたってない、0以上はあたってる
double Func::Lines(double a_x, double a_y, double b_x, double b_y, double c_x, double c_y, double d_x, double d_y)
{
	double c0;
	c0 = Cross2D(b_x - a_x, b_y - a_y, d_x - c_x, d_y - c_y);
	if (c0 == 0.0f)
		return 0.0f;
	double r0, r1;
	r0 = Cross2D(c_x - a_x, c_y - a_y, b_x - a_x, b_y - a_y) / c0;
	r1 = Cross2D(c_x - a_x, c_y - a_y, d_x - c_x, d_y - c_y) / c0;
	if (r0 >= 0.0f && r0 <= 1.0f && r1 >= 0.0f && r1 <= 1.0f)
		return r1;
	else
		return 0.0f;
}
//Linesで当たってた場合は位置を計算できる
Vector2 Func::LinesCalcCrossPoint(double lines_result, double a_x, double a_y, double b_x, double b_y)
{
	Vector2 AB(b_x - a_x, b_y - a_y);
	AB *= lines_result;
	AB.Translate(a_x, a_y);
	return AB;
}
//円と線分
bool Func::CircleAndLine(double cx, double cy, double r, double sx, double sy, double ex, double ey)
{
	if (distSqr(sx, sy, cx, cy) < r*r || distSqr(ex, ey, cx, cy) < r*r){
		return true;
	}
	else {
		double k = ey - sy;
		double l = ex - sx;
		if (!((k*cx - l*cy - k*sx + l*sy)*(k*cx - l*cy - k*sx + l*sy) < r * r * (k*k + l*l))){
			return false;
		}
		if (((sx - cx)*(ex - cx) + (sy - cy)*(ey - cy)) < 0){
			return true;
		}
	}
	return false;
}


//ベクトル

//原点を中心にang分回転
void Func::rotateonzero(double &x, double &y, double ang){
	double sx = x - 0;
	double sy = y - 0;
	x = sx * cos(ang) - sy * sin(ang) + 0;
	y = sx * sin(ang) + sy * cos(ang) + 0;
}

//ある点(centerx,centery)を中心にang分回転
void Func::rotateonpoint(double &x, double &y, double centerx, double centery, double ang){
	double sx = x - centerx;
	double sy = y - centery;
	x = sx * cos(ang) - sy * sin(ang) + centerx;
	y = sx * sin(ang) + sy * cos(ang) + centery;
}

//(原点から(sx,sy)への単位ベクトルを求める
void Func::normalizedVector(double &vx, double &vy, double sx, double sy){
	double rd = atan2(sy, sx);
	vx = cos(rd);
	vy = sin(rd);
}

//(sx,sy)から(ex,ey)への単位ベクトルを求める
void Func::normalizedVector(double &vx, double &vy, double sx, double sy, double ex, double ey){
	double rd = atan2(ey - sy, ex - sx);
	vx = cos(rd);
	vy = sin(rd);
}

//(dx,dy)方向、大きさdistのベクトルを求め、結果をresultに代入
void Func::calVector(double sx, double sy, double ex, double ey, double dist, double &resultx, double &resulty){
	double rd = atan2(ey - sy, ex - sx);
	resultx = dist * cos(rd);
	resulty = dist * sin(rd);
}

//(dx,dy)方向、大きさdistのベクトルを求め、結果をresultに加算
void Func::addVector(double sx, double sy, double ex, double ey, double dist, double &resultx, double &resulty){
	double rd = atan2(ey - sy, ex - sx);
	resultx += dist * cos(rd);
	resulty += dist * sin(rd);
}

//(dx,dy)方向、大きさdistのベクトルを求め、結果をresultに加算
void Func::addVector(double r, double angle, double &resultx, double &resulty){
	resultx += r * cos(angle);
	resulty += r * sin(angle);
}

//極座標表現からxy表現に直す
void Func::polartoxy(double &x, double &y, double r, double ang){
	x = r * cos(ang);
	y = r * sin(ang);
}

//角度を計算
double Func::calAngle(double x, double y){
	return atan2(y, x);
}

//角度を計算
double Func::calAngle(double sx, double sy, double ex, double ey){
	return atan2(ey - sy, ex - sx);
}

/*
startx : 開始の値(開始時の座標やスケールなど)
enddif : 開始と終了の値の差分
time_now : 現在の時間
time_end : Tweenの合計時間
*/

//／＼　←こういうグラフ
double Func::linef(double startx, double dif, double time_now, double time_end){
	return startx + (dif - startx) * (abs(time_end / 2 - time_now) / (time_end / 2));
}

//／＼　←こういう2次曲線
double Func::quadraticf(double startx, double dif, double time_now, double time_end){
	double x = time_now / time_end;
	return startx + (dif - startx) * -4 * (x * x - x);
}


//3点を通る直線グラフ
double Func::graph3(double x0, double x1, double x2, double t1, double t_now, double t_end){
	if (t_now < t1){
		return (x1 - x0) * t_now / t1 + x0;
	}
	else{
		return (x2 - x1) * (t_now - t1) / (t_end - t1) + x1;
	}
}

//4点を通る直線グラフ
double Func::graph4(double x0, double x1, double x2, double x3, double t1, double t2, double t_now, double t_end){
	if (t_now < t1){
		return (x1 - x0) * t_now / t1 + x0;
	}
	else if (t_now < t2){
		return (x2 - x1) * (t_now - t1) / (t2 - t1) + x1;
	}
	else{
		return (x3 - x2) * (t_now - t2) / (t_end - t2) + x2;
	}
}


//イージング曲線

/*
t : 現在の時間
b : 開始の値(開始時の座標やスケールなど)
c : 開始と終了の値の差分
d : Tweenの合計時間
*/

//イージング曲線 Cubic
double Func::ease_cubic_in(double t, double b, double c, double d){
	t /= d;
	return c*t*t*t + b;
}

double Func::ease_cubic_out(double t, double b, double c, double d){
	t /= d;
	t = t - 1;
	return c*(t*t*t + 1) + b;
}

double Func::ease_cubic_inout(double t, double b, double c, double d){
	t /= d / 2.0;
	if (t < 1){
		return c / 2.0*t*t*t + b;
	}
	else{
		t = t - 2;
		return c / 2.0 * (t*t*t + 2) + b;
	}
}


//イージング曲線 Sinusoidal
double Func::ease_sin_in(double t, double b, double c, double d){
	return -c * cos(t / d * (PI / 2.0)) + c + b;
}

double Func::ease_sin_out(double t, double b, double c, double d){
	return c * sin(t / d * (PI / 2.0)) + b;
}

double Func::ease_sin_inout(double t, double b, double c, double d){
	return -c / 2.0 * (cos(PI*t / d) - 1) + b;
}

//イージング曲線 Exponential
double Func::ease_exp_in(double t, double b, double c, double d){
	return c * pow(2.0, (10 * (t / d - 1))) + b;
}

double Func::ease_exp_out(double t, double b, double c, double d){
	return c * (-(pow(2.0, (-10.0 * t / d))) + 1) + b;
}

double Func::ease_exp_inout(double t, double b, double c, double d){
	t /= d / 2.0;
	if (t < 1)
		return c / 2.0 * pow(2.0, (10.0 * (t - 1))) + b;
	t = t - 1;
	return c / 2.0 * (-(pow(2.0, (-10 * t))) + 2) + b;
}

//イージング曲線 Circular
double Func::ease_sqrt_in(double t, double b, double c, double d){
	t /= d;
	return -c * (sqrt(1 - t*t) - 1) + b;
}

double Func::ease_sqrt_out(double t, double b, double c, double d){
	t /= d;
	t = t - 1;
	return c * sqrt(1 - t*t) + b;
}

double Func::ease_sqrt_inout(double t, double b, double c, double d){
	t /= d / 2.0;
	if (t < 1)
		return -c / 2.0 * (sqrt(1 - t*t) + 1);
	t = t - 2;
	return c / 2.0 * (sqrt(1 - t*t) + 1) + b;
}



//ベジェ曲線  p1->p2->p3  0<t<1
double Func::bz_curve(double p1, double p2, double p3, double t){
	double tp = 1 - t;
	return t*t*p3 + 2 * t*tp*p2 + tp*tp*p1;
}

//ベジェ曲線  p1->p2->p3  nowtime, endtime
double Func::bz_curve(double p1, double p2, double p3, double nowt, double endt){
	double t = nowt / endt;
	double tp = 1 - t;
	return t*t*p3 + 2 * t*tp*p2 + tp*tp*p1;
}

//アニメーション用・＼／＼／＼／となるグラフ
int Func::Repeat(int frame, int loop_num)
{
	--loop_num;
	frame = frame % (loop_num * 2);
	if (frame > loop_num)
		return loop_num * 2 - frame;
	else
		return frame;
}

//2次ベジエ曲線を計算する関数
Vector2 Func::GetBezier2(const Vector2& Start, const Vector2& Control
	, const Vector2& End, float t)
{
	Vector2 Result;
	// P = t^2*P0 + 2t(1-t)P1 + (1-t)^2P2
	Result.x = (t*t)*End.x + 2 * t*(1 - t)*Control.x + (1 - t)*(1 - t)*Start.x;
	Result.y = (t*t)*End.y + 2 * t*(1 - t)*Control.y + (1 - t)*(1 - t)*Start.y;
	return Result;
}

//2次ベジエ曲線で制御点も通るように引きたい場合の制御点を返す関数
Vector2 Func::GetBezierPassC2(const Vector2 &Start, const Vector2 &End, const Vector2 &PassPoint)
{
	Vector2 C;
	C.x = (4 * PassPoint.x - Start.x - End.x) / 2.0f;
	C.y = (4 * PassPoint.y - Start.y - End.y) / 2.0f;
	return C;
}

//Controlを通る2次ベジエ曲線を計算する関数
Vector2 Func::GetBezierCtrl2(const Vector2& Start, const Vector2& Control
	, const Vector2& End, float t)
{
	Vector2 C;//Controlを通る2次ベジエ曲線の制御点
	Vector2 Result;
	C.x = (4 * Control.x - Start.x - End.x) / 2.0f;
	C.y = (4 * Control.y - Start.y - End.y) / 2.0f;
	Result.x = (t*t)*End.x + 2 * t*(1 - t)*C.x + (1 - t)*(1 - t)*Start.x;
	Result.y = (t*t)*End.y + 2 * t*(1 - t)*C.y + (1 - t)*(1 - t)*Start.y;
	return Result;
}

//3次ベジエ曲線を計算する関数
Vector2 Func::GetBezier3(const Vector2& Start, const Vector2& ControlPoint1
	, const Vector2& ControlPoint2, const Vector2& End, float t)
{
	Vector2 Result;
	Result.x = (t*t*t)*End.x + 3 * t*t*(1 - t)*ControlPoint2.x
		+ 3 * t*(1 - t)*(1 - t)*ControlPoint1.x + (1 - t)*(1 - t)*(1 - t)*Start.x;
	Result.y = (t*t*t)*End.y + 3 * t*t*(1 - t)*ControlPoint2.y
		+ 3 * t*(1 - t)*(1 - t)*ControlPoint1.y + (1 - t)*(1 - t)*(1 - t)*Start.y;
	return Result;
}
//便利関数

//HSVをRGBに換算 直接関数の引数に渡す用
DWORD Func::GetColorHSV(int h, int s, int v){
	float f;
	int i, p, q, t;
	int rgb[3];

	i = ((int)floor(h / 60.0f)) % 6;
	f = (float)(h / 60.0f) - (float)floor(h / 60.0f);
	p = (int)(v * (1.0f - (s / 255.0f)));
	q = (int)(v * (1.0f - (s / 255.0f) * f));
	t = (int)(v * (1.0f - (s / 255.0f) * (1.0f - f)));

	switch (i){
	case 0: rgb[0] = v; rgb[1] = t; rgb[2] = p; break;
	case 1: rgb[0] = q; rgb[1] = v; rgb[2] = p; break;
	case 2: rgb[0] = p; rgb[1] = v; rgb[2] = t; break;
	case 3: rgb[0] = p; rgb[1] = q; rgb[2] = v; break;
	case 4: rgb[0] = t; rgb[1] = p; rgb[2] = v; break;
	case 5: rgb[0] = v; rgb[1] = p; rgb[2] = q; break;
	}

	return GetColor(rgb[0], rgb[1], rgb[2]);
}

//HSVをRGBに換算 intに保存する用
int Func::HSVtoRGB(int h, int s, int v){
	float f;
	int i, p, q, t;
	int rgb[3];

	i = ((int)floor(h / 60.0f)) % 6;
	f = (float)(h / 60.0f) - (float)floor(h / 60.0f);
	p = (int)(v * (1.0f - (s / 255.0f)));
	q = (int)(v * (1.0f - (s / 255.0f) * f));
	t = (int)(v * (1.0f - (s / 255.0f) * (1.0f - f)));

	switch (i){
	case 0: rgb[0] = v; rgb[1] = t; rgb[2] = p; break;
	case 1: rgb[0] = q; rgb[1] = v; rgb[2] = p; break;
	case 2: rgb[0] = p; rgb[1] = v; rgb[2] = t; break;
	case 3: rgb[0] = p; rgb[1] = q; rgb[2] = v; break;
	case 4: rgb[0] = t; rgb[1] = p; rgb[2] = v; break;
	case 5: rgb[0] = v; rgb[1] = p; rgb[2] = q; break;
	}

	return ((rgb[0]) << 16) + ((rgb[1]) << 8) + rgb[2];
}

//HSVでsetdrawbright
void Func::SetDrawBrightHSV(int h, int s, int v){
	float f;
	int i, p, q, t;
	int rgb[3];

	i = ((int)floor(h / 60.0f)) % 6;
	f = (float)(h / 60.0f) - (float)floor(h / 60.0f);
	p = (int)(v * (1.0f - (s / 255.0f)));
	q = (int)(v * (1.0f - (s / 255.0f) * f));
	t = (int)(v * (1.0f - (s / 255.0f) * (1.0f - f)));

	switch (i){
	case 0: rgb[0] = v; rgb[1] = t; rgb[2] = p; break;
	case 1: rgb[0] = q; rgb[1] = v; rgb[2] = p; break;
	case 2: rgb[0] = p; rgb[1] = v; rgb[2] = t; break;
	case 3: rgb[0] = p; rgb[1] = q; rgb[2] = v; break;
	case 4: rgb[0] = t; rgb[1] = p; rgb[2] = v; break;
	case 5: rgb[0] = v; rgb[1] = p; rgb[2] = q; break;
	}

	SetDrawBright(rgb[0], rgb[1], rgb[2]);
}

//0xXXXXXXでSetDrawBrightする関数
void Func::SetDrawBrightInt(int col){
	SetDrawBright(col >> 16, (col >> 8) & (0x00FF), col & 0x0000FF);
}

//自分の角度,相手の角度 2角の関係を返す　時計回り側に動いたほうが近ければ1 そうでなければ-1
int Func::abs_angle(double angle1, double angle2){
	if (sin(angle2 - angle1) > 0){
		return 1;
	}
	else{
		return -1;
	}
}

//内分した点に移動、rateは自分から相手方向への移動率 0.0 - 1.0  tarxとの差がerange以下でtarx = xにする
void Func::moverate(double &x, double tarx, double rate, double erange)
{
	x = x * (1 - rate) + tarx * rate;
	if (abs(x - tarx) < erange){
		x = tarx;
	}
}
//内分した点に移動、rateは自分から相手方向への移動率 0.0 - 1.0  distが0.5以下でtarP = Pにする
void Func::moverate(double &x, double &y, double tarx, double tary, double rate, double erangedist)
{
	x = x * (1 - rate) + tarx * rate;
	y = y * (1 - rate) + tary * rate;
	if (dist(x, y, tarx, tary) < erangedist){
		x = tarx;
		y = tary;
	}
}
//内分した点に移動、rateは自分から相手方向への移動率 0.0 - 1.0  distが0.5以下でtarP = Pにする
void Func::moverate(Vector2 &v2, const Vector2 &tarv2, double rate, double erangedist)
{
	v2.x = v2.x * (1 - rate) + tarv2.x * rate;
	v2.y = v2.y * (1 - rate) + tarv2.y * rate;
	if (dist(v2.x, v2.y, tarv2.x, tarv2.y) < erangedist){
		v2 = tarv2;
	}
}


//原点との距離を返す
double Func::dist(double x, double y){
	return sqrt(x*x + y*y);
}

//2点の距離を返す
double Func::dist(double x1, double y1, double x2, double y2){
	return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
}

//2点の距離の2乗を返す
double Func::distSqr(double x1, double y1, double x2, double y2){
	return (x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2);
}


//rateとcoolのセットのcoolを更新・boolを返す
bool Func::coolcount(int &cool){
	if (cool > 0){
		cool--;
		return false;
	}
	else{
		cool = 0;
		return true;
	}
}



//基準・振幅・周期(秒)・経過フレームを指定してsinを返す
double Func::sinsec(double base, double a, double t, double frame){
	return base + a * sin(2 * PI * frame / 60.0 / t);
}


void Func::strReplace(std::string &target, const std::string &oldValue, const std::string &newValue){
	auto beginIter = target.find(oldValue.c_str());
	if (beginIter != std::string::npos){
		auto endIter = beginIter + oldValue.size();
		target.replace(beginIter, endIter, newValue);
	}
}

Vector2 Func::getGraphSizeV2(int gHandle){
	int sx;
	int sy;
	GetGraphSize(gHandle, &sx, &sy);
	return Vector2(sx, sy);
}

//	//スクリーンの中心を返す
//	inline Vector2 GetScreenCenter(){
//		return Vector2(ScreenWidth / 2, ScreenHeight / 2);
//	}
//
//	//ランダムな2文字の大文字アルファベットを返す
//	std::string randStr(){
//		std::string str;
//		for (int i = 0; i < 2; i++){
//			str += (char)((int)'A' + GetRand(25));
//		}
//		return str;
//	}
//	//ランダムな2文字の大文字アルファベットを返す
//	std::string randStr(int loop){
//		std::string str;
//		for (int i = 0; i < loop; i++){
//			str += (char)((int)'A' + GetRand(25));
//		}
//		return str;
//	}
//
//	//スクリーンから出ているかを返す関数
//	bool isScreenOut(const Vector2 &pos){
//		return pos.x < 0 || pos.x > ScreenWidth
//			|| pos.y < 0 || pos.y > ScreenHeight;
//	}
//
//	//スクリーンからmarge外に出ているかを返す関数
//	bool isScreenOutMarge(const Vector2 &pos, int marge){
//		return pos.x < -marge || pos.x > ScreenWidth + marge
//			|| pos.y < -marge || pos.y > ScreenHeight + marge;
//	}

//class Random
Random::Random(){
	//SeedSetUseRDでMTの初期値を設定
	SeedSetUseRD();
}

Random& Random::get()
{
	static Random r;
	return r;
}

//MTの初期値をRandom_deviceを使用して設定
void Random::SeedSetUseRD(){
	std::random_device r;
	get().mt.seed(r());
}
//MTの初期値設定
void Random::Initialize(int seed)
{
	get().mt.seed(seed);
}
//mtエンジン本体を取得
std::mt19937& Random::getMT(){
	return get().mt;
}

//完全乱数
unsigned int Random::RamdomDeviceValue()
{
	std::random_device r;
	return r();
}

//通常のrand取得
int Random::Rand(){
	return get().mt();
}
//0~max指定取得(int)
int Random::Rand(int max)
{
	std::uniform_int_distribution<int> uid(0, max);
	return uid(get().mt);
}
//min~maxを返す(int)
int Random::Rand(int min, int max)
{
	if (min > max){
		int tmp = min;
		min = max;
		max = tmp;
	}
	std::uniform_int_distribution<int> uid(min, max);
	return uid(get().mt);
}
//1か-1を返す関数
int Random::RandPM1(){
	std::uniform_int_distribution<int> uid(0, 1);
	return uid(get().mt) * 2 - 1;
}
//0~1を返す(double)
double Random::Value()
{
	std::uniform_real_distribution<double> urd(0, 1);
	return urd(get().mt);
}
//0~maxを返す(double)
double Random::FRand(double max)
{
	if (max < 0.0){
		return 0.0;
	}
	std::uniform_real_distribution<double> urd(0, max);
	return urd(get().mt);
}
//min~maxを返す(double)
double Random::FRand(double min, double max)
{
	if (min > max){
		double tmp = min;
		min = max;
		max = tmp;
	}
	std::uniform_real_distribution<double> urd(min, max);
	return urd(get().mt);
}
//正規分布
double Random::FRandND(double mean, double sigma)
{
	std::normal_distribution<double> nd(mean, sigma);
	return nd(get().mt);
}
double Random::FRandND(double mean, double sigma, double limit)
{
	std::normal_distribution<double> nd(mean, sigma);
	double r = nd(get().mt);
	if (r < mean - limit)
		r = mean - limit;
	if (r > mean + limit)
		r = mean + limit;
	return r;
}
//正規分布 平均とレンジ指定
double Random::NormalDist(double ave, double range){
	std::normal_distribution<double> nd(ave, range / 3.0);
	double ret = nd(get().mt);
	if (ret < ave - range || ret > ave + range){
		ret = FRand(ave - range, ave + range);
	}
	return ret;
}

//ラジアンで取得
double Random::FRadRand()
{
	return FRand(-PI, PI);
}
double Random::FRadRand(double deg_min, double deg_max)
{
	return FRand(deg_min * DegToRad, deg_max * DegToRad);
}

//半径rの円上の点を返す
void Random::RandOnCircle(double r, double &x, double &y){
	double randang = FRadRand();
	x = r * cos(randang);
	y = r * sin(randang);
}
//半径rの円上の点を返す　原点からの角度も返す
void Random::RandOnCircle(double r, double &x, double &y, double &ang){
	double randang = FRadRand();
	x = r * cos(randang);
	y = r * sin(randang);
	ang = randang;
}
//半径rの円内部の点を返す
void Random::RandInCircle(double r, double &x, double &y){
	double randang = FRadRand();
	double rr = r * Value();
	x = rr * cos(randang);
	y = rr * sin(randang);
}
//半径rの円内部の点を返す　原点からの角度も返す
void Random::RandInCircle(double r, double &x, double &y, double &ang){
	double randang = FRadRand();
	double rr = r * Value();
	x = rr * cos(randang);
	y = rr * sin(randang);
	ang = randang;
}
//半径rの円上の点を返す
Vector2 Random::RandOnCircle(double r){
	Vector2 temp;
	double randang = FRadRand();
	temp.x = r * cos(randang);
	temp.y = r * sin(randang);
	return temp;
}
//半径rの円上の点を返す
Vector2 Random::RandOnCircle(double r1, double r2){
	Vector2 temp;
	double r = Random::FRand(r1, r2);
	double randang = FRadRand();
	temp.x = r * cos(randang);
	temp.y = r * sin(randang);
	return temp;
}
//半径rの円内部の点を返す
Vector2 Random::RandInCircle(double r){
	Vector2 temp;
	double randang = FRadRand();
	double rr = r * Value();
	temp.x = rr * cos(randang);
	temp.y = rr * sin(randang);
	return temp;
}

Vector2 Random::RandScreenEdge(){
	double marge = 50;
	double p = (double)SCREEN.y / (SCREEN.x + SCREEN.y);

	if (Random::RandBool(p)){
		if (Random::RandBool(0.5)){
			return Vector2(-marge, Random::FRand(SCREEN.y * 0.5));
		}
		else{
			return Vector2(SCREEN.x + marge, Random::FRand(SCREEN.y * 0.5));
		}
	}
	else{
		return Vector2(Random::FRand(SCREEN.x), -marge);
	}
}

Vector2 Random::RandInScreen(){
	return Vector2(Random::FRand(SCREEN.x), Random::FRand(SCREEN.y));
}


//pの確率でtrueを返す
bool Random::RandBool(double p){
	return Random::FRand(1.0) < p;
}

std::chrono::milliseconds Random::RandChrono(std::chrono::milliseconds min, std::chrono::milliseconds max)
{
	std::chrono::milliseconds temp(Random::Rand((int)min.count(), (int)max.count()));
	return temp;
}

int Random::posneg(double p)
{
	if (RandBool(p))
	{
		return 1;
	}
	else
	{
		return -1;
	}
}
//HSV Random::RandHSV(){
//	return HSV(Random::FRand(1.0), Random::FRand(1.0), Random::FRand(1.0));
//}