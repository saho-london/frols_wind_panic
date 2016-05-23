#pragma once


#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include "graph.h"
#include "file.h"
#include "time.h"
#include "myglobal.h"
#include "Draw.h"


File::File(){//コンストラクタをprivateに置き、クラス外で生成するのを禁止
	FILE_NAME = "data.dat";
	FILE_NAME_OPTION = "setting.dat";
}

void File::load_set_data()
{
	std::ifstream fin(FILE_NAME_OPTION, std::ios::in | std::ios::binary);
	
	int b;
	int s;

	fin.read((char *)&b, sizeof(int));
	fin.read((char *)&s, sizeof(int));
}

void File::save_set_data()
{
	std::ofstream fout;
	fout.open(FILE_NAME_OPTION, std::ios::out | std::ios::binary | std::ios::trunc);
	if (!fout) {
		exit(EXIT_FAILURE);
	}
	fout.clear();

	int b = 0;
	int s = 0;

	fout.write((char *)&b, sizeof(int));
	fout.write((char *)&s, sizeof(int));
}

void File::save_data(){
	TimeManager& tManager = TimeManager::get();
	std::ofstream fout;
	fout.open(FILE_NAME, std::ios::out | std::ios::binary | std::ios::trunc);
	if (!fout) {
		exit(EXIT_FAILURE);
	}
	fout.clear();

	auto d = tManager.sumPlayTime + std::chrono::system_clock::now() - tManager.startTime;
	MyTime runTime(d);
	int h = runTime.get_hour();
	int m = runTime.get_minute();
	int s = runTime.get_second();
	int f = runTime.get_frame();

	fout.write((char *) &h, sizeof(int));
	fout.write((char *) &m, sizeof(int));
	fout.write((char *) &s, sizeof(int));
	fout.write((char *) &f, sizeof(int));

	fout.close();
}

void File::read_data(){
	TimeManager& tManager = TimeManager::get();

	std::ifstream fin(FILE_NAME, std::ios::in | std::ios::binary);


	fin.clear();
	fin.seekg(0, std::ios::beg);
	MyTime t;
	int h = 0;
	int m = 0;
	int s = 0;
	int f = 0;


	if (fin.fail())
	{
		exit(EXIT_FAILURE);
	}

	fin.read((char *)&h, sizeof(int));
	fin.read((char *)&m, sizeof(int));
	fin.read((char *)&s, sizeof(int));
	fin.read((char *)&f, sizeof(int));


	t.set_time(h, m, s, f);
	tManager.sumPlayTime = t.MyTime_to_duration();
	tManager.startTime = std::chrono::system_clock::now();
}

char* File::get_file_name()
{
	return FILE_NAME;
}

char* File::get_file_name_option()
{
	return FILE_NAME_OPTION;
}

String::String(bool dFlag):
original(),
str(""),
existTime(0),
drawTime(0),
drawFlag(dFlag)
{

}

String::String(double y_, std::string str_, bool dFlag) :
original(SCREEN.x / 2, y_),
str(str_),
existTime(0),
drawTime(0),
drawFlag(dFlag)
{

}

String::String(const Vector2 &pos, std::string str_, bool dFlag) :
original(pos),
str(str_),
existTime(0),
drawTime(0),
drawFlag(dFlag)
{

}

void String::set_draw_flag(bool dFlag)
{
	drawFlag = dFlag;
}

void String::update()
{
	existTime++;
	if (drawFlag)
	{
		drawTime++;
	}
	else
	{
		drawTime = 0;
	}
}

void String::draw(int color, int fhandle, const Vector2 &camera, double alpha)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	int wd = GetDrawFormatStringWidthToHandle(fhandle, "%s", str.c_str());
	DrawFormatStringToHandle(original.x + camera.x - wd / 2, original.y + camera.y, color, fhandle, "%s", str.c_str());
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

void String::add_exist_time()
{
	existTime++;
}

void String::add_draw_time()
{
	drawTime++;
}

int String::get_exist_time()
{
	return existTime;
}

