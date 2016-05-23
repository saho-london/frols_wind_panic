#include <iostream>

#include "MyFunc.h"
#include "Vector2.h"
#include "myglobal.h"


//�����蔻��

//2��
template<typename T> T Func::Sqr(T x)
{
	return x*x;
}
//���όv�Z
template<typename T> T Func::Dot2D(T Ax, T Ay, T Bx, T By)
{
	return Ax*Bx + Ay*By;
}
//�O�όv�Z
template<typename T> T Func::Cross2D(T Ax, T Ay, T Bx, T By)
{
	return Ax*By - Bx*Ay;
}


//�ǉ�
//�_�Ɖ~
bool Func::PointCircle(const Vector2& point_pos, const Vector2& circle_center, double radius)
{
	return Sqr(circle_center.x - point_pos.x) + Sqr(circle_center.y - point_pos.y) < Sqr(radius);
}

//�~�`���m
bool Func::Circles(double x1, double y1, double r1, double x2, double y2, double r2)
{
	return Sqr(x2 - x1) + Sqr(y2 - y1) < Sqr(r2 + r1);
}
bool Func::Circles(const Vector2& c1, double r1, const Vector2& c2, double r2)
{
	return Sqr(c2.x - c1.x) + Sqr(c2.y - c1.y) < Sqr(r2 + r1);
}
//��`���m
bool Func::Boxes(double a1x, double a1y, double a2x, double a2y, double b1x, double b1y, double b2x, double b2y)
{
	return a1x < b2x && a1y < b2y && b1x < a2x && b1y < a2y;
}
bool Func::Boxes(const Vector2& a1, const Vector2& a2, const Vector2& b1, const Vector2& b2)
{
	return a1.x < b2.x && a1.y < b2.y && b1.x < a2.x && b1.y < a2.y;
}
//�_�ƕ��̂���� (�_�̍��W�A���̂�����̎n�_�E�I�_)
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

//�_�ƕ��̂���� (�_�̍��W�A���̂�����̎n�_�E�I�_�܂ł̋����A�p�x)
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

//�_�Ƌ�`
bool Func::BoxPoint(int px, int py, int box_cx, int box_cy, int box_width, int box_height){
	return abs(px - box_cx) < box_width / 2
		&& abs(py - box_cy) < box_height / 2;
}

//�_�Ƌ�`
bool Func::BoxPoint(const Vector2& p_pos, const Vector2& box_pos, const Vector2& box_size){
	return abs(p_pos.x - box_pos.x) < box_size.x / 2
		&& abs(p_pos.y - box_pos.y) < box_size.y / 2;
}
//���ʂ̓_�Ƌ�`
bool Func::DotAndRect(double px, double py, double b1x, double b1y, double b2x, double b2y)
{
	return  b1x < px  && px < b2x
		&&  b1y < py  && py < b2y;
}

//�~(���acr,(cx,cy))�̋ߎ������`�Ɓ@�����`(����(rx1,ry1), �E��(rx2, ry2))�̓����蔻��
bool Func::CircleAndRect(double cx, double cy, double cr, double rx1, double ry1, double rx2, double ry2){
	double rectx = (rx1 + rx2) / 2.0;
	double recty = (ry1 + ry2) / 2.0;
	return	cx > rx1 - cr && cy > ry1 - cr &&
		cx < rx2 + cr && cy < ry2 + cr;
}
//�������m(0�Ȃ炠�����ĂȂ��A0�ȏ�͂������Ă�
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
//Lines�œ������Ă��ꍇ�͈ʒu���v�Z�ł���
Vector2 Func::LinesCalcCrossPoint(double lines_result, double a_x, double a_y, double b_x, double b_y)
{
	Vector2 AB(b_x - a_x, b_y - a_y);
	AB *= lines_result;
	AB.Translate(a_x, a_y);
	return AB;
}
//�~�Ɛ���
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


//�x�N�g��

//���_�𒆐S��ang����]
void Func::rotateonzero(double &x, double &y, double ang){
	double sx = x - 0;
	double sy = y - 0;
	x = sx * cos(ang) - sy * sin(ang) + 0;
	y = sx * sin(ang) + sy * cos(ang) + 0;
}

//����_(centerx,centery)�𒆐S��ang����]
void Func::rotateonpoint(double &x, double &y, double centerx, double centery, double ang){
	double sx = x - centerx;
	double sy = y - centery;
	x = sx * cos(ang) - sy * sin(ang) + centerx;
	y = sx * sin(ang) + sy * cos(ang) + centery;
}

//(���_����(sx,sy)�ւ̒P�ʃx�N�g�������߂�
void Func::normalizedVector(double &vx, double &vy, double sx, double sy){
	double rd = atan2(sy, sx);
	vx = cos(rd);
	vy = sin(rd);
}

