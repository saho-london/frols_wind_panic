#include <memory>
#include "Scene.h"
#include <string>
#include "time.h"
#include "myglobal.h"
#include "input.h"
#include "Draw.h"
#include "graph.h"
#include "flower.h"


Status::Status() :
bFirstUpdate(true),
existFlag(true)
{
}

void Status::entryAction(){}

void Status::inputAction(){}

void Status::exitAction(){}

void Status::update()
{
	if (bFirstUpdate){
		entryAction();
		bFirstUpdate = false;
	}
	inputAction();
	if (SceneManager::get().nextScene != nullptr || existFlag == false)
	{
		exitAction();
	}
}

void Status::draw(){}

std::shared_ptr<Status> SceneManager::create(Scene sce)
{
//	if (sce == sprologue){ return std::make_shared<Prologue>(); }
	if (sce == sgame) { return std::make_shared<Game>(); }
	if (sce == stitle){ return std::make_shared<Title>(); }
//	if (sce == soption){ return std::make_shared<Option>(); }
	if (sce == sresult){ return std::make_shared<Result>(); }
	if (sce == sexplain){ return std::make_shared<Explain>(); }
//	return std::make_shared<Prologue>();
	return nullptr;
}

SceneManager::SceneManager() :
loadFlag(notLoadData),
nextScene(nullptr),
score(0),
SceneChangeFlag(false)
{
	sceneVec.push_back(std::make_shared<Title>());
}

void SceneManager::update()
{
	Input::get().update();
	(**(sceneVec.end() - 1)).update();
	if (nextScene != nullptr)
	{
		for (auto iter = sceneVec.begin(); iter < sceneVec.end();)
		{
			iter = sceneVec.erase(iter);
		}
		sceneVec.push_back(nextScene);
		nextScene = nullptr;
	}
	for (auto iter = sceneVec.begin(); iter < sceneVec.end();)
	{
		if (!(**iter).existFlag)
		{
			iter = sceneVec.erase(iter);
		}
		else { iter++; }
	}
}

void SceneManager::draw()
{
	for (auto element : sceneVec)
	{
		element->draw();
	}
}

void SceneManager::load()
{
	SEGOE_M = CreateFontToHandle("Segoe UI", SEGOE_M_SIZE, 5, DX_FONTTYPE_ANTIALIASING_4X4);
	SEGOE_S = CreateFontToHandle("Segoe UI", SEGOE_S_SIZE, DX_FONTTYPE_ANTIALIASING_4X4);
	MARU_GOTHIC_M = CreateFontToHandle("AR P丸ゴシック体M", MARU_GOTHIC_M_SIZE, 5, DX_FONTTYPE_ANTIALIASING_4X4);
	MARU_GOTHIC_S = CreateFontToHandle("AR P丸ゴシック体M", MARU_GOTHIC_S_SIZE, 5, DX_FONTTYPE_ANTIALIASING_4X4);
	Graph::get().load();
	Sound::get().load();
	GraphDiv::get().load();
	TimeManager::get().register_map();
}

void SceneManager::set_next(Scene nScene)
{
	nextScene = create(nScene);
}

Title::Title() :
Status()
{
}

void Title::entryAction()
{
	start.set_center(Vector2(280, 430), Vector2(200, 80));
	Sound::playbgm("春の訪れを");
}

void Title::inputAction()
{
	if (existTime > intervalTime)
	{
	}
	existTime++;
	start.update();

	if (start.get_clicked_down())
	{
		SceneManager::get().set_next(sexplain);
		Sound::playone("settle");
	}
	SceneManager::get().effect.update();
}

void Title::draw()
{
	MyDraw::center(SCREEN / 2, Graph::get().handle("title"));
	start.draw_on_mouse(Graph::get().handle("title_start0"), Graph::get().handle("title_start1"));
	SceneManager::get().effect.draw();
}

Game::Game() :
Status(),
tree(SCREEN/2 + Vector2(0, -50), 220),
flowerCloudNum(0),
limitTime(40),
intervalTime(90)
{
}


void Game::entryAction()
{
	TimeManager::get().load_time();
	TimeManager::get().set_last_time();
	existTime = 0;
	if (SceneManager::get().loadFlag == loadData)
	{
	}
	else
	{
	}

	startTime = std::chrono::system_clock::now();
	playTime = 0;

	TimeManager::get().register_map();

	SceneManager::get().score = 0;
	SceneManager::get().SceneChangeFlag = false;
	count = 0;

	//SetClassLongPtr(GetMainWindowHandle(), GCL_HCURSOR, (LONG)HANDCURSOR);

	Sound::get().playbgm("フロルの学び舎");
}

