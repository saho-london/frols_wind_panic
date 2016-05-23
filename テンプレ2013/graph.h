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
	// �R���X�g���N�^
	Dir(void);
	// �f�X�g���N�^
	virtual ~Dir(void);
	// �t�@�C���ꗗ�擾
	// folder : �t�H���_�̐�΃p�X����͂Ƃ��� 
	// �� : "D:\\Users\\Pictures\\"
	static std::vector<std::string> read(std::string folder);
};

class Graph{
public:
	//�V���O���g��
	Graph& operator=(const Graph& a) = delete;
	Graph(const Graph& a) = delete;
	static Graph& get();
	void load();

	//�n���h���擾
	static int handle(std::string name);

	void LoadToMap(std::string name);
private:
	std::unordered_map<std::string, int> handlemap;
	Graph();
};


class GraphDiv{
public:
	//�V���O���g��
	GraphDiv& operator=(const GraphDiv& a) = delete;
	GraphDiv(const GraphDiv& a) = delete;
	static GraphDiv& get();
	void load();

	//�n���h���擾
	static int handle(std::string name, int num);

	class gh_array{
		static const int ary_num = 512;
	public:
		int arr[ary_num];
	};

private:
	std::unordered_map<std::string, gh_array> handlemap;

	//png�̂ݓǂݍ���
	GraphDiv();

	//png�̂ݓǂݍ��� Images�t�H���_������
	void LoadToMap(std::string name, int AllNum, int XNum, int YNum, int XSize, int YSize);
	void LoadFont(std::string reg_name, std::string file_path, std::string font_name, int fontsize, int thick);
};





class Font{
public:
	//�V���O���g��
	Font& operator=(const Font& a) = delete;
	Font(const Font& a) = delete;
	static Font& get();
	void load();

	int operator()(std::string name);
	//�n���h���擾
	static int handle(std::string name);
	static int def();
	std::string defalutFontName;

private:
	std::unordered_map<std::string, int> handlemap;
	Font();

	//�t�H���g�ǂݍ��݁i���ł�OS�ɓo�^�ς݂̂��́j
	void LoadFont(std::string reg_name, std::string font_name, int fontsize, int thick);
	//�t�H���g�ǂݍ���
	void LoadFont(std::string reg_name, std::string file_path, std::string font_name, int fontsize, int thick);
};

extern Font& font;



class SoundHandle{
public:
	int handle;
	const double volume;	// 0.0 ~ 1.0
	int play_cool;	// < 0�ōĐ����Ȃ�
	const int play_rate;	//�Đ��Ԋu (���ʉ��Ȃǂ��A���ōĐ�����Ƃ��̊Ԋu�j0��1�t���[�����ɍĐ��\

	SoundHandle();
	SoundHandle(int handle_, double volume_ = 1.0, int play_rate_ = 0);
	void SetVolume(double master);
};

class Sound{
public:

	//�V���O���g��
	Sound& operator=(const Sound& a) = delete;
	Sound(const Sound& a) = delete;
	static Sound& get();
	void load();

	//�n���h�����擾
	static int handle(std::string name);

	//��񂾂��Đ�
	static void playone(std::string name);

	//���[�v�Đ�
	static void playloop(std::string name);

	//BGM�Đ� BGM�͏펞�����
	static void playbgm(std::string name);

	//BGM��~
	static void stopbgm();

	//�Đ����̉������ׂĒ�~
	static void stopall();

	//�w�肵�����̍Đ����~
	static void stopone(std::string name);

	//�{�����[�����Z�b�g
	static void setvolume(double master);

	//�Đ��Ԋu�t���[�����X�V
	static void update();

private:
	int bgmhandle = -1;
	double masterVolume = 1.0;
	std::unordered_map<std::string, SoundHandle> handlemap;

	Sound();
	void LoadToMap(std::string name);
	void LoadToMap(std::string name, double volume, int play_rate);
};