//(sx,sy)����(ex,ey)�ւ̒P�ʃx�N�g�������߂�
void Func::normalizedVector(double &vx, double &vy, double sx, double sy, double ex, double ey){
	double rd = atan2(ey - sy, ex - sx);
	vx = cos(rd);
	vy = sin(rd);
}

//(dx,dy)�����A�傫��dist�̃x�N�g�������߁A���ʂ�result�ɑ��
void Func::calVector(double sx, double sy, double ex, double ey, double dist, double &resultx, double &resulty){
	double rd = atan2(ey - sy, ex - sx);
	resultx = dist * cos(rd);
	resulty = dist * sin(rd);
}

//(dx,dy)�����A�傫��dist�̃x�N�g�������߁A���ʂ�result�ɉ��Z
void Func::addVector(double sx, double sy, double ex, double ey, double dist, double &resultx, double &resulty){
	double rd = atan2(ey - sy, ex - sx);
	resultx += dist * cos(rd);
	resulty += dist * sin(rd);
}

//(dx,dy)�����A�傫��dist�̃x�N�g�������߁A���ʂ�result�ɉ��Z
void Func::addVector(double r, double angle, double &resultx, double &resulty){
	resultx += r * cos(angle);
	resulty += r * sin(angle);
}

//�ɍ��W�\������xy�\���ɒ���
void Func::polartoxy(double &x, double &y, double r, double ang){
	x = r * cos(ang);
	y = r * sin(ang);
}

//�p�x���v�Z
double Func::calAngle(double x, double y){
	return atan2(y, x);
}

//�p�x���v�Z
double Func::calAngle(double sx, double sy, double ex, double ey){
	return atan2(ey - sy, ex - sx);
}

/*
startx : �J�n�̒l(�J�n���̍��W��X�P�[���Ȃ�)
enddif : �J�n�ƏI���̒l�̍���
time_now : ���݂̎���
time_end : Tween�̍��v����
*/

//�^�_�@�����������O���t
double Func::linef(double startx, double dif, double time_now, double time_end){
	return startx + (dif - startx) * (abs(time_end / 2 - time_now) / (time_end / 2));
}

//�^�_�@����������2���Ȑ�
double Func::quadraticf(double startx, double dif, double time_now, double time_end){
	double x = time_now / time_end;
	return startx + (dif - startx) * -4 * (x * x - x);
}


//3�_��ʂ钼���O���t
double Func::graph3(double x0, double x1, double x2, double t1, double t_now, double t_end){
	if (t_now < t1){
		return (x1 - x0) * t_now / t1 + x0;
	}
	else{
		return (x2 - x1) * (t_now - t1) / (t_end - t1) + x1;
	}
}

//4�_��ʂ钼���O���t
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


//�C�[�W���O�Ȑ�

/*
t : ���݂̎���
b : �J�n�̒l(�J�n���̍��W��X�P�[���Ȃ�)
c : �J�n�ƏI���̒l�̍���
d : Tween�̍��v����
*/

//�C�[�W���O�Ȑ� Cubic
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


//�C�[�W���O�Ȑ� Sinusoidal
double Func::ease_sin_in(double t, double b, double c, double d){
	return -c * cos(t / d * (PI / 2.0)) + c + b;
}

double Func::ease_sin_out(double t, double b, double c, double d){
	return c * sin(t / d * (PI / 2.0)) + b;
}

double Func::ease_sin_inout(double t, double b, double c, double d){
	return -c / 2.0 * (cos(PI*t / d) - 1) + b;
}

//�C�[�W���O�Ȑ� Exponential
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

//�C�[�W���O�Ȑ� Circular
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



//�x�W�F�Ȑ�  p1->p2->p3  0<t<1
double Func::bz_curve(double p1, double p2, double p3, double t){
	double tp = 1 - t;
	return t*t*p3 + 2 * t*tp*p2 + tp*tp*p1;
}

//�x�W�F�Ȑ�  p1->p2->p3  nowtime, endtime
double Func::bz_curve(double p1, double p2, double p3, double nowt, double endt){
	double t = nowt / endt;
	double tp = 1 - t;
	return t*t*p3 + 2 * t*tp*p2 + tp*tp*p1;
}

//�A�j���[�V�����p�E�_�^�_�^�_�^�ƂȂ�O���t
int Func::Repeat(int frame, int loop_num)
{
	--loop_num;
	frame = frame % (loop_num * 2);
	if (frame > loop_num)
		return loop_num * 2 - frame;
	else
		return frame;
}

//2���x�W�G�Ȑ����v�Z����֐�
Vector2 Func::GetBezier2(const Vector2& Start, const Vector2& Control
	, const Vector2& End, float t)
{
	Vector2 Result;
	// P = t^2*P0 + 2t(1-t)P1 + (1-t)^2P2
	Result.x = (t*t)*End.x + 2 * t*(1 - t)*Control.x + (1 - t)*(1 - t)*Start.x;
	Result.y = (t*t)*End.y + 2 * t*(1 - t)*Control.y + (1 - t)*(1 - t)*Start.y;
	return Result;
}

