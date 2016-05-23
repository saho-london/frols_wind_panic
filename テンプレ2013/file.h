#pragma once

#include <fstream>
#include "Vector2.h"
#include <vector>
#include "myglobal.h"

class File{
private:
	char *FILE_NAME;
	char *FILE_NAME_OPTION;

	File();

	File(const File& r) = delete;//ÉRÉsÅ[Çã÷é~
	File& operator=(const File& r) = delete; //ë„ì¸Çã÷é~

public:
	static File& get(){
		static File inst;
		return inst;
	}

	void load_set_data();
	void save_set_data();
	void save_data();
	void read_data();
	void update();
	char * get_file_name();
	char * get_file_name_option();
};

class String
{
	int existTime;
	int drawTime;
public:
	Vector2 original;
	std::string str;
	bool drawFlag;

	String(bool dFlag = true);
	String(double y, std::string str_, bool dFlag = true);
	String(const Vector2 &pos, std::string str_, bool dFlag = true);

	void update();
	void set_draw_flag(bool dflag);
	void draw(int color, int fhandle, const Vector2 &camera, double alpha = 255);
	void add_exist_time();
	void add_draw_time();
	int get_exist_time();
	int get_draw_time();
};

class ILog
{
protected:
	int existTime;

	std::string FILE_NAME;
	FILE *fp;
	int color;
	int fontHandle;
	Vector2 camera;
	const Vector2 startPoint;
	const Vector2 interval;

public:
	std::vector<String> vec;

	ILog(Vector2 start, Vector2 interv, int color_, int fHandle, std::string fname = "log.dat", const Vector2 &camera_ = Vector2());

	virtual void load();
	virtual void update();
	virtual void draw();
	void set_camera(const Vector2 &pos);
	void set_file_name(std::string str);
	double get_start();
	double get_end();
	void reset_camera();
	int vec_size();
};

class Log : public ILog
{
protected:
	const double logSpeed;

public:

	Log();


	void update() override;
	void draw() override;
};

class LogAlpha : public ILog
{
	int intervalTime;
	int maxTime;

public:

	LogAlpha();

	void load() override;
	void update() override;
	int get_undrawn();
	void set_draw_flag();
	void set_draw_flag_all();
	void draw();
	bool check_all_drawn();
};