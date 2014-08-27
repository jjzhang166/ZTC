#ifndef ZTCTEST_INCLUDE_ZLOG_H
#define ZTCTEST_INCLUDE_ZLOG_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using std::endl;
using std::ifstream;
using std::ofstream;
using std::string;

namespace ZTC
{
	class ZLog
	{
	public:

		enum DebugLevel
		{
			Waring = 0,
			Error
		};

		ZLog(const char* pFile, std::ios::openmode mode = std::ios::out);
		ZLog(const string& fileName, std::ios::openmode mode = std::ios::out);
		~ZLog();
		/******
		* �жϵ�ǰ�����Ƿ���ã��Ƿ���Զ��ļ�����д������
		*/
		bool IsValid();
		/******
		* ע�⣬��Log������ȷ����ͬһ�������ڲ�Ҫ��ZLog���캯������ͬ���ļ���
		* �⽫���¶��ZLogͬʱ��һ���ļ�д���������Ǵ���ģ����磺
		*  {
		*		ZLog("G:\\Dev\\PublicDemo\\ZTC\\ZTCTest\\Test\\log_test.txt", std::ios::app).Log("�ɹ��ˣ�");
		*		ZLog("G:\\Dev\\PublicDemo\\ZTC\\ZTCTest\\Test\\log_test.txt", std::ios::app).Log("�ɱ������%d����%s%c, %f", 4, "����Ա", 'a', 3.14156);
		*	}
		* ��Ӧ����ô��,��ȷ�÷�NO1��
		*  ZLog log("G:\\Dev\\PublicDemo\\ZTC\\ZTCTest\\Test\\log_test.txt");
		*  log.Log("����");
		*  log.Log("�Ǻ�");
		* ��Ӧ����ô��,��ȷ�÷�NO2��
		*  {
		*		ZLog("G:\\Dev\\PublicDemo\\ZTC\\ZTCTest\\Test\\log_test.txt", std::ios::app).Log("�ɹ��ˣ�");
		*   }
		*  {
		*		ZLog("G:\\Dev\\PublicDemo\\ZTC\\ZTCTest\\Test\\log_test.txt", std::ios::app).Log("�ɱ������%d����%s%c, %f", 4, "����Ա", 'a', 3.14156);
		*   }
		*
		*	���� ֱ���� Z_LOG_NO_PARAM��Z_LOG_PARAM��Z_LOG_MODE_PARAM��
		**/
		void Log(const string& strText);
		void Log(const char* pText, ...);

		void setLevel(DebugLevel level);


	private:
		ZLog(const ZLog&);
		ZLog& operator=(const ZLog&);

		int getCharNum(const char* pCh);
		//bool isZLogOpen(const char* pFile);

		void levelConvertStr(DebugLevel level, char *pStr);

		//--@�����С���ȶ���
		enum NumDefine{
			MAX_NUM = 1024,
			MIDDLE_NUM = 512,
			MIN_NUM = 100,
			SMAIL_NUM = 30
		};

		ofstream m_ofstream;
		DebugLevel m_debugLevel;
	};

	#define Z_LOG_NO_PARAM(FileName, StrText) {ZLog(FileName).Log(StrText);}
	#define Z_LOG_PARAM(FileName, StrTextFormat, ...) {ZLog(FileName, std::ios::app).Log(StrTextFormat, __VA_ARGS__);}
	#define Z_LOG_MODE_PARAM(FileName, Mode, StrTextFormat, ...) {ZLog(FileName, Mode).Log(StrTextFormat, __VA_ARGS__);}

}
#endif //ZTCTEST_INCLUDE_ZLOG_H