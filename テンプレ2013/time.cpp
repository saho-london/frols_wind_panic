#pragma once

#include "DxLib.h"
#include "time.h"
#include <string>
#include "myglobal.h"


TimeManager::TimeManager()
{//コンストラクタをprivateに置き、クラス外で生成するのを禁止
	startTime = std::chrono::system_clock::now();
	sumPlayTime = std::chrono::duration<std::chrono::system_clock::rep, std::chrono::system_clock::period>::zero();
}

TimeManager::TimeInterval::TimeInterval(int interval_, std::string duration) :
state(0),
down(false)
{
	if (duration == "seconds")
	{
		std::chrono::seconds temp1(interval_);
		intervalMin = temp1;
		std::chrono::seconds temp2(interval_);
		intervalMax = temp2;
	}
	else if (duration == "milliseconds")
	{
		std::chrono::milliseconds temp1(interval_);
		intervalMin = temp1;
		std::chrono::milliseconds temp2(interval_);
		intervalMax = temp2;
	}
	interval = Random::RandChrono(intervalMin, intervalMax);
	lastUpdate = std::chrono::system_clock::now();
}

TimeManager::TimeInterval::TimeInterval(int intervalMin_, int intervalMax_, std::string duration) :
state(0),
down(false)
{
	if (duration == "seconds")
	{
		std::chrono::seconds temp1(intervalMin_);
		intervalMin = temp1;
		std::chrono::seconds temp2(intervalMax_);
		intervalMax = temp2;
	}
	else if (duration == "milliseconds")
	{
		std::chrono::milliseconds temp1(intervalMin_);
		intervalMin = temp1;
		std::chrono::milliseconds temp2(intervalMax_);
		intervalMax = temp2;
	}
	interval = Random::RandChrono(intervalMin, intervalMax);
	lastUpdate = std::chrono::system_clock::now();
}

TimeManager::TimeInterval::TimeInterval() :
interval(2),
state(0),
down(false)
{
	lastUpdate = std::chrono::system_clock::now();
}

void TimeManager::TimeInterval::update()
{
	//if (std::chrono::duration_cast<std::chrono::seconds>(TimeManager::get().playTime).count() % interval.count() != 0)
	//{
	//	state++;
	//}
	//else { state = 0; }

	//if (state == 1){ down = true; }

	if (std::chrono::system_clock::now() >= (lastUpdate + interval) )
	{ 
		down = true;
		lastUpdate = std::chrono::system_clock::now();
		interval = Random::RandChrono(intervalMin, intervalMax);
	}
}

//void TimeManager::TimeInterval::set(int n)
//{
//	interval = std::chrono::seconds(n);
//}

void TimeManager::reset_time()
{
	startTime = std::chrono::system_clock::now();
	sumPlayTime = std::chrono::duration<std::chrono::system_clock::rep, std::chrono::system_clock::period>::zero();
	playTime = std::chrono::duration<std::chrono::system_clock::rep, std::chrono::system_clock::period>::zero();
}

void TimeManager::add_interval(std::string name_, int interval_, std::string duration)
{
		map.emplace(name_, std::make_shared<TimeInterval>(interval_, duration));
}

void TimeManager::add_interval(std::string name_, int intervalMin_, int intervalMax_, std::string duration)
{
		map.emplace(name_, std::make_shared<TimeInterval>(intervalMin_, intervalMax_, duration));

}

void TimeManager::register_map()
{
	add_interval("duration1", 800, 1600, "milliseconds");
	add_interval("duration2", 400, 800, "milliseconds");
	add_interval("duration3", 300, 600, "milliseconds");
}

bool TimeManager::check_down(std::string str)
{
	if (map.at(str)->down){
		map.at(str)->down = false;
		return true;
	}
	return map.at(str)->down;
}

void TimeManager::update()
{
	playTime = std::chrono::system_clock::now() - TimeManager::get().startTime;
	for (auto element : map){
		element.second->update();
	}
}

void TimeManager::save_time()
{
	sumPlayTime += playTime;
}

void TimeManager::load_time()
{
	startTime = std::chrono::system_clock::now();
}

void TimeManager::set_last_time()
{
	for (auto element : map)
	{
		element.second->lastUpdate = std::chrono::system_clock::now();
	}
}

void TimeManager::draw_map(int x, int y)
{
	int i = 0;
	for (auto element: map)
	{
		DrawFormatStringToHandle(x+i*20, y, 0xFFFFFF, SEGOE_M, "%s", element.first);
		i++;
	}
}



MyTime::MyTime() :
framePerSecond(60),
secondPerMinute(60),
minutePerHour(60),
hour(0),
minute(0),
second(0),
frame(0)
{
}

MyTime::MyTime(int h, int m, int s, int f) :
framePerSecond(60),
secondPerMinute(60),
minutePerHour(60),
hour(h),
minute(m),
second(s),
frame(f)
{
}

