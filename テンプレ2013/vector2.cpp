#include "Vector2.h"
#include "draw.h"
#include "input.h"
#include "MyFunc.h"

//2次元上の点を表すクラス
//コンストラクタ定義
Vector2::Vector2() :x(0), y(0){}
Vector2::Vector2(double x_, double y_) : x(x_), y(y_){}

//オペレーターオーバーロード
Vector2& Vector2::operator +=(const Vector2& t)
{
	x += t.x;
	y += t.y;
	return *this;
}
Vector2& Vector2::operator -=(const Vector2& t)
{
	x -= t.x;
	y -= t.y;
	return *this;
}
Vector2 Vector2::operator +(const Vector2& t){
	Vector2 temp;
	temp.x = x + t.x;
	temp.y = y + t.y;
	return temp;
}
Vector2 Vector2::operator -(const Vector2& t){
	Vector2 temp;
	temp.x = x - t.x;
	temp.y = y - t.y;
	return temp;
}
Vector2 Vector2::operator *(double t){
	Vector2 temp;
	temp.x = x * t;
	temp.y = y * t;
	return temp;
}
Vector2 Vector2::operator /(double t){
	Vector2 temp;
	temp.x = x / t;
	temp.y = y / t;
	return temp;
}
Vector2& Vector2::operator *=(double t)
{
	x *= t;
	y *= t;
	return *this;
}
Vector2& Vector2::operator /=(double t)
{
	x /= t;
	y /= t;
	return *this;
}

//内積
double Vector2::operator *(const Vector2& t){
	return x * t.x + y * t.y;
}

//外積
double Vector2::cross(const Vector2& t){
	return x * t.y - y * t.x;
}

//操作関数
void Vector2::Set(double x_, double y_)
{
	x = x_; y = y_;
}
//原点を中心に回転
void Vector2::Rotate(double rad)
{
	double sint = sin(rad), cost = cos(rad);	//sinとcosの値
	double tx = x;	//一時格納
	x = cost * tx - sint * y;		// ( cosθ -sinθ) ( x )
	y = sint * tx + cost * y;		// ( sinθ xosθ ) ( y )
}
//centerを中心に回転
void Vector2::RotateOnPoint(double rad, const Vector2 &center)
{
	double sint = sin(rad), cost = cos(rad);	//sinとcosの値
	double tx = x - center.x;	//一時格納
	double ty = y - center.y;	//一時格納
	x = cost * tx - sint * ty + center.x;		// ( cosθ -sinθ) ( x )
	y = sint * tx + cost * ty + center.y;		// ( sinθ xosθ ) ( y )
}
//原点を中心にベクトルを回転したものを返す
Vector2 Vector2::GetRotate(double rad){
	Vector2 temp = *this;
	double sint = sin(rad), cost = cos(rad);	//sinとcosの値
	double tx = temp.x;	//一時格納
	temp.x = cost * tx - sint * temp.y;		// ( cosθ -sinθ) ( x )
	temp.y = sint * tx + cost * temp.y;		// ( sinθ xosθ ) ( y )
	return temp;
}

//centerを中心に回転したベクトルを返す
Vector2 Vector2::GetRotateOnPoint(double rad, const Vector2 &center){
	Vector2 temp = *this;
	double sint = sin(rad), cost = cos(rad);	//sinとcosの値
	double tx = temp.x - center.x;	//一時格納
	double ty = temp.y - center.y;	//一時格納
	temp.x = cost * tx - sint * ty + center.x;		// ( cosθ -sinθ) ( x )
	temp.y = sint * tx + cost * ty + center.y;		// ( sinθ xosθ ) ( y )
	return temp;
}

//dx,dy分だけ移動
void Vector2::Translate(double dx, double dy)
{
	x += dx;
	y += dy;
}
//ベクトルの大きさを返す
double Vector2::Magnitude(){
	return sqrt(x*x + y*y);
}
//ベクトルを正規化する
void Vector2::Normalize(){
	double r = sqrt(x*x + y*y);
	if (r < 0.01){
		r = 0.01;
	}
	x /= r;
	y /= r;
}