int String::get_draw_time()
{
	return drawTime;
}

ILog::ILog(Vector2 start, Vector2 interv, int color_, int fHandle, std::string fname, const Vector2 &camera_) :
existTime(0),
FILE_NAME(fname),
color(color_),
fontHandle(fHandle),
startPoint(start),
interval(interv),
camera(camera_)
{

}

void ILog::load()
{
	std::ifstream ifs(FILE_NAME);
	ifs.clear();
	ifs.seekg(0, std::ios::beg);
	int i = 0;
	std::string str;
	if (ifs.fail())
	{
		exit(EXIT_FAILURE);
	}
	while (getline(ifs, str))
	{
		vec.emplace_back(String((Vector2)interval * i + startPoint, str));
		i++;
	}
}

void ILog::update()
{
	for (auto element : vec)
	{
		element.update();
	}
	existTime++;
}

void ILog::draw()
{
	for (auto element : vec)
	{
		if (element.drawFlag)
		{
			element.draw(color, fontHandle, camera);
		}
	}
}

void ILog::set_camera(const Vector2 &pos)
{
	camera = pos;
}

void ILog::set_file_name(std::string str)
{
	FILE_NAME = str;
}

double ILog::get_start()
{
	if (vec.size() == 0){
		return camera.y;
	}
	else{
		auto iter = vec.begin();
		return iter->original.y + camera.y;
	}

}

double ILog::get_end()
{
	if (vec.size() == 0){
		return camera.y;
	}
	else{
		auto iter = vec.end() - 1;
		return iter->original.y + camera.y;
	}
}

void ILog::reset_camera()
{
	camera = Vector2(0, 0);
}

int ILog::vec_size()
{
	return vec.size();
}

Log::Log() :
ILog(Vector2(SCREEN.x/2, SCREEN.y), Vector2(0, 30), 0x444444, SEGOE_S),
logSpeed(0.5)
{

}



void Log::update()
{
	for (auto element : vec)
	{
		element.update();
	}
	existTime++;
	camera.y -= logSpeed;
}

void Log::draw()
{
	for (auto element : vec)
	{
		element.draw(color, fontHandle, camera);
	}
}

LogAlpha::LogAlpha():
ILog(Vector2(330, 75), Vector2(0, 50), 0x6d0122, MARU_GOTHIC_S),
intervalTime(90),
maxTime(20)
{

}

void LogAlpha::update()
{
	if (existTime % intervalTime == 0)
	{
		set_draw_flag();
	}
	for (auto &element : vec)
	{
		element.update();
	}
	existTime++;
}

int LogAlpha::get_undrawn()
{
	int num = 0;
	auto iter = vec.begin();
	while (iter != vec.end())
	{
		if (iter->drawFlag)
		{
			iter++;
			num++;
		}
		else
		{
			return num;
		}
	}
	return -1;
}


void LogAlpha::set_draw_flag()
{
	int temp = get_undrawn();
	if (temp >= 0)
	{
		vec[temp].set_draw_flag(true);
	}
}

void LogAlpha::set_draw_flag_all()
{
	for (auto &element :vec)
	{
		element.set_draw_flag(true);
	}
}


void LogAlpha::draw()
{
	for (auto element : vec)
	{
		element.draw(color, fontHandle, Vector2(), 255.0 * (double)element.get_draw_time() / (double)maxTime);
	}
}

void LogAlpha::load()
{
	std::ifstream ifs(FILE_NAME);
	ifs.clear();
	ifs.seekg(0, std::ios::beg);
	int i = 0;
	std::string str;
	if (ifs.fail())
	{
		exit(EXIT_FAILURE);
	}
	while (getline(ifs, str))
	{
		vec.emplace_back(String((Vector2)interval * i + startPoint, str, false));
		i++;
	}

	fontHandle = MARU_GOTHIC_S;
}

bool LogAlpha::check_all_drawn()
{
	bool temp = true;
	for (auto &element : vec)
	{
		if (!element.drawFlag)
		{
			temp = false;
		}
	}
	return temp;
}