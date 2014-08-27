#include "ReadMp3Information.h"
#include <iostream>
#include <string>
#include "ZCommonality.h"

using std::cout;
using std::endl;
using std::string;

using namespace ZTC;

const string mStrErrorFileName = "\//:*?<>|";
const char mChErrorFileName = '"';

ReadMP3Information::ReadMP3Information()
{
}

ReadMP3Information::ReadMP3Information(char *pFileName)
{
	if(m_mp3File)
		m_mp3File.close();
	m_mp3File.open(pFileName, std::ios::binary | std::ios::in);
}

ReadMP3Information::~ReadMP3Information()
{
	if(m_mp3File)
		m_mp3File.close();
}

void ReadMP3Information::close()
{
	m_mp3File.close();
}

bool ReadMP3Information::readInformation(MP3Info &mp3Info)
{
	if(!m_mp3File || !m_mp3File.is_open())
		return false;

	char strBuf[129] = {'0'};
	m_mp3File.seekg(-128, std::ios::end);
	m_mp3File.read(strBuf, 128);

	charToMp3Info(strBuf, mp3Info);
	return true;
}

bool ReadMP3Information::charToMp3Info(const char* pFileText, MP3Info &mp3Info)
{
	if(pFileText == NULL)
		return false;
	memset(&mp3Info, 0, sizeof(MP3Info));
	memcpy(&(mp3Info.tag), pFileText, 3);
	memcpy(&(mp3Info.name), &pFileText[3], 30);
	memcpy(&(mp3Info.singer), &pFileText[33], 30);
	memcpy(&(mp3Info.aname), &pFileText[63], 30);
	memcpy(&(mp3Info.year), &pFileText[93], 4);
	memcpy(&(mp3Info.content), &pFileText[97], 28);
	memcpy(&(mp3Info.other), &pFileText[125], 3);
	return true;
}

bool ReadMP3Information::readInformation(const char *pFileName, MP3Info &mp3Info)
{
	if(m_mp3File)
		m_mp3File.close();
	m_mp3File.open(pFileName, std::ios::binary | std::ios::in);

	if(!m_mp3File || !m_mp3File.is_open())
		return false;

	//m_mp3File.seekg(std::ios::beg, 0);

	char strBuf[129] = {'0'};
	m_mp3File.seekg(-128, std::ios::end);
	m_mp3File.read(strBuf, 128);

	charToMp3Info(strBuf, mp3Info);

	m_mp3File.close();
	return true;
}

void ReadMP3Information::renameDirMp3File(const char *pDir)
{
	path dir(pDir);
	recursiveDir(dir);
}

void ReadMP3Information::recursiveDir(const path& dir)
{
	directory_iterator end;
	for(directory_iterator pos(dir); pos != end; ++pos)
	{
		if(is_directory(*pos))
		{
			recursiveDir(*pos);  //是一个子目录，继续迭代
		}
		else
		{
			//是一个文件，判断是否是MP3文件
			string str = pos->path().string();
			if(isMp3File(str.c_str()))
			{
				 vector<string> veStr;
				 SplitBaseOnSingleChar(str, "/\\", veStr);

				 string convertFileName;
				 for(vector<string>::iterator iter = veStr.begin(); iter != veStr.end(); ++iter)
				 {
					 convertFileName += *iter;
					 if(iter != veStr.end() - 1)
						 convertFileName += "/";
				 }
				 MP3Info info;
				 readInformation(convertFileName.c_str(), info);

				 string dirPath;
				 for(vector<string>::iterator iter = veStr.begin(); iter != veStr.end() - 1; ++iter)
				 {
					 dirPath += *iter + "/";
				 }
				 
				 string newFileName;
				 newFileName += info.name; //歌曲名
				 newFileName += "--";
				 newFileName += info.singer; 

				 if(info.aname != "")
				 {
					 newFileName += "(";
					 newFileName += info.aname; //专辑名
					 newFileName += ")";
				 }

				 if(isErrorFileName(newFileName.c_str()))
				 {
					 cout<<"文件： "<<str<<" 无法被程序从命名，请手动命名！"<<endl;
				 }
				 else
				 {
					 newFileName += ".mp3";
					 path filePath(pos->path());
					 rename(filePath, dirPath + newFileName);
				 }
			}
		}
	}
}

bool ReadMP3Information::isMp3File(const char* pFileName)
{
	if(pFileName == NULL)
		return false;

	vector<string> veStr;
	SplitBaseOnSingleChar(pFileName, "/\\", veStr);

	string strFileName = veStr.back();
	unsigned int index = strFileName.find(".", 0);
	string fileType = strFileName.substr(index);
	if(fileType == ".mp3" 
	  || fileType == ".Mp3"
	  || fileType == ".mP3"
	  || fileType == ".MP3")
		return true;
	else 
		return false;
}

bool ReadMP3Information::isErrorFileName(const char *pFileName)
{
	//错误文件名可能包括的字符
	string strErrorFileName(mStrErrorFileName);
	strErrorFileName += mChErrorFileName;

	string newFileName(pFileName);

	//错误的文件名
	if(string::npos != newFileName.find_first_of(strErrorFileName.c_str()))
	{
		return true;
	}
	return false;
}
