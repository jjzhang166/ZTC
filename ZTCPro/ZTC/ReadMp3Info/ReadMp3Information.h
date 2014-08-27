/*
* Copyright (c) 2013 ZZ
* All rights reserved.
* 
* File Name       : ReadMp3Infomation.h
* File Identifier :
* Abstract        :
* 
* Current Version : 1.0
* Author          : ZZ
* Completion Date : 2014.5.25 21:48:45
*
* Replace Version : 
* Original Author :
* Completion Date : 2014.5.25 21:48:45
*/

//
//MP3歌曲的基本信息存在了MP3文件的最后128个字节里，
//其结构是：
//1－3 TAG 
//4－33 歌曲名(Take Me To Your Heart )
//34－63 歌手名(Michael Learns to Rock)
//64－93 专辑名(Take Me to Your Heart)
//94－97 年(2004）
//98－125 备注 （http://www.uptu.com）
//126　保留位，这时为0，则说明有音轨，下一位就是音轨
//127　保留位，为音轨（第几首歌）（OC）
//128 保留位 （风格）（66）
//请写出一个读取MP3歌曲信息的函数,将信息存放在结构成员变量中。

#ifndef READMP3INFOMATION_INCLUDE_READMP3INFOMATION_H
#define READMP3INFOMATION_INCLUDE_READMP3INFOMATION_H

#include <fstream>
#include <boost/filesystem.hpp>

using std::ifstream;
using namespace boost::filesystem;

struct MP3Info
{
	char tag[3];
	char name[31]; //歌曲名
	char singer[31]; //歌手名
	char aname[31]; //专辑名
	char year[5]; //年份
	char content[29]; //备注
	char other[4];
};

class ReadMP3Information
{
public:
	ReadMP3Information();
	ReadMP3Information(char *pFileName);
	~ReadMP3Information();

	bool readInformation(MP3Info &mp3Info);
	bool readInformation(const char *pFileName, MP3Info &mp3Info);

	void renameDirMp3File(const char *pDir); //把目录下面的所有MP3文件按MP3文件信息中的歌名和歌手名进行命名
	void close();

private:

	bool charToMp3Info(const char* pFileText, MP3Info &mp3Info);
	void recursiveDir(const path& dir);
	bool isMp3File(const char* pFileName);
	bool isErrorFileName(const char *pFileName);

	ifstream m_mp3File;
};


#endif //READMP3INFOMATION_INCLUDE_READMP3INFOMATION_H



