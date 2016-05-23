#include <Dxlib.h>

#include "graph.h"
#include "MyFunc.h"

// �R���X�g���N�^
Dir::Dir(void){}
// �f�X�g���N�^
Dir::~Dir(void){}

// �t�@�C���ꗗ�擾
// folder : �t�H���_�̐�΃p�X����͂Ƃ��� 
// �� : "D:\\Users\\Pictures\\"
std::vector<std::string> Dir::read(std::string folder){
	// �錾
	std::vector<std::string> fileList;
	HANDLE hFind;
	WIN32_FIND_DATA fd;

	// �t�@�C���������̂��߂Ƀ��C���h�J�[�h�ǉ�
	// �� : "D:\\Users\\Pictures\\*.*"
	std::stringstream ss;
	ss << folder;
	std::string::iterator itr = folder.end();
	itr--;
	if (*itr != '\\') ss << '\\';
	ss << "*.*";

	// �t�@�C���T��
	// FindFirstFile(�t�@�C����, &fd);
	hFind = FindFirstFile(ss.str().c_str(), &fd);

	// �������s
	if (hFind == INVALID_HANDLE_VALUE){
		std::cout << "�t�@�C���ꗗ���擾�ł��܂���ł���" << std::endl;
		exit(1); // �G���[�I��
	}

	// �t�@�C���������X�g�Ɋi�[���邽�߂̃��[�v
	do{
		// �t�H���_�͏���
		if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			&& !(fd.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN))
		{
			//�t�@�C���������X�g�Ɋi�[
			char *file = fd.cFileName;
			std::string str = file;
			fileList.push_back(str);
		}
	} while (FindNextFile(hFind, &fd)); //���̃t�@�C����T��

	// hFind�̃N���[�Y
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

//�n���h���擾
int Graph::handle(std::string name){
	if (get().handlemap.find(name) == get().handlemap.end()){
		std::string log = "Graph::handle�����œǂݍ��݃G���[����\n�ǂݍ������Ƃ���string : " + name;
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

//�n���h���擾
int GraphDiv::handle(std::string name, int num){
	if (get().handlemap.find(name) == get().handlemap.end()){
		std::string log = "GraphDiv::handle�����œǂݍ��݃G���[����\n�ǂݍ������Ƃ���string : " + name;
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

//�n���h���擾
int Font::handle(std::string name){
	if (get().handlemap.find(name) == get().handlemap.end()){
		std::string log = "Font::handle�����œǂݍ��݃G���[����\n�ǂݍ������Ƃ���string : " + name;
		MessageBox(NULL, log.c_str(), "", MB_OK);
	}
	return get().handlemap.at(name);
}

//�n���h���擾
int Font::def(){
	return get().handlemap.at(get().defalutFontName);
}

Font& font = Font::get();

//�o�^���E�t�@�C���̃p�X�E�t�H���g�̖��O���w��iPC�Ɍ���������Ă�����́j
//ex ("HG96", "Hogeman's_Font", 96, 5)
void Font::LoadFont(std::string reg_name, std::string font_name, int fontsize, int thick){
	int tmp_handle = CreateFontToHandle(font_name.c_str(), fontsize, thick, DX_FONTTYPE_ANTIALIASING_4X4);
	handlemap.emplace(reg_name.c_str(), tmp_handle);
}

//�o�^���E�t�@�C���̃p�X�E�t�H���g�̖��O���w��
//ex ("HG96", "hoge.ttf", "Hogeman's_Font", 96, 5)
void Font::LoadFont(std::string reg_name, std::string file_path, std::string font_name, int fontsize, int thick){

	file_path = "Fonts/" + file_path;
	const char* filename = file_path.c_str();

	// �t�@�C���̃T�C�Y�𓾂�
	int FontFileSize = FileRead_size(filename);
	// �t�H���g�t�@�C�����J��
	int FontFileHandle = FileRead_open(filename);
	// �t�H���g�f�[�^�i�[�p�̃������̈���m��
	void *Buffer = malloc(FontFileSize);
	// �t�H���g�t�@�C�����ۂ��ƃ������ɓǂݍ���
	FileRead_read(Buffer, FontFileSize, FontFileHandle);
	// AddFontMemResourceEx�����p
	DWORD font_num = 0;
	// �������ɓǂݍ��񂾃t�H���g�f�[�^���V�X�e���ɒǉ�
	if (AddFontMemResourceEx(Buffer, FontFileSize, NULL, &font_num) != 0){}
	else
	{
		// �t�H���g�Ǎ��G���[����
		MessageBox(NULL, "�t�H���g�Ǎ����s", "", MB_OK);
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

//�n���h�����擾
int Sound::handle(std::string name){
	if (get().handlemap.find(name) == get().handlemap.end()){
		std::string log = "Sound::handle�����œǂݍ��݃G���[����\n�ǂݍ������Ƃ���string : " + name;
		MessageBox(NULL, log.c_str(), "", MB_OK);
	}
	return get().handlemap[name].handle;
}

//��񂾂��Đ�
void Sound::playone(std::string name){
	auto &a = get().handlemap[name];
	if (a.play_cool <= 0){
		PlaySoundMem(get().handle(name), DX_PLAYTYPE_BACK);
		a.play_cool = a.play_rate;
	}
}

//���[�v�Đ�
void Sound::playloop(std::string name){
	PlaySoundMem(get().handle(name), DX_PLAYTYPE_LOOP);
}

//BGM�Đ� BGM�͏펞�����
void Sound::playbgm(std::string name){
	StopSoundMem(get().bgmhandle);
	get().bgmhandle = get().handle(name);
	PlaySoundMem(get().bgmhandle, DX_PLAYTYPE_LOOP);
}

//BGM��~
void Sound::stopbgm(){
	StopSoundMem(get().bgmhandle);
}

//�Đ����̉������ׂĒ�~
void Sound::stopall(){
	for (auto &i : get().handlemap){
		StopSoundMem(i.second.handle);
	}
}

//�w�肵�����̍Đ����~
void Sound::stopone(std::string name){
	StopSoundMem(get().handle(name));
}

//�{�����[�����Z�b�g
void Sound::setvolume(double master)
{
	get().masterVolume = master;
	for (auto &i : get().handlemap){
		i.second.SetVolume(get().masterVolume);
	}
}

//�Đ��Ԋu�t���[�����X�V
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

