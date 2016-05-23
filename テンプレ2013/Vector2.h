#pragma once

#include <string>
#include <vector>
#include <memory>

//2次元上の点を表すクラス

class Rectangular;

class Vector2
{
public:
	double x;
	double y;

	//コンストラクタ定義
	Vector2();
	Vector2(double x_, double y_);

	//オペレーターオーバーロード
	Vector2& operator +=(const Vector2& t);
	Vector2& operator -=(const Vector2& t);
	Vector2 operator +(const Vector2& t);
	Vector2 operator -(const Vector2& t);
	Vector2 operator *(double t);
	Vector2 operator /(double t);
	Vector2& operator *=(double t);
	Vector2& operator /=(double t);

	//内積
	double operator *(const Vector2& t);

	//外積
	double cross(const Vector2& t);

	//操作関数
	void Set(double x_, double y_);

	//原点を中心に回転
	void Rotate(double rad);

	//centerを中心に回転
	void RotateOnPoint(double rad, const Vector2 &center);

	//原点を中心にベクトルを回転したものを返す
	Vector2 GetRotate(double rad);

	//centerを中心に回転したベクトルを返す
	Vector2 GetRotateOnPoint(double rad, const Vector2 &center);

	//dx,dy分だけ移動
	void Translate(double dx, double dy);

	//ベクトルの大きさを返す
	double Magnitude();

	//ベクトルを正規化する
	void Normalize();

	//正規化されたベクトルを返す
	Vector2 GetNormalized();

	//ベクトルの角度を返す
	double GetAngle();

	//極座標系式で表されたベクトルを返す static
	static Vector2 GetPolar(double r, double angle);

	//指定した範囲内にベクトルを修正
	void maximize(double xMin, double xMax, double yMin, double yMax);
	void maximize(Vector2 Min, Vector2 Max);
	void maximize(Rectangular range);

	//y軸対象
	Vector2 symmetry_y();

};

class Rectangular{
	Vector2 start;
	Vector2 end;
	int onMouseTime;
	int clickedTime;
	int existTime;
	int alpha;
	int ratioTime;

	bool is_on_mouse();
	bool is_clicked();

public:

	Rectangular();
	Rectangular(Vector2 s, Vector2 e);

	void update();

	bool get_clicked_down();
	bool get_clicked();
	bool get_on_mouse_down();
	bool get_on_mouse();

	void set(Vector2 s, Vector2 e);
	void set(double x1, double y1, double x2, double y2);
	void set_size(Vector2 s, Vector2 size);
	void set_center(Vector2 center, Vector2 size);
	void set_ratio_time(int rT);
	void move(Vector2 dis);

	bool is_in(double x, double y);
	bool is_in(Vector2 point);
	
	void draw();
	void draw(int gHandle);
	void draw_ratio(int gHandle);
	void draw_clicked(int gHandle1, int gHandle2);
	void draw_on_mouse(int gHandle1, int gHandle2);
	void draw_ratio_on_mouse(int gHandle, double ratio1, double ratio2, int time);
	void draw_ratio_on_mouse(int gHandle1, int gHandle2, double ratio1, double ratio2, int time);
	void draw_ratio_on_mouse_alpha(int gHandle1, int gHandle2, double ratio1, double ratio2, int ratioTime, int alphaTime);
	void draw_ratio_on_mouse_alpha_fadein(int gHandle1, int gHandle2, double ratio1, double ratio2, int ratioTime, int alphaTime, int fadeTime);
	void draw_alpha_on_mouse(int gHandle);
	void draw_alpha_on_mouse(int gHandle, int alphaTime);
	void draw(std::string str, int color, int fontHandle);
	void draw(std::string str, int color, int fontHandle, int fontSize);
	void draw_debug(std::string str);

	bool is_draw_finished();

	Vector2 get_start();
	Vector2 get_end();
	Vector2 get_center();
	Vector2 get_size();

	Vector2 rand();
};

class Que
{
	class Point
	{
	public:
		Point(int gHandle);

		int graphHandle;
		int t;
		bool swich;

		void draw(Vector2 p);
		void draw_ratio(Vector2 p, int time);
	};

	Vector2 firstCenter;
	Vector2 duration;
	std::vector<std::shared_ptr<Point>> vec;

public:
	Que();
	Que(Vector2 f, Vector2 d, int gH, int num);

	void set(Vector2 f, Vector2 d, int gH, int num);
	void set(double fx, double fy, double dx, double dy, int gH, int num);
	void set(int num);
	void set(int num, bool f);
	void set(int s, int e);
	void draw();
	void draw(int num);
	void draw(int s, int e);
	void draw_ratio(int num, int time);
};

class Circle
{
	Vector2 center;
	double range;

	int onMouseTime;
	int clickedTime;
	int existTime;
	int alpha;
	int ratioTime;

	bool is_on_mouse();
	bool is_clicked();

public:
	Circle(Vector2 c, double r);
	Circle(double x, double y, double r);

	void update();

	bool get_clicked_down();
	bool get_clicked();
	bool get_on_mouse_down();
	bool get_on_mouse();

	void set(Vector2 c, double r);
	void set(double x, double y, double r);
	Vector2 get_center();
	double get_range();
	Circle symmetry_y(Vector2 outerCenter);
	Circle slide(Vector2 outerCenter);
	Vector2 get_random();

	void draw();
	void draw(double x, double y);
	void draw(Vector2 outerCenter);
	bool is_in(double x, double y);
	bool is_in(Vector2 point);
	bool is_in(Vector2 point, Vector2 camera);
};