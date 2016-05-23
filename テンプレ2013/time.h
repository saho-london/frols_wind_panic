#pragma once

#include <chrono>
#include <string>
#include <memory>
#include <map>

class TimeManager {
private:
	TimeManager();

	TimeManager(const TimeManager& r) = delete;//ÉRÉsÅ[Çã÷é~
	TimeManager& operator=(const TimeManager& r) = delete; //ë„ì¸Çã÷é~

	class TimeInterval
	{
	public:
		std::chrono::milliseconds interval;
		std::chrono::milliseconds intervalMin;
		std::chrono::milliseconds intervalMax;

		int state;
		bool down;
		std::chrono::system_clock::time_point lastUpdate;

		TimeInterval(int interval_, std::string duration = "seconds");
		TimeInterval(int intervalMin_, int intervalMax_, std::string duration = "seconds");
		TimeInterval();

		void update();

		//void set(int n);

	};

public:
	static TimeManager& get(){
		static TimeManager inst;
		return inst;
	}

	std::chrono::system_clock::time_point startTime;
	std::chrono::duration<std::chrono::system_clock::rep, std::chrono::system_clock::period> sumPlayTime;
	std::chrono::duration<std::chrono::system_clock::rep, std::chrono::system_clock::period> playTime;

	std::map<std::string, std::shared_ptr<TimeInterval>> map;

	void reset_time();

	void add_interval(std::string name_, int interval_, std::string duration = "seconds");
	void add_interval(std::string name_, int intervalMin_, int intervalMax_, std::string duration = "seconds");

	void register_map();

	bool check_down(std::string str);

	void update();

	void save_time();

	void load_time();

	void set_last_time();

	void draw_map(int x, int y);
};

class MyTime {
	int hour;
	int minute;
	int second;
	int frame;
	const int framePerSecond;
	const int secondPerMinute;
	const int minutePerHour;

public:
	MyTime();
	MyTime(int h, int m, int s, int f);
	MyTime(std::chrono::duration<std::chrono::system_clock::rep, std::chrono::system_clock::period> d);

	void operator++();
	MyTime operator+(const MyTime& u);
	MyTime operator+(int second);
	MyTime operator-(const MyTime& u);
	MyTime& operator=(const MyTime& u);
	MyTime operator *(int k);
	bool operator>(const MyTime& u);
	bool operator<(const MyTime& u);
	bool operator>=(const MyTime& u);
	bool operator<=(const MyTime& u);
	MyTime operator%(const MyTime& u);
	bool operator== (int frame);


	void set_time(const int h, const int m, const int s, const int f);

	int const get_frame();

	int const get_second();

	int const get_minute();

	int const get_hour();

	void set_time(std::chrono::duration<std::chrono::system_clock::rep, std::chrono::system_clock::period> d);

	std::chrono::duration<std::chrono::system_clock::rep, std::chrono::system_clock::period> MyTime_to_duration();

	void draw(int x, int y);
};

