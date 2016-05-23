#include <DxLib.h>

#include "myglobal.h"
#include "scene.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetAlwaysRunFlag(true);

	SetWindowIconID(101);
	SetMainWindowText("フロルの春風パニック");

	ChangeWindowMode(TRUE);//非全画面にセット
	SetGraphMode(SCREEN.x,  SCREEN.y, 32);//画面サイズ指定
	SetOutApplicationLogValidFlag(FALSE);//Log.txtを生成しないように設定

	if (DxLib_Init() == 1){ return -1; }//初期化に失敗時にエラーを吐かせて終了
	

	//
	//ここで敵やプレイヤーのオブジェクトの実体を作る
	//
	SceneManager::get().load();


	while (ProcessMessage() == 0)
	{
		ClearDrawScreen();//裏画面消す
		SetDrawScreen(DX_SCREEN_BACK);//描画先を裏画面に	

		SceneManager::get().update();
		SceneManager::get().draw();

		ScreenFlip();//裏画面を表画面にコピー
	}

	DxLib_End();
	return 0;
}