void Game::inputAction(/*, std::shared_ptr<Status> ppOutNextState*/)
{
	SceneManager::get().bloomFlag = true;

	if (DEBUG)
	{
		if (Input::get().keydown(KEY_INPUT_C))
		{
			SceneManager::get().score++;
		}
		if (Input::get().keydown(KEY_INPUT_X))
		{
			SceneManager::get().SceneChangeFlag = true;

		}
	}

	playTime = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - startTime).count();

	double temp = SceneManager::get().score * (17.0 / 45.0) / 50.0 + 0.99;
	flowerCloudNum = temp;
	if (flowerCloudNum > 17)
	{
		flowerCloudNum = 17;
	}

	flowerVec.update();
	TimeManager::get().update();

	if (playTime < 10)
	{
		if (TimeManager::get().check_down("duration1"))
		{
			flowerVec.add(std::make_shared<Object>(tree.get_random()));
		}
	}
	else if (playTime <33)
	{
		if (TimeManager::get().check_down("duration2"))
		{
			flowerVec.add(std::make_shared<Object>(tree.get_random()));
		}
	}
	else if (SceneManager::get().SceneChangeFlag)
	{

	}
	else
	{
		if (TimeManager::get().check_down("duration3"))
		{
			flowerVec.add(std::make_shared<Object>(tree.get_random()));
		}
	}

	if (Input::keydown(KEY_INPUT_Z))
	{
		flowerVec.add(std::make_shared<Object>(tree.get_random()));
	}

	if (playTime == limitTime)
	{
		SceneManager::get().SceneChangeFlag = true;
	}

	if (SceneManager::get().SceneChangeFlag)
	{
		count++;
		if (count >= intervalTime)
		{
			SceneManager::get().set_next(sresult);
		}
	}

	SceneManager::get().effect.update();
	existTime++;
}

void Game::exitAction()
{
	TimeManager::get().save_time();
}

void Game::draw(){
	MyDraw::center(SCREEN.x / 2, SCREEN.y / 2, Graph::handle("back"));
	MyDraw::center(SCREEN.x / 2, SCREEN.y / 2, Graph::handle("tree"));
	//backToTitle.draw_alpha_on_mouse(Graph::handle("back_title"), 10);
	for (int i = 0; i < flowerCloudNum; i++)
	{
		if (i < 10)
		{
			MyDraw::normal(Vector2(), Graph::get().handle("flowercloud0" + std::to_string(i)));
		}
		else
		{
			MyDraw::normal(Vector2(), Graph::get().handle("flowercloud" + std::to_string(i)));
		}
	}
	int temp = SceneManager::get().score;
	DrawFormatStringToHandle(600, 30, 0x6d0122, MARU_GOTHIC_S, "スコア ： %d", temp);
//	DrawFormatStringToHandle(20, 20, 0xFFFFFF, SEGOE_20, "%d / %d", playTime, limitTime);
	MyDraw::center(Vector2(206, 40), Graph::get().handle("gauge"));
	Func::SetDrawBrightHSV(120 * (((double)limitTime - (double)playTime) / (double)limitTime), 200, 255);
	MyDraw::trim(Vector2(65, 8), Vector2(), Vector2(282 * (((double)limitTime - (double)playTime) / (double)limitTime), 64), Graph::get().handle("gauge_bar"));
	Func::SetDrawBrightInt(0xFFFFFF);
	MyDraw::center(Vector2(360, 40), Graph::get().handle("clock"));
	MyDraw::animation(Vector2(130, 400 + 30 * sin(((double)existTime*2.0*PI) / 300.0)), Graph::get().handle("chara_panic0"), Graph::get().handle("chara_panic1"), existTime, 60, true);
	flowerVec.draw();
	SceneManager::get().effect.draw();
	if (SceneManager::get().SceneChangeFlag)
	{
		if (count < 15)
		{
			MyDraw::center(SCREEN / 2 + Vector2(0, 450 * (15.0 - (double)count) /15.0), Graph::get().handle("time_up"));
		}
		else if (count < 75)
		{
			MyDraw::center(SCREEN / 2, Graph::get().handle("time_up"));
		}
		else
		{
			MyDraw::center(SCREEN / 2 + Vector2(0, -450 * ((double)count - 75.0) / 15.0), Graph::get().handle("time_up"));
		}
	}
}

Result::String2::String2() :
original(),
str("")
{

}

Result::String2::String2(double x_, double y_, std::string str_) :
original(x_, y_),
str(str_)
{

}

void Result::String2::draw(Vector2 camera)
{
	int wd = GetDrawFormatStringWidthToHandle(MARU_GOTHIC_S, "%s", str.c_str());
	DrawFormatStringToHandle(original.x + camera.x - wd / 2, original.y + camera.y, 0x6d0122, MARU_GOTHIC_S, "%s", str.c_str());
}

void Result::String2::set(Vector2 pos)
{
	original = pos;
}

void Result::String2::set(std::string str_)
{
	str = str_;
}


Result::Result() :
Status(),
flowerCloudNum(0),
rank(0)
{
	retry.set_center(Vector2(620, 90), Vector2(160, 70));
}

