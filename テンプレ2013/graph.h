#pragma once

#include <vector>
#include <map>
#include <string>
#include <unordered_map>
#include <iostream>
#include <sstream>
#include <Windows.h>

class Dir
{
public:
	// コンストラクタ
	Dir(void);
	// デストラクタ
	virtual ~Dir(void);
	// ファイル一覧取得
	// folder : フォルダの絶対パスを入力とする 
	// 例 : "D:\\Users\\Pictures\\"
	static std::vector<std::string> read(std::string folder);
};

class Graph{
public:
	//シングルトン
	Graph& operator=(const Graph& a) = delete;
	Graph(const Graph& a) = delete;
	static Graph& get();
	void load();

	//ハンドル取得
	static int handle(std::string name);

	void LoadToMap(std::string name);
private:
	std::unordered_map<std::string, int> handlemap;
	Graph();
};


class GraphDiv{
public:
	//シングルトン
	GraphDiv& operator=(const GraphDiv& a) = delete;
	GraphDiv(const GraphDiv& a) = delete;
	static GraphDiv& get();
	void load();

	//ハンドル取得
	static int handle(std::string name, int num);

	class gh_array{
		static const int ary_num = 512;
	public:
		int arr[ary_num];
	};

private:
	std::unordered_map<std::string, gh_array> handlemap;

	//pngのみ読み込み
	GraphDiv();

	//pngのみ読み込み Imagesフォルダを見る
	void LoadToMap(std::string name, int AllNum, int XNum, int YNum, int XSize, int YSize);
	void LoadFont(std::string reg_name, std::string file_path, std::string font_name, int fontsize, int thick);
};





class Font{
public:
	//シングルトン
	Font& operator=(const Font& a) = delete;
	Font(const Font& a) = delete;
	static Font& get();
	void load();

	int operator()(std::string name);
	//ハンドル取得
	static int handle(std::string name);
	static int def();
	std::string defalutFontName;

private:
	std::unordered_map<std::string, int> handlemap;
	Font();

	//フォント読み込み（すでにOSに登録済みのもの）
	void LoadFont(std::string reg_name, std::string font_name, int fontsize, int thick);
	//フォント読み込み
	void LoadFont(std::string reg_name, std::string file_path, std::string font_name, int fontsize, int thick);
};

extern Font& font;



class SoundHandle{
public:
	int handle;
	const double volume;	// 0.0 ~ 1.0
	int play_cool;	// < 0で再生しない
	const int play_rate;	//再生間隔 (効果音などが連続で再生するときの間隔）0で1フレーム毎に再生可能

	SoundHandle();
	SoundHandle(int handle_, double volume_ = 1.0, int play_rate_ = 0);
	void SetVolume(double master);
};

class Sound{
public:

	//シングルトン
	Sound& operator=(const Sound& a) = delete;
	Sound(const Sound& a) = delete;
	static Sound& get();
	void load();

	//ハンドルを取得
	static int handle(std::string name);

	//一回だけ再生
	static void playone(std::string name);

	//ループ再生
	static void playloop(std::string name);

	//BGM再生 BGMは常時一つだけ
	static void playbgm(std::string name);

	//BGM停止
	static void stopbgm();

	//再生中の音をすべて停止
	static void stopall();

	//指定した音の再生を停止
	static void stopone(std::string name);

	//ボリュームをセット
	static void setvolume(double master);

	//再生間隔フレームを更新
	static void update();

private:
	int bgmhandle = -1;
	double masterVolume = 1.0;
	std::unordered_map<std::string, SoundHandle> handlemap;

	Sound();
	void LoadToMap(std::string name);
	void LoadToMap(std::string name, double volume, int play_rate);
};