//正規化されたベクトルを返す
Vector2 Vector2::GetNormalized(){
	Vector2 temp = *this;
	double r = sqrt(x*x + y*y);
	if (r < 0.01){
		r = 0.01;
	}
	temp.x /= r;
	temp.y /= r;
	return temp;
}

//ベクトルの角度を返す
double Vector2::GetAngle(){
	return atan2(y, x);
}

//極座標系式で表されたベクトルを返す static
Vector2 Vector2::GetPolar(double r, double angle){
	Vector2 temp;
	temp.x = r * cos(angle);
	temp.y = r * sin(angle);
	return temp;
}

//指定した範囲内にベクトルを修正
void Vector2::maximize(double xMin, double xMax, double yMin, double yMax)
{
	if (x < xMin){ x = xMin; }
	if (x > xMax){ x = xMax; }
	if (y < yMin){ y = yMin; }
	if (y > yMax){ y = yMax; }
}

void Vector2::maximize(Vector2 Min, Vector2 Max)
{
	if (x < Min.x){ x = Min.x; }
	if (x > Max.x){ x = Max.x; }
	if (y < Min.y){ y = Min.y; }
	if (y > Max.y){ y = Max.y; }
}

void Vector2::maximize(Rectangular range)
{
	if (x < range.get_start().x){ x = range.get_start().x; }
	if (x > range.get_end().x){ x = range.get_end().x; }
	if (y < range.get_start().y){ y = range.get_start().y; }
	if (y > range.get_end().y){ y = range.get_end().y; }
}

Vector2 Vector2::symmetry_y()
{
	return Vector2(-x, y);
}

//void Sound::loop_play(std::string name)
//{
//	PlaySoundFile(name.c_str(), DX_PLAYTYPE_LOOP);
//}
//
//void Sound::loop_play(int sHandle)
//{
//	PlaySoundMem(sHandle, DX_PLAYTYPE_LOOP);
//}
//
//void Sound::back_play(std::string name)
//{
//	PlaySoundFile(name.c_str(), DX_PLAYTYPE_BACK);
//}
//
//void Sound::back_play(int sHandle)
//{
//	PlaySoundMem(sHandle, DX_PLAYTYPE_BACK);
//}
//
//void Sound::stop_play(int sHandle)
//{
//	StopSoundMem(sHandle);
//}
//
//void Sound::check_stop_play(int sHandle)
//{
//	if (check_play(sHandle))
//	{
//		stop_play(sHandle);
//	}
//}
//
//bool Sound::check_play(int sHandle)
//{
//	return CheckSoundMem(sHandle);
//}

Rectangular::Rectangular() :
start(),
end(),
onMouseTime(0),
clickedTime(0),
existTime(0),
alpha(0),
ratioTime(0)
{

}

Rectangular::Rectangular(Vector2 s, Vector2 e) :
start(s),
end(e),
onMouseTime(0),
clickedTime(0),
existTime(0),
alpha(0),
ratioTime(0)
{

}

bool Rectangular::is_on_mouse()
{
	return is_in(Input::get().mouse);
}

bool Rectangular::is_clicked()
{
	return is_in(Input::get().mouse) && Input::get().mouseState != 0;
}

void Rectangular::update()
{
	if (is_on_mouse())	{ onMouseTime++; }
	else { onMouseTime = 0; }
	if (is_clicked()){ clickedTime++; }
	else { clickedTime = 0; }
	existTime++;
}

bool Rectangular::get_clicked_down()
{
	return clickedTime == 1;
}

bool Rectangular::get_clicked()
{
	return clickedTime > 0;
}

bool Rectangular::get_on_mouse_down()
{
	return onMouseTime == 1;
}

bool Rectangular::get_on_mouse()
{
	return onMouseTime > 0;
}

void Rectangular::set(Vector2 s, Vector2 e)
{
	start = s;
	end = e;
}

void Rectangular::set(double x1, double y1, double x2, double y2)
{
	start.Set(x1, y1);
	end.Set(x2, y2);
}

void Rectangular::set_size(Vector2 s, Vector2 size)
{
	start = s;
	end = s + size;
}