void Result::entryAction()
{
	double temp = SceneManager::get().score * (17.0 / 45.0) / 50.0 + 0.99;
	flowerCloudNum = temp;
	if (flowerCloudNum > 17)
	{
		flowerCloudNum = 17;
	}
	if (SceneManager::get().score < 800){ rank = 0; }
	else if (SceneManager::get().score < 1700){ rank = 1; }
	else if (SceneManager::get().score < 2200){ rank = 2; }
	else if (SceneManager::get().score < 2700){ rank = 3; }
	else { rank = 4; }

	for (int i = 0; i < 5; i++)
	{
		for (int k = 0; k < 3; k++)
			str[i][k].set(Vector2(330, 415 + (k * 45)));
	}

	str[4][0].set("君のセンスは最高です！");
	str[4][1].set("是非その才能をCCSで");
	str[4][2].set("活かすと良いのですよ！");
	str[3][0].set("君のおかげで満開です！");
	str[3][1].set("CCSへようこそなのです！");
	str[3][2].set("");
	str[2][0].set("キレイな桜が咲いたのです！");
	str[2][1].set("CCSのところに来てくれて");
	str[2][2].set("ありがとうです！");
	str[1][0].set("なんとか半分ですね……！");
	str[1][1].set("寂しいのでもう一本咲かせましょう！");
	str[1][2].set("");
	str[0][0].set("あんまりうまく");
	str[0][1].set("咲かせられなかったのです……");
	str[0][2].set("急いでもう一回やり直しましょう！");

}

void Result::inputAction(/*, std::shared_ptr<Status> ppOutNextState*/)
{
	if (DEBUG)
	{
		if (Input::get().keydown(KEY_INPUT_C))
		{
			rank++;
		}
		if (Input::get().keydown(KEY_INPUT_V))
		{
			rank--;
		}
	}
	retry.update();
	if (retry.get_clicked_down())
	{
		Sound::playone("settle");
		SceneManager::get().set_next(sgame);
	}
	SceneManager::get().effect.update();
}

void Result::exitAction()
{
}

void Result::draw()
{
	MyDraw::center(SCREEN.x / 2, SCREEN.y / 2, Graph::handle("back"));
	MyDraw::center(SCREEN.x / 2, SCREEN.y / 2, Graph::handle("tree"));
	//backToTitle.draw_alpha_on_mouse(Graph::handle("back_title"), 10);
	for (int i = 0; i < flowerCloudNum; i++)
	{
		if (i < 10)
		{
			MyDraw::normal(Vector2(), Graph::get().handle("flowercloud0" + std::to_string(i)));
		}
		else
		{
			MyDraw::normal(Vector2(), Graph::get().handle("flowercloud" + std::to_string(i)));
		}
	}
	MyDraw::center(SCREEN / 2, Graph::get().handle("result"));
	MyDraw::center(SCREEN / 2 + Vector2(0, -45), Graph::get().handle("rank"+std::to_string(rank)));
	int temp = SceneManager::get().score;
	DrawFormatStringToHandle(SCREEN.x / 2 - 30, SCREEN.y / 2, 0x6d0122, MARU_GOTHIC_M, "スコア ： %d", temp);
	MyDraw::center(Vector2(650, 450), Graph::get().handle("chara" + std::to_string(rank)));
	if (rank == 0 || rank == 2 || rank == 4)
	{
		for (int i = 0; i < 3; i++)
		{
			str[rank][i].draw(Vector2(0, -27));
		}
	}
	else
	{
		for (int i = 0; i < 3; i++)
		{
			str[rank][i].draw();
		}
	}
	retry.draw_on_mouse(Graph::get().handle("retry0"), Graph::get().handle("retry1"));
	SceneManager::get().effect.draw();
}

Explain::Explain():
Status()
{

}

void Explain::entryAction()
{
	log.load();
	start.set_center(Vector2(550, 520), Vector2(80, 40));
	existTime = 0;
}

void Explain::inputAction()
{
	log.update();
	if (Input::get().mouseDown)
	{
		log.set_draw_flag_all();
	}
	if (log.check_all_drawn())
	{
		start.update();
		if (start.get_clicked_down())
		{
			SceneManager::get().set_next(sgame);
			Sound::playone("settle");
		}
	}

	SceneManager::get().effect.update();
	existTime++;
}

void Explain::exitAction()
{
}

void Explain::draw()
{
	MyDraw::center(SCREEN / 2, Graph::get().handle("explain"));
	log.draw();
	start.draw_ratio_on_mouse_alpha_fadein(Graph::get().handle("explain_start_s"), Graph::get().handle("explain_start_l"), 0.8, 1.0, 10, 120, 60);
	MyDraw::animation(Vector2(670, 370), Graph::get().handle("chara_panic0"), Graph::get().handle("chara_panic1"), existTime, 60);
	SceneManager::get().effect.draw();
}

