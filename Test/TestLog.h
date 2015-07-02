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
	string str = "E:\\ZTCPro\\Test\\";
	ZLog::getInstance().init(string(str + "log_test.txt").c_str(), "error");
	TRACE_ERR("�ɱ������%d����%s%c, %f�Ǻ�", 4, "����Ա", 'a', 3.14156);
}


#endif //ZTC_TEST_TESTLOG_H