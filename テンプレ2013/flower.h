#pragma once

#include "Vector2.h"
#include <memory>
#include "manager.h"

enum FlowerStatus
{
	sbud,
	sflower,
	scloud
};

class FlowerData
{
public:
	int existTime;
	Vector2 position;
	FlowerStatus state;
	bool turnFlag;

	FlowerData();
	FlowerData(const Vector2 &pos);

	FlowerData get();
	void set(const Vector2 &pos);
	void set_state(FlowerStatus sta);
};

class IFlower
{
protected:
	std::shared_ptr<FlowerData> flowerData;

public:
	const int bloomTime;
	const int deadTime;
	bool IsDead;
	Circle range;

	IFlower();
	IFlower(const Vector2 &pos);

	virtual void set(const Vector2 &pos);
	virtual void update();
	virtual void draw() = 0;

	Vector2 get_pos();
	int get_exist_time();
	std::shared_ptr<FlowerData> get_flower_data();

	void set_flower_data(std::shared_ptr<FlowerData> fdata);
};

class Flower : public IFlower
{
public:
	Flower();
	Flower(const Vector2 &pos);

	void update() override;
	void draw() override;
};

class Bud : public IFlower
{
public:
	Bud(const Vector2 &pos);

	void update() override;
	void draw() override;
};

//class FlowerCloud : public IFlower
//{
//	int graphNumber;
//public:
//	FlowerCloud();
//	FlowerCloud(const Vector2 &pos);
//
//	void draw();
//};

class Object : public IObject
{
	std::shared_ptr<IFlower> flowerPtr;

public:
	Object(const Vector2 &pos);

	void update() override;
	void draw() override;

	void bloom();
	void fix();
};