//2���x�W�G�Ȑ��Ő���_���ʂ�悤�Ɉ��������ꍇ�̐���_��Ԃ��֐�
Vector2 Func::GetBezierPassC2(const Vector2 &Start, const Vector2 &End, const Vector2 &PassPoint)
{
	Vector2 C;
	C.x = (4 * PassPoint.x - Start.x - End.x) / 2.0f;
	C.y = (4 * PassPoint.y - Start.y - End.y) / 2.0f;
	return C;
}

//Control��ʂ�2���x�W�G�Ȑ����v�Z����֐�
Vector2 Func::GetBezierCtrl2(const Vector2& Start, const Vector2& Control
	, const Vector2& End, float t)
{
	Vector2 C;//Control��ʂ�2���x�W�G�Ȑ��̐���_
	Vector2 Result;
	C.x = (4 * Control.x - Start.x - End.x) / 2.0f;
	C.y = (4 * Control.y - Start.y - End.y) / 2.0f;
	Result.x = (t*t)*End.x + 2 * t*(1 - t)*C.x + (1 - t)*(1 - t)*Start.x;
	Result.y = (t*t)*End.y + 2 * t*(1 - t)*C.y + (1 - t)*(1 - t)*Start.y;
	return Result;
}

//3���x�W�G�Ȑ����v�Z����֐�
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
//�֗��֐�

//HSV��RGB�Ɋ��Z ���ڊ֐��̈����ɓn���p
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

//HSV��RGB�Ɋ��Z int�ɕۑ�����p
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

//HSV��setdrawbright
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

//0xXXXXXX��SetDrawBright����֐�
void Func::SetDrawBrightInt(int col){
	SetDrawBright(col >> 16, (col >> 8) & (0x00FF), col & 0x0000FF);
}

//�����̊p�x,����̊p�x 2�p�̊֌W��Ԃ��@���v��葤�ɓ������ق����߂����1 �����łȂ����-1
int Func::abs_angle(double angle1, double angle2){
	if (sin(angle2 - angle1) > 0){
		return 1;
	}
	else{
		return -1;
	}
}

//���������_�Ɉړ��Arate�͎������瑊������ւ̈ړ��� 0.0 - 1.0  tarx�Ƃ̍���erange�ȉ���tarx = x�ɂ���
void Func::moverate(double &x, double tarx, double rate, double erange)
{
	x = x * (1 - rate) + tarx * rate;
	if (abs(x - tarx) < erange){
		x = tarx;
	}
}
//���������_�Ɉړ��Arate�͎������瑊������ւ̈ړ��� 0.0 - 1.0  dist��0.5�ȉ���tarP = P�ɂ���
void Func::moverate(double &x, double &y, double tarx, double tary, double rate, double erangedist)
{
	x = x * (1 - rate) + tarx * rate;
	y = y * (1 - rate) + tary * rate;
	if (dist(x, y, tarx, tary) < erangedist){
		x = tarx;
		y = tary;
	}
}
//���������_�Ɉړ��Arate�͎������瑊������ւ̈ړ��� 0.0 - 1.0  dist��0.5�ȉ���tarP = P�ɂ���
void Func::moverate(Vector2 &v2, const Vector2 &tarv2, double rate, double erangedist)
{
	v2.x = v2.x * (1 - rate) + tarv2.x * rate;
	v2.y = v2.y * (1 - rate) + tarv2.y * rate;
	if (dist(v2.x, v2.y, tarv2.x, tarv2.y) < erangedist){
		v2 = tarv2;
	}
}


//���_�Ƃ̋�����Ԃ�
double Func::dist(double x, double y){
	return sqrt(x*x + y*y);
}

//2�_�̋�����Ԃ�
double Func::dist(double x1, double y1, double x2, double y2){
	return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
}

//2�_�̋�����2���Ԃ�
double Func::distSqr(double x1, double y1, double x2, double y2){
	return (x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2);
}


//rate��cool�̃Z�b�g��cool���X�V�Ebool��Ԃ�
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



//��E�U���E����(�b)�E�o�߃t���[�����w�肵��sin��Ԃ�
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

