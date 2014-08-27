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
		* 判断当前对象是否可用（是否可以对文件进行写操作）
		*/
		bool IsValid();
		/******
		* 注意，用Log函数请确保在同一作用域内不要用ZLog构造函数打开相同的文件，
		* 这将导致多个ZLog同时对一个文件写操作，这是错误的，例如：
		*  {
		*		ZLog("G:\\Dev\\PublicDemo\\ZTC\\ZTCTest\\Test\\log_test.txt", std::ios::app).Log("成功了！");
		*		ZLog("G:\\Dev\\PublicDemo\\ZTC\\ZTCTest\\Test\\log_test.txt", std::ios::app).Log("可变参数！%d我是%s%c, %f", 4, "程序员", 'a', 3.14156);
		*	}
		* 你应该这么用,正确用法NO1：
		*  ZLog log("G:\\Dev\\PublicDemo\\ZTC\\ZTCTest\\Test\\log_test.txt");
		*  log.Log("哈哈");
		*  log.Log("呵呵");
		* 你应该这么用,正确用法NO2：
		*  {
		*		ZLog("G:\\Dev\\PublicDemo\\ZTC\\ZTCTest\\Test\\log_test.txt", std::ios::app).Log("成功了！");
		*   }
		*  {
		*		ZLog("G:\\Dev\\PublicDemo\\ZTC\\ZTCTest\\Test\\log_test.txt", std::ios::app).Log("可变参数！%d我是%s%c, %f", 4, "程序员", 'a', 3.14156);
		*   }
		*
		*	或者 直接用 Z_LOG_NO_PARAM，Z_LOG_PARAM，Z_LOG_MODE_PARAM宏
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

		//--@数组大小长度定义
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