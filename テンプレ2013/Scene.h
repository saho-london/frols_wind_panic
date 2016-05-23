#pragma once

#include <string>
#include <memory>
#include "MyFunc.h"
#include "Vector2.h"
#include "File.h"
#include "manager.h"
#include "flower.h"
#include <chrono>
#include "effect.h"


//シーンの種類
enum Scene
{
	stitle,
//	soption,
	sgame,
//	sprologue,
	sresult,
	sexplain
};

//title画面からゲーム開始時にセーブデータをロードするか
enum LoadFlag
{
	loadData,
	notLoadData
};

//シーンの基底クラス
class Status
{
private:
	bool bFirstUpdate;

protected:
	virtual void entryAction();
	virtual void inputAction();
	virtual void exitAction();
public:
	bool existFlag;

	Status();

	void update();
	virtual void draw();
};

//シーンを管理するクラス
class SceneManager
{
	SceneManager();

	SceneManager(const SceneManager& r) = delete;//コピーを禁止
	SceneManager& operator=(const SceneManager& r) = delete; //代入を禁止
public:
	static SceneManager& get(){
		static SceneManager inst;
		return inst;
	}

	bool bloomFlag;
	double score;
	Mgr<IEaseEffect> effect;
	bool SceneChangeFlag;

	std::shared_ptr<Status> create(Scene sce);

	std::vector<std::shared_ptr<Status>> sceneVec;
	std::shared_ptr<Status> nextScene;
	LoadFlag loadFlag;

	void update();
	void draw();
	void load();
	void set_next(Scene nScene);
};

//タイトル画面
class Title : public Status
{
public:
	int existTime;
	int intervalTime;

	Rectangular start;

	Title();

	virtual void entryAction() override;
	virtual void inputAction() override;

	virtual void draw() override;
};

class Game : public Status
{
public:
	Circle tree;
	Mgr<Object> flowerVec;

	std::chrono::system_clock::time_point startTime;
	int playTime;
	const int limitTime;
	int count;
	int intervalTime;

	int flowerCloudNum;

	int existTime;

	Game();

	virtual void entryAction() override;
	virtual void inputAction() override;
	virtual void exitAction() override;

	void add_flower(const Vector2 &pos);

	virtual void draw() override;

};

class Result : public Status
{
	class String2
	{
	public:
		String2();
		String2(double x_, double y, std::string str_);
		Vector2 original;
		std::string str;
		void draw(Vector2 camera = Vector2());
		void set(Vector2 pos);
		void set(std::string str_);
	};

public:
	Result();

	int flowerCloudNum;
	int rank;
	String2 str[5][3];
	Rectangular retry;

	virtual void entryAction() override;
	virtual void inputAction() override;
	virtual void exitAction() override;

	virtual void draw() override;
};

class Explain : public Status
{
public:
	LogAlpha log;
	Rectangular start;
	int existTime;

	Explain();

	virtual void entryAction() override;
	virtual void inputAction() override;
	virtual void exitAction() override;

	virtual void draw() override;
};