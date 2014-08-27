#ifndef ZTC_TEST_TESTLOG_H
#define ZTC_TEST_TESTLOG_H

#include <iostream>
#include <string>
#include "../ZTC/include/ZStdf.h"
#include "../ZTC/include/ZCommonality.h"
#include "../ZTC/include/ZLog.h"

using std::string;

void TestLog()
{
	string str = "F:\\Dev\\ZTCPro\\ZTCPro\\Test\\";
	Z_LOG_NO_PARAM(string(str + "log_test.txt").c_str(), "Oh No!");
	Z_LOG_PARAM(string(str + "log_test.txt").c_str(), "\n%doooo\n", 87);
	{
		ZLog log("log_test.txt", std::ios::app);
		if(!log.IsValid())
			cout<<"文件路径错误"<<endl;
		log.Log("我是中国人！\n");
		log.Log("不是中国人！\n");
	}
	{
		ZLog(string(str + "log_test.txt"), std::ios::app).Log("成功了！");
	}
	ZLog(string(str + "log_test.txt"), std::ios::app).Log("可变参数！%d我是%s%c, %f呵呵", 4, "程序员", 'a', 3.14156);
	
}


#endif //ZTC_TEST_TESTLOG_H