void Rectangular::set_center(Vector2 center, Vector2 size)
{
	start = center - size / 2;
	end = center + size / 2;
}

void Rectangular::set_ratio_time(int rT)
{
	ratioTime = rT;
}

void Rectangular::move(Vector2 dis)
{
	start += dis;
	end += dis;
}

bool Rectangular::is_in(double x, double y){
	return  start.x < x  && x < end.x
		&&  start.y < y  && y < end.y;
}

bool Rectangular::is_in(Vector2 point)
{
	return  start.x < point.x  && point.x < end.x
		&&  start.y < point.y  && point.y < end.y;
}

void Rectangular::draw()
{
	MyDraw::box(start, end, 0xFFFFFF, 1);
}

void Rectangular::draw(int gHandle)
{
	MyDraw::center(get_center(), gHandle);
}

void Rectangular::draw_ratio(int gHandle)
{
	if (existTime <= ratioTime)
	{
		MyDraw::exrot(get_center(), (double)existTime / (double)ratioTime, 0, gHandle);
	}
	else
	{
		MyDraw::center(get_center(), gHandle);
	}
}

void Rectangular::draw_clicked(int gHandle1, int gHandle2)
{
	if (get_clicked())
	{
		MyDraw::center(get_center(), gHandle2);
	}
	else { MyDraw::center(get_center(), gHandle1); }
}

void Rectangular::draw_on_mouse(int gHandle1, int gHandle2)
{
	if (get_on_mouse())
	{
		MyDraw::center(get_center(), gHandle2);
	}
	else { MyDraw::center(get_center(), gHandle1); }
}

void Rectangular::draw_ratio_on_mouse(int gHandle, double ratio1, double ratio2, int time)
{
	if (get_on_mouse())
	{
		if (onMouseTime <= time)
		{
			MyDraw::exrot(get_center(), ((time - onMouseTime)*ratio1 + onMouseTime* ratio2) / time, 0, gHandle);
		}
		else
		{
			MyDraw::center(get_center(), gHandle);
		}
	}
	else
	{
		MyDraw::exrot(get_center(), ratio1, 0, gHandle);
	}
}

void Rectangular::draw_ratio_on_mouse(int gHandle1, int gHandle2, double ratio1, double ratio2, int time)
{
	if (get_on_mouse())
	{
		if (onMouseTime <= time)
		{
			MyDraw::exrot(get_center(), ((time - onMouseTime)*ratio1 + onMouseTime* ratio2) / time, 0, gHandle2);
		}
		else
		{
			MyDraw::center(get_center(), gHandle2);
		}
	}
	else
	{
		MyDraw::center(get_center(), gHandle1);
	}
}

void Rectangular::draw_ratio_on_mouse_alpha(int gHandle1, int gHandle2, double ratio1, double ratio2, int ratioTime, int alphaTime)
{
	int aT = (alphaTime / 2) * 2;
	if ((existTime % aT) < (aT / 2)){ alpha++; }
	else { alpha--; }

	if (get_on_mouse())
	{
		if (onMouseTime <= ratioTime)
		{
			MyDraw::exrot(get_center(), ((ratioTime - onMouseTime)*ratio1 + onMouseTime* ratio2) / ratioTime, 0, gHandle2, 255 - ((double)alpha / (double)(aT / 2))*128.0);
		}
		else
		{
			MyDraw::center(get_center(), gHandle2);
		}
	}
	else
	{
		MyDraw::center(get_center(), gHandle1, 255 - ((double)alpha / (double)(aT / 2))*128.0);
	}
}

