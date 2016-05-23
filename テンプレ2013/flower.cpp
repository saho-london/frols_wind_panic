#include "flower.h"
#include "Draw.h"
#include "Graph.h"
#include <DxLib.h>
#include "MyFunc.h"
#include "Scene.h"
#include "input.h"

FlowerData::FlowerData() :
position(),
existTime(0),
state(sbud),
turnFlag(Random::Rand(1))
{

}

FlowerData::FlowerData(const Vector2 &pos) :
position(pos),
existTime(0),
state(sbud),
turnFlag(Random::Rand(1))
{

}

FlowerData FlowerData::get()
{
	return *this;
}

void FlowerData::set(const Vector2 &pos)
{
	position = pos;
}

void FlowerData::set_state(FlowerStatus sta)
{
	state = sta;
}

IFlower::IFlower() :
bloomTime(60),
deadTime(180),
IsDead(false),
range(Vector2(), 30)
{
	flowerData = std::make_shared<FlowerData>();
}

IFlower::IFlower(const Vector2 &pos) :
bloomTime(60),
deadTime(180),
IsDead(false),
range(pos, 30)
{
	flowerData = std::make_shared<FlowerData>(pos);
}

void IFlower::set(const Vector2 &pos)
{
	flowerData->position = pos;
}

void IFlower::update()
{
	flowerData->existTime++;
	range.update();
}

Vector2 IFlower::get_pos()
{
	return flowerData->position;
}

int IFlower::get_exist_time()
{
	return flowerData->existTime;
}

std::shared_ptr<FlowerData> IFlower::get_flower_data()
{
	return flowerData;
}

void IFlower::set_flower_data(std::shared_ptr<FlowerData> fdata)
{
	flowerData = fdata;
}


Flower::Flower():
IFlower()
{

}

Flower::Flower(const Vector2 &pos) :
IFlower(pos)
{

}

void Flower::update()
{
	flowerData->existTime++;
	if (flowerData->existTime > deadTime)
	{
		IsDead = true;
		if (!SceneManager::get().SceneChangeFlag)
		{
			Sound::get().playone("fail");
		}
	}
	range.update();
	if (range.get_clicked() && Input::get().mouseDown && SceneManager::get().bloomFlag&& !SceneManager::get().SceneChangeFlag)
	{
		IsDead = true;
		SceneManager::get().bloomFlag = false;
		Sound::get().playone("bloom");
		for (int i = 0; i < 50; i++)
		{
			SceneManager::get().effect.add(std::make_shared<AllowEffect>(flowerData->position));
		}
		if (flowerData->existTime - (double)bloomTime < 20)
		{
			SceneManager::get().score += 50;
			SceneManager::get().effect.add(std::make_shared<ScoreEffect>(flowerData->position, 50));
		}
		else
		{
			SceneManager::get().score += (1.0 - (((double)flowerData->existTime - (double)bloomTime) / ((double)deadTime - (double)bloomTime)))*35.0 + 15.0;
			SceneManager::get().effect.add(std::make_shared<ScoreEffect>(flowerData->position, (1.0 - (((double)flowerData->existTime - (double)bloomTime) / ((double)deadTime - (double)bloomTime)))*35.0 + 15.0));
		}
	}
}

void Flower::draw()
{
	MyDraw::fade_fadeout(flowerData->position, GraphDiv::get().handle("flower", 2), GraphDiv::get().handle("flower", 3), flowerData->existTime - bloomTime, deadTime - bloomTime, 60, 120, flowerData->turnFlag);
}

Bud::Bud(const Vector2 &pos) :
IFlower(pos)
{

}

void Bud::update()
{
	flowerData->existTime++;
	if (flowerData->existTime > deadTime)
	{
		IsDead = true;
	}
	range.update();
	if (range.get_clicked() && Input::get().mouseDown && SceneManager::get().bloomFlag && !SceneManager::get().SceneChangeFlag)
	{
		SceneManager::get().bloomFlag = false;
		Sound::get().playone("bloom");
		IsDead = true;
		SceneManager::get().score += 35.0*((double)flowerData->existTime / (double)bloomTime) + 15.0;
		SceneManager::get().effect.add(std::make_shared<ScoreEffect>(flowerData->position, 35.0*((double)flowerData->existTime / (double)bloomTime) + 15.0));
		for (int i = 0; i < 50; i++)
		{
			SceneManager::get().effect.add(std::make_shared<AllowEffect>(flowerData->position));
		}
	}
}


void Bud::draw()
{
	//MyDraw::center(flowerData->position, GraphDiv::get().handle("flower", 0), 255, flowerData->turnFlag);
	//MyDraw::center(flowerData->position, GraphDiv::get().handle("flower", 1), 255 * (double)flowerData->existTime / (double)bloomTime, flowerData->turnFlag);
	MyDraw::fade_popin(flowerData->position, GraphDiv::get().handle("flower", 0), GraphDiv::get().handle("flower", 1), flowerData->existTime, bloomTime, 5, flowerData->turnFlag);
}

Object::Object(const Vector2 &pos)
{
	flowerPtr = std::make_shared<Bud>(pos);
}

void Object::update()
{
	flowerPtr->update();
	if (flowerPtr->get_flower_data()->existTime == flowerPtr->bloomTime)
	{
		bloom();
	}
	if (flowerPtr->IsDead)
	{
		IsDead = true;
	}
}

void Object::draw()
{
	flowerPtr->draw();
}

void Object::bloom()
{
	std::shared_ptr<FlowerData> temp;
	temp = flowerPtr->get_flower_data();
	flowerPtr = std::make_shared<Flower>(temp->position);
	flowerPtr->set_flower_data(temp);
	flowerPtr->get_flower_data()->set_state(sflower);
}
