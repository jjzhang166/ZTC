#include "../include/ZFormatData.h"
#include <string.h>
#include <iostream>

const int a[2] = {2,3};

ZFormatData::ZFormatData(const char *pReadFileName, const char * pWriteFileName)
{
	m_readFile.open(pReadFileName);
	m_writeFile.open(pWriteFileName, ios::binary | ios::app);
}

ZFormatData::~ZFormatData()
{
	m_writeFile.close();
	m_readFile.close();
}

bool ZFormatData::isVaild()
{
	if(!m_readFile || !m_writeFile || !m_readFile.is_open() || !m_writeFile.is_open())
		return false;
	return true;
}

bool ZFormatData::splitBaseOnGropChar(string str, string split, vector<string > &vStr)
{
	string::size_type pos = 0;
	string::size_type numBegin = 0;
	string::size_type length = str.length(); //str的实际长度
	str += split;    //确保待分割的字符串末尾有分隔符
	while((pos = str.find_first_of(split, pos))!= string::npos )
	{
		if(pos != length + 1  && 0 == (str.substr(pos, split.length())).compare(split)) 
		{
			if(!(str.substr(numBegin, pos - numBegin)).empty())
			{
				vStr.push_back(str.substr(numBegin, pos - numBegin ));
			}

			pos += split.length();
			numBegin = pos;
		}
		else
		{
			++pos ;
		}
	}
	if(vStr.size() >= 2)
		return true;
	else
		return false;
}

void ZFormatData::trim( string &str)
{
	if(str.empty())
		return;

	if(str.length() == 1 && iswspace(str[0]))
	{
		str = "";
		return;
	}

	string::iterator c;
	// Erase whitespace before the string
	for (c = str.begin(); c != str.end() && iswspace(*c++););
		str.erase(str.begin(), --c);

	// Erase whitespace after the string
	for (c = str.end(); c != str.begin() && iswspace(*--c););
		str.erase(++c, str.end());
}

int zh(string s)
{
	int i,m,temp=0,n;
	m = s.length();//十六进制是按字符串传进来的，所以要获得他的长度
	for(i=0;i<m;i++)
	{
		if(s[i]>='A'&&s[i]<='F')//十六进制还要判断他是不是在A-F或者a-f之间a=10。。
			n=s[i]-'A'+10;
		else if(s[i]>='a'&&s[i]<='f')
			n=s[i]-'a'+10;
		else 
			n=s[i]-'0';
		temp=temp*16+n;
	}
	return temp;
}

void ZFormatData::formatData()
{
	if(!isVaild())
	{
		cout<<"格式化失败"<<endl;
	}

	const int maxSize = 100;
	char data[maxSize];
	string originalData; //原始数据
	string formatedData; //原始数据被格式化后的数据
	bool isFirst = true;
	while(!m_readFile.eof())
	{
		memset(data, 0, maxSize);
		m_readFile.read(data, maxSize - 1);
		originalData += string(data);
		vector<string> veStr;
		splitBaseOnGropChar(originalData, "03 FC", veStr);
		int size = veStr.size();
		if(size <= 1 && isFirst && originalData.length() >= 30)
		{
			originalData = "";
			isFirst = false;
			continue;
		}
		if(size <= 1)
			continue;
		originalData = "";
		string str2;
		for(vector<string>::iterator iter = veStr.begin(); iter != veStr.end(); ++iter)
		{
			string tmpStr = (*iter);
			if(tmpStr.length() >= 30)
				continue;
			str2 += tmpStr;

			vector <string> veStr2;
			bool bo = splitBaseOnGropChar(str2, "FC 03", veStr2);
			if(bo)
			{
				trim(veStr2[0]);
				//m_writeFile<<veStr2[0].c_str()<<"\r\n";
				vector <string> veStr3;
				splitBaseOnGropChar(veStr2[0], " ", veStr3);
				short x = 0;
				short y = 0;
				short z = 0;
				string numberStr = "";

				for(vector<string>::size_type i = 0; i < veStr3.size(); ++i)
				{
					if(i >= 6)
						break;
					if(i%2 != 0)
					{
						string tmp = veStr3[i];
						tmp.append(numberStr.c_str());
						numberStr = tmp;
						if(i <= 1)
							x = zh(numberStr);//x = atof(numberStr.c_str());
						else if(i > 1 && i <= 3)
							y = zh(numberStr);//y = atof(numberStr.c_str());
						else if(i >= 4 && i <= 5)
							z = zh(numberStr);//z = atof(numberStr.c_str());
					}
					else
					{
						numberStr = veStr3[i];
					}
				}
				char text[maxSize];
				memset(text, 0, maxSize);
				sprintf(text, "%d , %d , %d\r\n", x, y, z);
				m_writeFile<<text;

				//m_writeFile<<"\r\n";

				if(veStr2[1].length() == 1 && iswspace(veStr2[1][0]))
					str2 = "";
				else
					str2 = veStr2[1];
			}
		}
		originalData = str2;
	}
	cout <<"格式化成功!"<<endl;
}

