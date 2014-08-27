#include "../include/ZLog.h"
#include <cstdarg>
#include <cstdio>

namespace ZTC
{
	ZLog::ZLog(const char* pFile, std::ios::openmode mode) : m_debugLevel(Error)
	{
		m_ofstream.open(pFile, mode);
	}

	ZLog::ZLog(const string& fileName, std::ios::openmode mode)
	{
		m_ofstream.open(fileName.c_str(), mode);
	}

	ZLog::~ZLog()
	{
		m_ofstream.close();
	}

	bool ZLog::IsValid()
	{
		if(!m_ofstream || !m_ofstream.is_open())
			return false;
		return true;
	}

	void ZLog::Log(const string& strText)
	{
		Log(strText.c_str());
	}


	void ZLog::Log(const char* pText, ...)
	{
		va_list ap;                          
		va_start(ap, pText);        // 初始化ap，让它指向第一个变参n之后的参数

		char textBuff[MAX_NUM] = {'\0'};
		vsprintf(textBuff, pText, ap);

		/*
		int i = 0;
		for(const char* pCh = pText; *pCh; ++pCh)
		{
			if(*pCh != '%')
			{
				textBuff[i] = *pCh;
				++i;
				continue;
			}

			char numBuff[SMAIL_NUM] = {'\0'};
			switch(*++pCh)
			{
			case 'd':{
						 int ival = va_arg(ap, int);
						 //itoa(ival, numBuff, 10);
						 sprintf(numBuff, "%d", ival);
					 }break;
			case 'c':{
						char chValue = va_arg(ap, char);
						textBuff[i] = chValue;
						++i;
					 }break;
			case 's':{
						char *pChText = va_arg(ap, char*);
						strcat(textBuff + i, pChText);
						i += getCharNum(pChText);
					 }break;
			case 'f':{
						double value = va_arg(ap, double);
						sprintf(numBuff, "%f", value);
					 }break;
			case '%':
					{
						char chValue = va_arg(ap, char);
						textBuff[i] = chValue;
						++i;
					}break;
			case 'o':
				{
					
				}break;
			case 'x':
				{}break;
			case 'X':
				{}break;
			default:
				break;
			}
			
			strcat(textBuff + i, numBuff);
			i += getCharNum(numBuff);
		}
		*/
#ifdef DEBUG_PUTOUT_FILE_LINE
	m_ofstream<<__FILE__<<" , "<<__LINE__<<" ";
#endif //DEBUG_PUTOUT_FILE_LINE
		char level[100] = {'\0'};
		levelConvertStr(m_debugLevel, level);
		m_ofstream<<level<<" : ";
		m_ofstream<<textBuff;
	}

	int ZLog::getCharNum(const char* pCh)
	{
		int i = 0;
		while(*pCh++)
			++i;
		return i;
	}

	void ZLog::setLevel(DebugLevel level)
	{
		m_debugLevel = level;
	}

	void ZLog::levelConvertStr(DebugLevel level, char *pStr)
	{
		switch(level)
		{
		case Waring:
			{
				memcpy(pStr, "Waring", 7);
			}break;
		case Error:
			{
				memcpy(pStr, "Error", 6);
			}break;
		default:
			break;
		}
	}
}