#pragma once

#include<memory>
#include<string>
#include<DxLib.h>
#include <typeinfo.h>
#include <random>
#include <chrono>

class Vector2;

//Sound名前空間




//
//namespace Sound{
//	void loop_play(std::string name);
//	void loop_play(int sHandle);
//	void back_play(std::string name);
//	void back_play(int sHandle);
//	void stop_play(int sHandle);
//	void check_stop_play(int sHandle);
//	bool check_play(int sHandle);
//}


namespace Func{
	//当たり判定

	//2乗
	template<typename T> T Sqr(T x);
	//内積計算
	template<typename T> T Dot2D(T Ax, T Ay, T Bx, T By);

	//外積計算
	template<typename T> T Cross2D(T Ax, T Ay, T Bx, T By);


	//追加
	//点と円
	bool PointCircle(const Vector2& point_pos, const Vector2& circle_center, double radius);

	//円形同士
	bool Circles(double x1, double y1, double r1, double x2, double y2, double r2);

	bool Circles(const Vector2& c1, double r1, const Vector2& c2, double r2);

	//矩形同士
	bool Boxes(double a1x, double a1y, double a2x, double a2y, double b1x, double b1y, double b2x, double b2y);

	bool Boxes(const Vector2& a1, const Vector2& a2, const Vector2& b1, const Vector2& b2);

	//点と幅のある線 (点の座標、幅のある線の始点・終点)
	bool BroadLinePoint(double px, double py, double line_sx, double line_sy, double line_ex, double line_ey, double broad);

	//点と幅のある線 (点の座標、幅のある線の始点・終点までの距離、角度)
	bool BroadLinePointAng(double px, double py, double line_sx, double line_sy, double e_r, double e_ang, double broad);

	//点と矩形
	bool BoxPoint(int px, int py, int box_cx, int box_cy, int box_width, int box_height);

	//点と矩形
	bool BoxPoint(const Vector2& p_pos, const Vector2& box_pos, const Vector2& box_size);

	//普通の点と矩形
	bool DotAndRect(double px, double py, double b1x, double b1y, double b2x, double b2y);

	//円(半径cr,(cx,cy))の近似正方形と　長方形(左上(rx1,ry1), 右下(rx2, ry2))の当たり判定
	bool CircleAndRect(double cx, double cy, double cr, double rx1, double ry1, double rx2, double ry2);

	//線分同士(0ならあたってない、0以上はあたってる
	double Lines(double a_x, double a_y, double b_x, double b_y, double c_x, double c_y, double d_x, double d_y);

	//Linesで当たってた場合は位置を計算できる
	Vector2 LinesCalcCrossPoint(double lines_result, double a_x, double a_y, double b_x, double b_y);

	//円と線分
	bool CircleAndLine(double cx, double cy, double r, double sx, double sy, double ex, double ey);


	//ベクトル

	//原点を中心にang分回転
	void rotateonzero(double &x, double &y, double ang);

	//ある点(centerx,centery)を中心にang分回転
	void rotateonpoint(double &x, double &y, double centerx, double centery, double ang);

	//(原点から(sx,sy)への単位ベクトルを求める
	void normalizedVector(double &vx, double &vy, double sx, double sy);

	//(sx,sy)から(ex,ey)への単位ベクトルを求める
	void normalizedVector(double &vx, double &vy, double sx, double sy, double ex, double ey);

	//(dx,dy)方向、大きさdistのベクトルを求め、結果をresultに代入
	void calVector(double sx, double sy, double ex, double ey, double dist, double &resultx, double &resulty);

	//(dx,dy)方向、大きさdistのベクトルを求め、結果をresultに加算
	void addVector(double sx, double sy, double ex, double ey, double dist, double &resultx, double &resulty);

	//(dx,dy)方向、大きさdistのベクトルを求め、結果をresultに加算
	void addVector(double r, double angle, double &resultx, double &resulty);

	//極座標表現からxy表現に直す
	void polartoxy(double &x, double &y, double r, double ang);

	//角度を計算
	double calAngle(double x, double y);

	//角度を計算
	double calAngle(double sx, double sy, double ex, double ey);

	/*
	startx : 開始の値(開始時の座標やスケールなど)
	enddif : 開始と終了の値の差分
	time_now : 現在の時間
	time_end : Tweenの合計時間
	*/

	//／＼　←こういうグラフ
	double linef(double startx, double dif, double time_now, double time_end);

	//／＼　←こういう2次曲線
	double quadraticf(double startx, double dif, double time_now, double time_end);

	//3点を通る直線グラフ
	double graph3(double x0, double x1, double x2, double t1, double t_now, double t_end);

	//4点を通る直線グラフ
	double graph4(double x0, double x1, double x2, double x3, double t1, double t2, double t_now, double t_end);


	//イージング曲線

	/*
	t : 現在の時間
	b : 開始の値(開始時の座標やスケールなど)
	c : 開始と終了の値の差分
	d : Tweenの合計時間
	*/

	//イージング曲線 Cubic
	double ease_cubic_in(double t, double b, double c, double d);

	double ease_cubic_out(double t, double b, double c, double d);

	double ease_cubic_inout(double t, double b, double c, double d);


	//イージング曲線 Sinusoidal
	double ease_sin_in(double t, double b, double c, double d);

	double ease_sin_out(double t, double b, double c, double d);

	double ease_sin_inout(double t, double b, double c, double d);

	//イージング曲線 Exponential
	double ease_exp_in(double t, double b, double c, double d);

	double ease_exp_out(double t, double b, double c, double d);

	double ease_exp_inout(double t, double b, double c, double d);

	//イージング曲線 Circular
	double ease_sqrt_in(double t, double b, double c, double d);

