#pragma once

#include <DxLib.h>

class Input{
private:
	Input(){//コンストラクタをprivateに置き、クラス外で生成するのを禁止
		x = 30;
	}

	Input(const Input& r) = delete;//コピーを禁止
	Input& operator=(const Input& r) = delete; //代入を禁止

public:
	static Input& get()
	{
		static Input inst;
		return inst;
	}

	int x;
	int keystate[256];
	char buf[256];
	bool mouseBuf;
	int mouseState;
	bool mouseDown;
	int mousex, mousey;
	Vector2 mouse;
	Vector2 lastMouse;

	void update()
	{
		lastMouse = mouse;
		GetHitKeyStateAll(buf);
		for (int i = 0; i< 256; i++)
		{
			if (buf[i] == 1) keystate[i]++;
			else keystate[i] = 0;
		}
		mouseBuf = GetMouseInput()& MOUSE_INPUT_LEFT;
		if (mouseBuf == 1) mouseState++;
		else mouseState = 0;
		mouseDown = mouseState == 1;
		GetMousePoint(&mousex, &mousey);
		mouse.Set(mousex, mousey);
	}

	double mouse_speed()
	{
		return (mouse - lastMouse).Magnitude() * 60;
	}

	static bool keynow(int keynum)
	{
		return get().keystate[keynum] > 0;
	}

	static bool keydown(int keynum)
	{
		return get().keystate[keynum] == 1;
	}

	static int keytime(int keynum)
	{
		return get().keystate[keynum];
	}
	static int get_mouse_x()
	{
		return get().mousex;
	}
	static int get_mouse_y()
	{
		return get().mousey;
	}
};