void ZFormatData::formatData1()
{
	if(!isVaild())
	{
		cout<<"格式化失败"<<endl;
	}

	const int maxSize = 100;
	char data[maxSize];
	string originalData; //原始数据
	string formatedData; //原始数据被格式化后的数据
	bool isFirst = true;
	while(!m_readFile.eof())
	{
		memset(data, 0, maxSize);
		m_readFile.read(data, maxSize - 1);
		originalData += string(data);
		vector<string> veStr;
		splitBaseOnGropChar(originalData, "03 FC", veStr);
		int size = veStr.size();
		if(size <= 1 && isFirst && originalData.length() >= 30)
		{
			originalData = "";
			isFirst = false;
			continue;
		}
		if(size <= 1)
			continue;
		originalData = "";
		string str2;
		for(vector<string>::iterator iter = veStr.begin(); iter != veStr.end(); ++iter)
		{
			string tmpStr = (*iter);
			if(tmpStr.length() >= 30)
				continue;
			str2 += tmpStr;

			vector <string> veStr2;
			bool bo = splitBaseOnGropChar(str2, "FC 03", veStr2);
			if(bo)
			{
				trim(veStr2[0]);
				//m_writeFile<<veStr2[0].c_str()<<"\r\n";
				vector <string> veStr3;
				splitBaseOnGropChar(veStr2[0], " ", veStr3);
				short x = 0;
				short y = 0;
				short z = 0;
				string numberStr = "";

				for(vector<string>::size_type i = 0; i < veStr3.size(); ++i)
				{
					if(i >= 6)
						break;
					if(i%2 != 0)
					{
						/*string tmp = veStr3[i];
						tmp.append(numberStr.c_str());
						numberStr = tmp;*/
						numberStr.append(veStr3[i].c_str());
						memcpy(&x, numberStr.c_str(), numberStr.length() - 1);
						if(i <= 1)
							x = zh(numberStr);//x = atof(numberStr.c_str());
						else if(i > 1 && i <= 3)
							y = zh(numberStr);//y = atof(numberStr.c_str());
						else if(i >= 4 && i <= 5)
							z = zh(numberStr);//z = atof(numberStr.c_str());
					}
					else
					{
						numberStr = veStr3[i];
					}
				}
				char text[maxSize];
				memset(text, 0, maxSize);
				sprintf(text, "(%d , %d , %d)\r\n", x, y, z);
				m_writeFile<<text;

				//m_writeFile<<"\r\n";

				if(veStr2[1].length() == 1 && iswspace(veStr2[1][0]))
					str2 = "";
				else
					str2 = veStr2[1];
			}
		}
		originalData = str2;
	}
	cout <<"格式化成功!"<<endl;
}