	double ease_sqrt_out(double t, double b, double c, double d);

	double ease_sqrt_inout(double t, double b, double c, double d);



	//ベジェ曲線  p1->p2->p3  0<t<1
	double bz_curve(double p1, double p2, double p3, double t);

	//ベジェ曲線  p1->p2->p3  nowtime, endtime
	double bz_curve(double p1, double p2, double p3, double nowt, double endt);

	//アニメーション用・＼／＼／＼／となるグラフ
	int Repeat(int frame, int loop_num);

	//2次ベジエ曲線を計算する関数
	Vector2 GetBezier2(const Vector2& Start, const Vector2& Control
		, const Vector2& End, float t);

	//2次ベジエ曲線で制御点も通るように引きたい場合の制御点を返す関数
	Vector2 GetBezierPassC2(const Vector2 &Start, const Vector2 &End, const Vector2 &PassPoint);

	//Controlを通る2次ベジエ曲線を計算する関数
	Vector2 GetBezierCtrl2(const Vector2& Start, const Vector2& Control
		, const Vector2& End, float t);

	//3次ベジエ曲線を計算する関数
	Vector2 GetBezier3(const Vector2& Start, const Vector2& ControlPoint1
		, const Vector2& ControlPoint2, const Vector2& End, float t);

	//便利関数

	//HSVをRGBに換算 直接関数の引数に渡す用
	DWORD GetColorHSV(int h, int s, int v);

	//HSVをRGBに換算 intに保存する用
	int HSVtoRGB(int h, int s, int v);

	//HSVでsetdrawbright
	void SetDrawBrightHSV(int h, int s, int v);

	//0xXXXXXXでSetDrawBrightする関数
	void SetDrawBrightInt(int col);

	//自分の角度,相手の角度 2角の関係を返す　時計回り側に動いたほうが近ければ1 そうでなければ-1
	int abs_angle(double angle1, double angle2);

	//内分した点に移動、rateは自分から相手方向への移動率 0.0 - 1.0  tarxとの差がerange以下でtarx = xにする
	void moverate(double &x, double tarx, double rate, double erange = 1.0);

	//内分した点に移動、rateは自分から相手方向への移動率 0.0 - 1.0  distが0.5以下でtarP = Pにする
	void moverate(double &x, double &y, double tarx, double tary, double rate, double erangedist = 0.5);

	//内分した点に移動、rateは自分から相手方向への移動率 0.0 - 1.0  distが0.5以下でtarP = Pにする
	void moverate(Vector2 &v2, const Vector2 &tarv2, double rate, double erangedist = 0.5);


	//原点との距離を返す
	double dist(double x, double y);

	//2点の距離を返す
	double dist(double x1, double y1, double x2, double y2);

	//2点の距離の2乗を返す
	double distSqr(double x1, double y1, double x2, double y2);

	//rateとcoolのセットのcoolを更新・boolを返す
	bool coolcount(int &cool);

	//基準・振幅・周期(秒)・経過フレームを指定してsinを返す
	double sinsec(double base, double a, double t, double frame);

	void strReplace(std::string &target, const std::string &oldValue, const std::string &newValue);

	Vector2 getGraphSizeV2(int gHandle);
}

class Random{
private:
	std::mt19937 mt;
	Random();

public:
	Random(const Random& r) = delete;
	Random& operator=(const Random& r) = delete;

	static Random& get();

	//SeedSetUseRDでMTの初期値を設定
	static void SeedSetUseRD();

	//MTの初期値をRandom_deviceを使用して設定
	static void Initialize(int seed);

	//mtエンジン本体を取得
	static std::mt19937& getMT();

	//完全乱数
	static unsigned int RamdomDeviceValue();

	//通常のrand取得
	static int Rand();

	//0~max指定取得(int)
	static int Rand(int max);

	//min~maxを返す(int)
	static int Rand(int min, int max);

	//1か-1を返す関数
	static int RandPM1();

	//0~1を返す(double)
	static double Value();

	//0~maxを返す(double)
	static double FRand(double max);

	//min~maxを返す(double)
	static double FRand(double min, double max);

	//正規分布
	static double FRandND(double mean, double sigma);

	//正規分布 平均とレンジ指定
	static double FRandND(double mean, double sigma, double limit);

	//正規分布 平均とレンジ指定
	static double NormalDist(double ave, double range);

	//ラジアンで取得
	static double FRadRand();

	//ラジアンで取得
	static double FRadRand(double deg_min, double deg_max);

	//半径rの円上の点を返す
	static void RandOnCircle(double r, double &x, double &y);

	//半径rの円上の点を返す　原点からの角度も返す
	static void RandOnCircle(double r, double &x, double &y, double &ang);

	//半径rの円内部の点を返す
	static void RandInCircle(double r, double &x, double &y);

	//半径rの円内部の点を返す　原点からの角度も返す
	static void RandInCircle(double r, double &x, double &y, double &ang);

	//半径rの円上の点を返す
	static Vector2 RandOnCircle(double r);

	//半径r2の円から半径r1の円の領域を引いた領域上の点を返す
	static Vector2 RandOnCircle(double r1, double r2);

	//半径rの円内部の点を返す
	static Vector2 RandInCircle(double r);

	//スクリーンの端から50出た点をランダムに返す
	static Vector2 RandScreenEdge();

	//スクリーン上のランダムな点を返す
	static Vector2 RandInScreen();

	//pの確率でtrueを返す
	static bool RandBool(double p);

	static std::chrono::milliseconds RandChrono(std::chrono::milliseconds min, std::chrono::milliseconds max);
	
	static int posneg(double p);
	//ランダムなHSVを返す
//	static HSV RandHSV();
};