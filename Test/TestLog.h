#ifndef ZTC_TEST_TESTLOG_H
#define ZTC_TEST_TESTLOG_H

#include <iostream>
#include <string>
#include "../ZTC/include/ZStdf.h"
#include "../ZTC/include/ZCommonality.h"
#include "../ZTC/include/ZLog.h"

using std::string;
using namespace ZTC;

void TestLog()
{
	string str = ".\\";
	int i = ZLog::getInstance().init(string(str + "log_test.txt").c_str(), "error");
	ZLOG_LOG(LOG_ERROR, "1111可变参数！%d我是%s%c, %f呵呵\r\n", 4, "程序员", 'a', 3.14156);
}

#endif //ZTC_TEST_TESTLOG_H