void MyTime::operator++() {
	frame++;
	if (frame == framePerSecond)
	{
		frame = 0;
		second++;
		if (second == secondPerMinute)
		{
			second = 0;
			minute++;
			if (minute == minutePerHour)
			{
				minute = 0;
				hour++;
			}
		}
	}
	return;
}

MyTime::MyTime(std::chrono::duration<std::chrono::system_clock::rep, std::chrono::system_clock::period> d) :
framePerSecond(60),
secondPerMinute(60),
minutePerHour(60),
frame(0)
{
	std::chrono::hours hours = std::chrono::duration_cast<std::chrono::hours>(d);
	d -= hours;
	std::chrono::minutes minutes = std::chrono::duration_cast<std::chrono::minutes>(d);
	d -= minutes;
	std::chrono::seconds seconds = std::chrono::duration_cast<std::chrono::seconds>(d);
	hour = hours.count();
	minute = minutes.count();
	second = seconds.count();
}


MyTime MyTime::operator+(const MyTime& u)
{
	MyTime w;
	int t1 = -10;
	while (framePerSecond*t1 > this->frame + u.frame || framePerSecond*(t1 + 1) <= this->frame + u.frame){ t1++; }
	w.frame = (this->frame + u.frame) - framePerSecond * t1;
	int t2 = -10;
	while (secondPerMinute*t2 > this->second + u.second + t1 || secondPerMinute*(t2 + 1) <= this->second + u.second + t1){ t2++; }
	w.second = (this->second + u.second + t1) - secondPerMinute*t2;
	int t3 = -10;
	while (minutePerHour*t3 > this->minute + u.minute + t2 || minutePerHour*(t3 + 1) <= this->minute + u.minute + t2){ t3++; }
	w.minute = (this->minute + u.minute + t2) - minutePerHour*t3;
	w.hour = (this->hour + u.hour + t3);
	return w;
}

MyTime MyTime::operator+(int second)
{
	MyTime w;
	w.frame = this->frame;
	int t1 = -10;
	while (secondPerMinute*t1 > this->second + second || secondPerMinute*(t1 + 1) <= this->second + second){ t1++; }
	w.second = (this->second + second) - secondPerMinute*t1;
	int t2 = -10;
	while (minutePerHour*t2 > this->minute + t1 || minutePerHour*(t2 + 1) <= this->minute + t1){ t2++; }
	w.minute = (this->minute + t1) - minutePerHour*t2;
	w.hour = (this->hour + t2);
	return w;
}

MyTime MyTime::operator-(const MyTime& u)
{
	MyTime w;
	int t1 = 10;
	while (framePerSecond * t1 > this->frame - u.frame || framePerSecond * (t1 + 1) <= this->frame - u.frame){ t1 -= 1;; }
	w.frame = (this->frame - u.frame) - framePerSecond*t1;
	int t2 = 10;
	while (secondPerMinute * t2 > this->second - u.second + t1 || secondPerMinute * (t2 + 1) <= this->second - u.second + t1){ t2 -= 1;; }
	w.second = (this->second - u.second + t1) - secondPerMinute*t2;
	int t3 = 10;
	while (minutePerHour * t3 > this->minute - u.minute + t2 || minutePerHour * (t3 + 1) <= this->minute - u.minute + t2){ t3 -= 1;; }
	w.minute = (this->minute - u.minute + t2) - minutePerHour*t3;
	w.hour = (this->hour - u.hour + t3);
	return w;
}

MyTime& MyTime::operator=(const MyTime& u) {
	this->hour = u.hour;
	this->minute = u.minute;
	this->second = u.second;
	this->frame = u.frame;
	return *this;
}

MyTime MyTime::operator *(int k)
{
	MyTime w;
	int t0 = -10;
	while (framePerSecond*t0 > this->frame*k || framePerSecond*(t0 + 1) <= this->frame*k){ t0++; }
	w.frame = k * this->frame - framePerSecond * t0;
	int t1 = -10;
	while (secondPerMinute*t1 > this->second*k + t0 || secondPerMinute*(t1 + 1) <= this->second*k + t0){ t1++; }
	w.second = (this->second *k) + t0 - secondPerMinute*t1;
	int t2 = -10;
	while (minutePerHour*t2 > this->minute* k + t1 || minutePerHour*(t2 + 1) <= this->minute * k + t1){ t2++; }
	w.minute = (this->minute*k + t1) - minutePerHour*t2;
	w.hour = (this->hour + t2);
	return w;
}

bool MyTime::operator>(const MyTime& u)
{
	if (this->hour > u.hour){ return true; }
	else if (this->hour < u.hour){ return false; }
	else if (this->minute > u.minute){ return true; }
	else if (this->minute < u.minute){ return false; }
	else if (this->second > u.second){ return true; }
	else if (this->second < u.second){ return false; }
	else if (this->frame > u.frame){ return true; }
	else{ return false; }
}