void Rectangular::draw_ratio_on_mouse_alpha_fadein(int gHandle1, int gHandle2, double ratio1, double ratio2, int ratioTime, int alphaTime, int fadeTime)
{
	int aT = (alphaTime / 2) * 2;

	if (!get_on_mouse() && existTime < fadeTime)
	{
		MyDraw::center(get_center(), gHandle1, 255.0*((double)existTime/(double)fadeTime));
	}
	else
	{
		if (((existTime - fadeTime) % aT) < (aT / 2)){ alpha++; }
		else { alpha--; }

		if (get_on_mouse())
		{
			if (onMouseTime <= ratioTime)
			{
				MyDraw::exrot(get_center(), ((ratioTime - onMouseTime)*ratio1 + onMouseTime* ratio2) / ratioTime, 0, gHandle2, 255 - ((double)alpha / (double)(aT / 2))*128.0);
			}
			else
			{
				MyDraw::center(get_center(), gHandle2);
			}
		}
		else
		{
			MyDraw::center(get_center(), gHandle1, 255 - ((double)alpha / (double)(aT / 2))*128.0);
		}
	}
}


void Rectangular::draw_alpha_on_mouse(int gHandle)
{
	if (get_on_mouse())
	{
		MyDraw::center(get_center(), gHandle);
	}
	else
	{
		MyDraw::center(get_center(), gHandle, 127);
	}
}

void Rectangular::draw_alpha_on_mouse(int gHandle, int alphaTime)
{
	if (get_on_mouse())
	{
		if (onMouseTime < alphaTime)
		{
			MyDraw::center(get_center(), gHandle, 127 + 128 * ((double)onMouseTime / (double)alphaTime));
		}
		else MyDraw::center(get_center(), gHandle);
	}
	else
	{
		MyDraw::center(get_center(), gHandle, 127);
	}
}

void Rectangular::draw(std::string str, int color, int fontHandle)
{
	MyDraw::centertext((start + end) / 2, color, fontHandle, str, 255);
}

void Rectangular::draw(std::string str, int color, int fontHandle, int fontSize)
{
	MyDraw::centertext((start + end - Vector2(0, fontSize)) / 2, color, fontHandle, str, 255);
}

bool Rectangular::is_draw_finished()
{
	return existTime >= ratioTime;
}

Vector2 Rectangular::get_start()
{
	return start;
}

Vector2 Rectangular::get_end()
{
	return end;
}

Vector2 Rectangular::get_center()
{
	return (start + end) / 2;
}

Vector2 Rectangular::get_size()
{
	return start - end;
}

Vector2 Rectangular::rand()
{
	return Vector2(GetRand(end.x - start.x) + start.x, GetRand(end.y - start.y) + start.y);
}

Que::Point::Point(int gHandle) :
graphHandle(gHandle),
t(0),
swich(true)
{

}

void Que::Point::draw(Vector2 p)
{
	if (swich == true)
	{
		MyDraw::center(p, graphHandle);
	}
}

void Que::Point::draw_ratio(Vector2 p, int time)
{
	if (swich == true)
	{
		if (t <= time)
		{
			t++;
			MyDraw::exrot(p, (double)t / (double)time, 0, graphHandle);
		}
		else
		{
			MyDraw::center(p, graphHandle);
		}
	}
	else{ t = 0; }
}

Que::Que()
{
}

Que::Que(Vector2 f, Vector2 d, int gH, int num) :
firstCenter(f),
duration(d)
{
	for (int i = 0; i < num; i++)
	{
		vec.push_back(std::make_shared<Point>(gH));
	}
}

void Que::set(Vector2 f, Vector2 d, int gH, int num)
{
	firstCenter = f;
	duration = d;
	for (int i = 0; i < num; i++)
	{
		vec.push_back(std::make_shared<Point>(gH));
	}
}

void Que::set(double fx, double fy, double dx, double dy, int gH, int num)
{
	firstCenter.Set(fx, fy);
	duration.Set(dx, dy);
	for (int i = 0; i < num; i++)
	{
		vec.push_back(std::make_shared<Point>(gH));
	}
}

void Que::set(int num)
{
	if (num > vec.size())
	{
		for (auto element : vec)
		{
			element->swich = true;
		}
	}
	else
	{
		for (auto iter = vec.begin(); iter < vec.end(); iter++)
		{
			if (iter - vec.begin() < num)
			{
				(**iter).swich = true;
			}
			else
			{
				(**iter).swich = false;
			}
		}
	}
}

void Que::set(int num, bool f)
{
	if (num > vec.size())
	{
		for (auto element : vec)
		{
			element->swich = f;
		}
	}
	else
	{
		for (auto iter = vec.begin(); iter - vec.begin() < num; iter++){ (**iter).swich = f; }
	}
}

