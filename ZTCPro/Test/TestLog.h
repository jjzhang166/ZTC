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
			cout<<"�ļ�·������"<<endl;
		log.Log("�����й��ˣ�\n");
		log.Log("�����й��ˣ�\n");
	}
	{
		ZLog(string(str + "log_test.txt"), std::ios::app).Log("�ɹ��ˣ�");
	}
	ZLog(string(str + "log_test.txt"), std::ios::app).Log("�ɱ������%d����%s%c, %f�Ǻ�", 4, "����Ա", 'a', 3.14156);
	
}


#endif //ZTC_TEST_TESTLOG_H