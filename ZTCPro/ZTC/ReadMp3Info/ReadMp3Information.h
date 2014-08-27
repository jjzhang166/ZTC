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
//MP3�����Ļ�����Ϣ������MP3�ļ������128���ֽ��
//��ṹ�ǣ�
//1��3 TAG 
//4��33 ������(Take Me To Your Heart )
//34��63 ������(Michael Learns to Rock)
//64��93 ר����(Take Me to Your Heart)
//94��97 ��(2004��
//98��125 ��ע ��http://www.uptu.com��
//126������λ����ʱΪ0����˵�������죬��һλ��������
//127������λ��Ϊ���죨�ڼ��׸裩��OC��
//128 ����λ ����񣩣�66��
//��д��һ����ȡMP3������Ϣ�ĺ���,����Ϣ����ڽṹ��Ա�����С�

#ifndef READMP3INFOMATION_INCLUDE_READMP3INFOMATION_H
#define READMP3INFOMATION_INCLUDE_READMP3INFOMATION_H

#include <fstream>
#include <boost/filesystem.hpp>

using std::ifstream;
using namespace boost::filesystem;

struct MP3Info
{
	char tag[3];
	char name[31]; //������
	char singer[31]; //������
	char aname[31]; //ר����
	char year[5]; //���
	char content[29]; //��ע
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

	void renameDirMp3File(const char *pDir); //��Ŀ¼���������MP3�ļ���MP3�ļ���Ϣ�еĸ����͸�������������
	void close();

private:

	bool charToMp3Info(const char* pFileText, MP3Info &mp3Info);
	void recursiveDir(const path& dir);
	bool isMp3File(const char* pFileName);
	bool isErrorFileName(const char *pFileName);

	ifstream m_mp3File;
};


#endif //READMP3INFOMATION_INCLUDE_READMP3INFOMATION_H



