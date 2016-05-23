#include <Dxlib.h>

#include "graph.h"
#include "MyFunc.h"

// コンストラクタ
Dir::Dir(void){}
// デストラクタ
Dir::~Dir(void){}

// ファイル一覧取得
// folder : フォルダの絶対パスを入力とする 
// 例 : "D:\\Users\\Pictures\\"
std::vector<std::string> Dir::read(std::string folder){
	// 宣言
	std::vector<std::string> fileList;
	HANDLE hFind;
	WIN32_FIND_DATA fd;

	// ファイル名検索のためにワイルドカード追加
	// 例 : "D:\\Users\\Pictures\\*.*"
	std::stringstream ss;
	ss << folder;
	std::string::iterator itr = folder.end();
	itr--;
	if (*itr != '\\') ss << '\\';
	ss << "*.*";

	// ファイル探索
	// FindFirstFile(ファイル名, &fd);
	hFind = FindFirstFile(ss.str().c_str(), &fd);

	// 検索失敗
	if (hFind == INVALID_HANDLE_VALUE){
		std::cout << "ファイル一覧を取得できませんでした" << std::endl;
		exit(1); // エラー終了
	}

	// ファイル名をリストに格納するためのループ
	do{
		// フォルダは除く
		if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			&& !(fd.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN))
		{
			//ファイル名をリストに格納
			char *file = fd.cFileName;
			std::string str = file;
			fileList.push_back(str);
		}
	} while (FindNextFile(hFind, &fd)); //次のファイルを探索

	// hFindのクローズ
	FindClose(hFind);

	return fileList;
}

Graph::Graph(){
}

Graph& Graph::get(){
	static Graph inst;
	return inst;
}

void Graph::load(){
	std::vector<std::string> fileVec = Dir::read("Image");
	for (auto i = fileVec.begin(); i < fileVec.end(); i++){
		LoadToMap(i->c_str());
	}
}

//ハンドル取得
int Graph::handle(std::string name){
	if (get().handlemap.find(name) == get().handlemap.end()){
		std::string log = "Graph::handle内部で読み込みエラー発生\n読み込もうとしたstring : " + name;
		MessageBox(NULL, log.c_str(), "", MB_OK);
	}
	return get().handlemap.at(name);
}

void Graph::LoadToMap(std::string name){
	int gh;
	std::string loadname = "Image/" + name;
	gh = LoadGraph(loadname.c_str());
	if (gh != -1){
		std::vector<std::string> extensionList = { ".png", ".jpg" };
		for (auto &i : extensionList){
			Func::strReplace(name, i, "");
		}
		handlemap.emplace(name, gh);
		return;
	}
}



GraphDiv::GraphDiv(){
}
GraphDiv& GraphDiv::get(){
	static GraphDiv inst;
	return inst;
}

void GraphDiv::load(){
	LoadToMap("flowercloud.png", 3, 3, 1, 256, 100);
	LoadToMap("flower.png", 4, 4, 1, 128, 128);
}

//ハンドル取得
int GraphDiv::handle(std::string name, int num){
	if (get().handlemap.find(name) == get().handlemap.end()){
		std::string log = "GraphDiv::handle内部で読み込みエラー発生\n読み込もうとしたstring : " + name;
		MessageBox(NULL, log.c_str(), "", MB_OK);
	}
	return get().handlemap.at(name).arr[num];
}


void GraphDiv::LoadToMap(std::string name, int AllNum, int XNum, int YNum, int XSize, int YSize){
	std::string loadname = "ImageDiv/" + name;
	gh_array gh_array_;
	LoadDivGraph(loadname.c_str(), AllNum, XNum, YNum, XSize, YSize, &gh_array_.arr[0]);

	std::vector<std::string> extensionList = { ".png", ".jpg" };
	for (auto &i : extensionList){
		Func::strReplace(name, i, "");
	}
	handlemap.emplace(name, gh_array_);
}



Font::Font(){
}

Font& Font::get(){
	static Font inst;
	return inst;
}

int Font::operator()(std::string name){
	return handle(name);
}

//ハンドル取得
int Font::handle(std::string name){
	if (get().handlemap.find(name) == get().handlemap.end()){
		std::string log = "Font::handle内部で読み込みエラー発生\n読み込もうとしたstring : " + name;
		MessageBox(NULL, log.c_str(), "", MB_OK);
	}
	return get().handlemap.at(name);
}

//ハンドル取得
int Font::def(){
	return get().handlemap.at(get().defalutFontName);
}

Font& font = Font::get();

//登録名・ファイルのパス・フォントの名前を指定（PCに元から入っているもの）
//ex ("HG96", "Hogeman's_Font", 96, 5)
void Font::LoadFont(std::string reg_name, std::string font_name, int fontsize, int thick){
	int tmp_handle = CreateFontToHandle(font_name.c_str(), fontsize, thick, DX_FONTTYPE_ANTIALIASING_4X4);
	handlemap.emplace(reg_name.c_str(), tmp_handle);
}