void Que::set(int s, int e)
{
	if (s > vec.size())
	{
		for (auto element : vec)
		{
			element->swich = false;
		}
	}
	else if (e > vec.size())
	{
		for (auto iter = vec.begin(); iter < vec.end(); iter++)
		{
			if (iter - vec.begin() < s)
			{
				(**iter).swich = false;
			}
			else
			{
				(**iter).swich = true;
			}
		}
	}
	else
	{
		for (auto iter = vec.begin(); iter < vec.end(); iter++)
		{
			if (iter - vec.begin() < s)
			{
				(**iter).swich = false;
			}
			else if (iter - vec.begin() < e)
			{
				(**iter).swich = true;
			}
			else
			{
				(**iter).swich = false;
			}
		}
	}
}

void Que::draw()
{
	for (auto iter = vec.begin(); iter < vec.end(); iter++)
	{
		(**iter).draw(firstCenter + duration*(iter - vec.begin()));
	}
}

void Que::draw(int num)
{
	set(num);
	for (auto iter = vec.begin(); iter < vec.end(); iter++)
	{
		(**iter).draw(firstCenter + duration*(iter - vec.begin()));
	}
}

void Que::draw(int s, int e)
{
	set(s, e);
	for (auto iter = vec.begin(); iter < vec.end(); iter++)
	{
		(**iter).draw(firstCenter + duration*(iter - vec.begin()));
	}
}

void Que::draw_ratio(int num, int time)
{
	set(num);
	for (auto iter = vec.begin(); iter < vec.end(); iter++)
	{
		(**iter).draw_ratio(firstCenter + duration*(iter - vec.begin()), time);
	}
}

Circle::Circle(Vector2 c, double r) :
center(c),
range(r)
{

}

Circle::Circle(double x, double y, double r) :
center(x, y),
range(r)
{

}

bool Circle::is_on_mouse()
{
	return is_in(Input::get().mouse);
}

bool Circle::is_clicked()
{
	return is_in(Input::get().mouse) && Input::get().mouseState != 0;
}

void Circle::update()
{
	if (is_on_mouse())	{ onMouseTime++; }
	else { onMouseTime = 0; }
	if (is_clicked()){ clickedTime++; }
	else { clickedTime = 0; }
	existTime++;
}

bool Circle::get_clicked_down()
{
	return clickedTime == 1;
}

bool Circle::get_clicked()
{
	return clickedTime > 0;
}

bool Circle::get_on_mouse_down()
{
	return onMouseTime == 1;
}

bool Circle::get_on_mouse()
{
	return onMouseTime > 0;
}

void Circle::set(Vector2 c, double r)
{
	center = c;
	range = r;
}

void Circle::set(double x, double y, double r)
{
	center.Set(x, y);
	range = r;
}

Vector2 Circle::get_center()
{
	return center;
}

double Circle::get_range()
{
	return range;
}

Circle Circle::symmetry_y(Vector2 outerCenter)
{
	return Circle(outerCenter.x - center.x, outerCenter.y + center.y, range);
}

Circle Circle::slide(Vector2 outerCenter)
{
	return Circle(center + outerCenter, range);
}

Vector2 Circle::get_random()
{
	return Random::RandInCircle(range) + center;
}

void Circle::draw()
{
	MyDraw::circle(center, range, 0xFFFFFF);
}

void Circle::draw(double x, double y)
{
	MyDraw::circle(center, x + x, center.y + y, range, 0xFFFFFF);
}

void Circle::draw(Vector2 camera)
{
	MyDraw::circle(center + camera, range, 0xFFFFFF);
}

bool Circle::is_in(double x, double y)
{
	return (x - center.x)*(x - center.x) + (y - center.y)*(y - center.y) < range*range;
}

bool Circle::is_in(Vector2 point)
{
	return (point - center).Magnitude() < range;
}
bool Circle::is_in(Vector2 point, Vector2 camera)
{
	return (point - (center + camera)).Magnitude() < range;
}