bool MyTime::operator<(const MyTime& u)
{
	if (this->hour < u.hour){ return true; }
	else if (this->hour > u.hour){ return false; }
	else if (this->minute < u.minute){ return true; }
	else if (this->minute > u.minute){ return false; }
	else if (this->second < u.second){ return true; }
	else if (this->second > u.second){ return false; }
	else if (this->frame < u.frame){ return true; }
	else{ return false; }
}

bool MyTime::operator>=(const MyTime& u)
{
	if (this->hour > u.hour){ return true; }
	else if (this->hour < u.hour){ return false; }
	else if (this->minute > u.minute){ return true; }
	else if (this->minute < u.minute){ return false; }
	else if (this->second > u.second){ return true; }
	else if (this->second < u.second){ return false; }
	else if (this->frame >= u.frame){ return true; }
	else{ return false; }
}

bool MyTime::operator<=(const MyTime& u)
{
	if (this->hour < u.hour){ return true; }
	else if (this->hour > u.hour){ return false; }
	else if (this->minute < u.minute){ return true; }
	else if (this->minute > u.minute){ return false; }
	else if (this->second < u.second){ return true; }
	else if (this->second > u.second){ return false; }
	else if (this->frame <= u.frame){ return true; }
	else{ return false; }
}

MyTime MyTime::operator%(const MyTime& u)
{
	MyTime v = *this;
	while (v > u)
	{
		v = v - u;
	}
	return v;
};

bool MyTime::operator==(int frame)
{
	return ((this->hour * minutePerHour + this->minute) * secondPerMinute + this->second)*framePerSecond + this->frame == frame;
}

void MyTime::set_time(int h, int m, int s, int f)
{
	hour = h;
	minute = m;
	second = s;
	frame = f;
}

int const MyTime::get_frame(){
	return frame;
}

int const MyTime::get_second(){
	return second;
}

int const MyTime::get_minute(){
	return minute;
}

int const MyTime::get_hour(){
	return hour;
}

void MyTime::set_time(std::chrono::duration<std::chrono::system_clock::rep, std::chrono::system_clock::period> d)
{
	std::chrono::hours hours = std::chrono::duration_cast<std::chrono::hours>(d);
	d -= hours;
	std::chrono::minutes minutes = std::chrono::duration_cast<std::chrono::minutes>(d);
	d -= minutes;
	std::chrono::seconds seconds = std::chrono::duration_cast<std::chrono::seconds>(d);
	hour = hours.count();
	minute = minutes.count();
	second = seconds.count();
	frame = 0;
}

std::chrono::duration<std::chrono::system_clock::rep, std::chrono::system_clock::period> MyTime::MyTime_to_duration()
{
	std::chrono::duration<std::chrono::system_clock::rep, std::chrono::system_clock::period> d;
	d = std::chrono::duration<std::chrono::system_clock::rep, std::chrono::system_clock::period>::zero();
	std::chrono::hours h(hour);
	std::chrono::minutes m(minute);
	std::chrono::seconds s(second);
	d = h + m + s;
	return d;
}

void MyTime::draw(int x, int y)
{
	DrawFormatStringToHandle(x, y, 0xFFFFFF, SEGOE_M, "%2d:%2d:%2d:%2d", hour, minute, second, frame);
}

//static MyTime now_run_to_MyTime(std::chrono::system_clock::time_point st)
//{
//	MyTime t;
//	auto runTime = std::chrono::system_clock::now() - st;
//	std::chrono::hours hours = std::chrono::duration_cast<std::chrono::hours>(runTime);
//	runTime -= hours;
//	std::chrono::minutes minutes = std::chrono::duration_cast<std::chrono::minutes>(runTime);
//	runTime -= minutes;
//	std::chrono::seconds seconds = std::chrono::duration_cast<std::chrono::seconds>(runTime);
//	t.set_time(hours.count(), minutes.count(), seconds.count(), 0);
//	return t;
//}

//ランダムなTimeを返す関数
//void rand_set(MyTime max)
//{
//	std::uniform_int_distribution<int> uidF(0, max.get_frame());
//	std::uniform_int_distribution<int> uidS(0, max.get_second());
//	std::uniform_int_distribution<int> uidM(0, max.get_minute());
//	std::uniform_int_distribution<int> uidH(0, max.get_hour());
//	set_time(uidH(get().mt), uidM(get().mt), uidS(get().mt), uidF(get().mt));
//}

//void rand_set(MyTime min, MyTime max)
//{
//	std::uniform_int_distribution<int> uidF(0, max.get_frame());
//	std::uniform_int_distribution<int> uidS(0, max.get_second());
//	std::uniform_int_distribution<int> uidM(0, max.get_minute());
//	std::uniform_int_distribution<int> uidH(0, max.get_hour());
//	set_time(uidH(get().mt), uidM(get().mt), uidS(get().mt), uidF(get().mt));
//}