//登録名・ファイルのパス・フォントの名前を指定
//ex ("HG96", "hoge.ttf", "Hogeman's_Font", 96, 5)
void Font::LoadFont(std::string reg_name, std::string file_path, std::string font_name, int fontsize, int thick){

	file_path = "Fonts/" + file_path;
	const char* filename = file_path.c_str();

	// ファイルのサイズを得る
	int FontFileSize = FileRead_size(filename);
	// フォントファイルを開く
	int FontFileHandle = FileRead_open(filename);
	// フォントデータ格納用のメモリ領域を確保
	void *Buffer = malloc(FontFileSize);
	// フォントファイルを丸ごとメモリに読み込む
	FileRead_read(Buffer, FontFileSize, FontFileHandle);
	// AddFontMemResourceEx引数用
	DWORD font_num = 0;
	// メモリに読み込んだフォントデータをシステムに追加
	if (AddFontMemResourceEx(Buffer, FontFileSize, NULL, &font_num) != 0){}
	else
	{
		// フォント読込エラー処理
		MessageBox(NULL, "フォント読込失敗", "", MB_OK);
	}

	int tmp_handle = CreateFontToHandle(font_name.c_str(), fontsize, thick, DX_FONTTYPE_ANTIALIASING_4X4);
	handlemap.emplace(reg_name.c_str(), tmp_handle);
}



SoundHandle::SoundHandle() :
handle(0),
volume(0),
play_cool(0),
play_rate(0)
{
}

SoundHandle::SoundHandle(int handle_, double volume_, int play_rate_) :
handle(handle_),
volume(volume_),
play_cool(0),
play_rate(play_rate_)
{
}

void SoundHandle::SetVolume(double master)
{
	ChangeVolumeSoundMem(master * volume * 255.0, handle);
}

Sound::Sound(){
}

Sound& Sound::get(){
	static Sound inst;
	return inst;
}

void Sound::load(){
	std::vector<std::string> fileVec = Dir::read("Sound");
	for (auto i = fileVec.begin(); i < fileVec.end(); i++){
		LoadToMap(i->c_str());
	}
}

//ハンドルを取得
int Sound::handle(std::string name){
	if (get().handlemap.find(name) == get().handlemap.end()){
		std::string log = "Sound::handle内部で読み込みエラー発生\n読み込もうとしたstring : " + name;
		MessageBox(NULL, log.c_str(), "", MB_OK);
	}
	return get().handlemap[name].handle;
}

//一回だけ再生
void Sound::playone(std::string name){
	auto &a = get().handlemap[name];
	if (a.play_cool <= 0){
		PlaySoundMem(get().handle(name), DX_PLAYTYPE_BACK);
		a.play_cool = a.play_rate;
	}
}

//ループ再生
void Sound::playloop(std::string name){
	PlaySoundMem(get().handle(name), DX_PLAYTYPE_LOOP);
}

//BGM再生 BGMは常時一つだけ
void Sound::playbgm(std::string name){
	StopSoundMem(get().bgmhandle);
	get().bgmhandle = get().handle(name);
	PlaySoundMem(get().bgmhandle, DX_PLAYTYPE_LOOP);
}

//BGM停止
void Sound::stopbgm(){
	StopSoundMem(get().bgmhandle);
}

//再生中の音をすべて停止
void Sound::stopall(){
	for (auto &i : get().handlemap){
		StopSoundMem(i.second.handle);
	}
}

//指定した音の再生を停止
void Sound::stopone(std::string name){
	StopSoundMem(get().handle(name));
}

//ボリュームをセット
void Sound::setvolume(double master)
{
	get().masterVolume = master;
	for (auto &i : get().handlemap){
		i.second.SetVolume(get().masterVolume);
	}
}

//再生間隔フレームを更新
void Sound::update()
{
	for (auto &i : get().handlemap){
		if (i.second.play_cool > 0){
			i.second.play_cool--;
		}
	}
}

void Sound::LoadToMap(std::string name){
	int tmphandle;
	std::string loadname = "Sound/" + name;
	tmphandle = LoadSoundMem(loadname.c_str());
	if (tmphandle != -1){
		std::vector<std::string> extensionList = { ".wav", ".ogg", ".mp3" };
		for (auto &i : extensionList){
			Func::strReplace(name, i, "");
		}

		handlemap.emplace(name, SoundHandle(tmphandle));
		return;
	}
	OutputDebugString(("\n" + name + " is not exist\n").c_str());
	//assert(1 == 0 && "sound file is not exist" && name.c_str());
}

void Sound::LoadToMap(std::string name, double volume, int play_rate){
	int tmphandle;
	std::string loadname = "Sound/" + name;
	tmphandle = LoadSoundMem(loadname.c_str());
	if (tmphandle != -1){
		std::vector<std::string> extensionList = { ".wav", ".ogg", ".mp3" };
		for (auto &i : extensionList){
			Func::strReplace(name, i, "");
		}
		handlemap.emplace(name, SoundHandle(tmphandle, volume, play_rate));
		return;
	}
	OutputDebugString(("\n" + name + " is not exist\n").c_str());
}

