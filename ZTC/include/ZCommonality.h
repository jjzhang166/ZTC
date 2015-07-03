#ifndef ZTC_ZCOMMONALITY_H
#define ZTC_ZCOMMONALITY_H

#include "ZStdf.h"
#include <stdlib.h>
#include <sstream>
#include <limits>

#include "ZBase.h"
#include "ZMacroDefine.h"

BEGIN_ZTC_NAMESPACE
/***************** 字符串分割函数
* 函数： int SplitFromSingleChar(const string &desStr, const string &split, vector<string > &vStr);
* 功能： 分割desStr字符串
* 参数说明： desStr：需要分割字符串； split:分割的字符串字符； vStr：分割后的字符串
* 返回值：函数执行成功，返回分割得到的字符串的个数, 如果失败，返回 0 。
* 例如：str = "my name is<hello,word> : test[string](string.)world";
*       split = " ,;:!?.<>[]()'";  //split中的每一个字符都是分隔符
*****/
ZTC_API int SplitBaseOnSingleChar(const string &desStr, const string &split, vector<string > &vStr);

/***************** 字符串分割函数
* 函数：int SplitFromGropChar(string str, string split, vector<string > &vStr);
* 功能：分割str字符串
* 参数说明： str：需要分割字符串； split:分割的字符串字符； vStr：分割后的字符串
* 返回值：函数执行成功，返回分割得到的字符串的个数 ，如果失败，返回 0 。
* 例如：str = "my##eedsfa##";
*       split = "##"; //split整个是分隔符 
*
*****/
ZTC_API int SplitBaseOnGropChar(string str, string split, vector<string > &vStr);

/*****************
* 函数：int SplitFromMultiGropChar(string str, vector<string > split, vector<string >&vStr);
* 功能：用分割符集合分割str字符串
* 参数说明：str：需要分割字符串； split:分割的字符串字符集合； vStr：分割后的字符串
* 返回值：函数执行成功，返回分割得到的字符串的个数 ，如果失败，返回 0 。
* 例如：str = "my##eedsfa##";
*       split[0] = "##"; //split[0]整个是分隔符 
*       split[1] = "||"; //split[1]整个是分隔符 
*       split[2] = ","; //split[2]整个是分隔符 
*
*****/
ZTC_API int SplitBaseOnMultiGropChar(string str, vector<string > split, vector<string >&vStr);

/***************** 四舍五入
* 函数：double RoundOff(double num, int n = 2);
* 功能：四舍五入
* 参数说明：num：待四舍五入的值； n:要求的精度, 默认值为2(即小数点后两位)； 
* 返回值：函数执行成功，一个double值 ，如果失败，返回 初始值（即num） 。
* 说明：该函数最多只能返回一个精确到小数点后5位的值(即double的精确值),若n的价值小于0，返回值为0；
*       若n的值大于5，函数将默认n的值为5.
*****/
ZTC_API double RoundOf(double num, int n = 2);

/***数字转字符***/
ZTC_API string ItoString(long double value, int precision = 3);
ZTC_API string do_fraction(long double value, int decplaces = 3);

/*********字符个数统计
***/
ZTC_CLASS	map<char, int> CalChar(char const *pCh);

/********把字符转换成16进制
*  返回值：16进制字符串
*/
ZTC_API string CharToHex(const char *pCh);

/********把16进制转换成10进制
*/
ZTC_API unsigned long HexToDec(const char* pCh);

ZTC_API bool multi_to_wide(const std::string& multi, std::wstring& unicode);
ZTC_API bool wide_to_multi(const std::wstring& unicode, std::string& multi);

ZTC_API bool utf8_to_unicode(const std::string& utf8, std::wstring& unicode);
ZTC_API bool unicode_to_utf8(const std::wstring& unicode, std::string& utf8);

END_ZTC_NAMESPACE
#endif // ZTC_ZCOMMONALITY_H