//	//�X�N���[���̒��S��Ԃ�
//	inline Vector2 GetScreenCenter(){
//		return Vector2(ScreenWidth / 2, ScreenHeight / 2);
//	}
//
//	//�����_����2�����̑啶���A���t�@�x�b�g��Ԃ�
//	std::string randStr(){
//		std::string str;
//		for (int i = 0; i < 2; i++){
//			str += (char)((int)'A' + GetRand(25));
//		}
//		return str;
//	}
//	//�����_����2�����̑啶���A���t�@�x�b�g��Ԃ�
//	std::string randStr(int loop){
//		std::string str;
//		for (int i = 0; i < loop; i++){
//			str += (char)((int)'A' + GetRand(25));
//		}
//		return str;
//	}
//
//	//�X�N���[������o�Ă��邩��Ԃ��֐�
//	bool isScreenOut(const Vector2 &pos){
//		return pos.x < 0 || pos.x > ScreenWidth
//			|| pos.y < 0 || pos.y > ScreenHeight;
//	}
//
//	//�X�N���[������marge�O�ɏo�Ă��邩��Ԃ��֐�
//	bool isScreenOutMarge(const Vector2 &pos, int marge){
//		return pos.x < -marge || pos.x > ScreenWidth + marge
//			|| pos.y < -marge || pos.y > ScreenHeight + marge;
//	}

//class Random
Random::Random(){
	//SeedSetUseRD��MT�̏����l��ݒ�
	SeedSetUseRD();
}

Random& Random::get()
{
	static Random r;
	return r;
}

//MT�̏����l��Random_device���g�p���Đݒ�
void Random::SeedSetUseRD(){
	std::random_device r;
	get().mt.seed(r());
}
//MT�̏����l�ݒ�
void Random::Initialize(int seed)
{
	get().mt.seed(seed);
}
//mt�G���W���{�̂��擾
std::mt19937& Random::getMT(){
	return get().mt;
}

//���S����
unsigned int Random::RamdomDeviceValue()
{
	std::random_device r;
	return r();
}

//�ʏ��rand�擾
int Random::Rand(){
	return get().mt();
}
//0~max�w��擾(int)
int Random::Rand(int max)
{
	std::uniform_int_distribution<int> uid(0, max);
	return uid(get().mt);
}
//min~max��Ԃ�(int)
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
//1��-1��Ԃ��֐�
int Random::RandPM1(){
	std::uniform_int_distribution<int> uid(0, 1);
	return uid(get().mt) * 2 - 1;
}
//0~1��Ԃ�(double)
double Random::Value()
{
	std::uniform_real_distribution<double> urd(0, 1);
	return urd(get().mt);
}
//0~max��Ԃ�(double)
double Random::FRand(double max)
{
	if (max < 0.0){
		return 0.0;
	}
	std::uniform_real_distribution<double> urd(0, max);
	return urd(get().mt);
}
//min~max��Ԃ�(double)
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
//���K���z
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
//���K���z ���ςƃ����W�w��
double Random::NormalDist(double ave, double range){
	std::normal_distribution<double> nd(ave, range / 3.0);
	double ret = nd(get().mt);
	if (ret < ave - range || ret > ave + range){
		ret = FRand(ave - range, ave + range);
	}
	return ret;
}

//���W�A���Ŏ擾
double Random::FRadRand()
{
	return FRand(-PI, PI);
}
double Random::FRadRand(double deg_min, double deg_max)
{
	return FRand(deg_min * DegToRad, deg_max * DegToRad);
}

//���ar�̉~��̓_��Ԃ�
void Random::RandOnCircle(double r, double &x, double &y){
	double randang = FRadRand();
	x = r * cos(randang);
	y = r * sin(randang);
}
//���ar�̉~��̓_��Ԃ��@���_����̊p�x���Ԃ�
void Random::RandOnCircle(double r, double &x, double &y, double &ang){
	double randang = FRadRand();
	x = r * cos(randang);
	y = r * sin(randang);
	ang = randang;
}
//���ar�̉~�����̓_��Ԃ�
void Random::RandInCircle(double r, double &x, double &y){
	double randang = FRadRand();
	double rr = r * Value();
	x = rr * cos(randang);
	y = rr * sin(randang);
}
//���ar�̉~�����̓_��Ԃ��@���_����̊p�x���Ԃ�
void Random::RandInCircle(double r, double &x, double &y, double &ang){
	double randang = FRadRand();
	double rr = r * Value();
	x = rr * cos(randang);
	y = rr * sin(randang);
	ang = randang;
}
//���ar�̉~��̓_��Ԃ�
Vector2 Random::RandOnCircle(double r){
	Vector2 temp;
	double randang = FRadRand();
	temp.x = r * cos(randang);
	temp.y = r * sin(randang);
	return temp;
}
//���ar�̉~��̓_��Ԃ�
Vector2 Random::RandOnCircle(double r1, double r2){
	Vector2 temp;
	double r = Random::FRand(r1, r2);
	double randang = FRadRand();
	temp.x = r * cos(randang);
	temp.y = r * sin(randang);
	return temp;
}
//���ar�̉~�����̓_��Ԃ�
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


//p�̊m����true��Ԃ�
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