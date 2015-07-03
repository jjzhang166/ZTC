#include "../include/ZCommonality.h"
#include "../include/ZMultiPlatformConfig.h"
#include <sstream>
#include <limits>
#include <ctype.h>
#include <cstdio>

BEGIN_ZTC_NAMESPACE
	int SplitBaseOnSingleChar(const string &desStr, const string &split, vector<string > &vStr)
	{
		string::size_type pos = 0;
		string::size_type numBegin = 0;
		string str = desStr;
		str += split.substr(0, 1);    //确保待分割的字符串末尾有分隔符
		while((pos = str.find_first_of(split, pos))!= string::npos )
		{
			if( pos!= 0 && string::npos == str.substr(pos - 1, 1).find_first_of(split))
			{
				vStr.push_back(str.substr(numBegin, pos - numBegin ));
			}
			++pos;
			numBegin = pos;
		}
		return vStr.size();
	}

	int SplitBaseOnGropChar(string str, string split, vector<string > &vStr)
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
		return vStr.size();
	}

	bool IsSplit(string str, vector<string >&vStr, int num)
	{
		if(0 == str.compare((*(vStr.end()-1)))) //	没有分割成子串
		{
			vStr.erase(vStr.end() -1); //删除末尾元素
			return false;
		}

		//字符串被分割了，删除vStr中源字符串，将分割后的字符串插入源字符串的位置
		vector<string >::iterator it = find(vStr.begin(), vStr.end(), str);
		int n = 0;
		if(it != vStr.end())
		{   
			n = vStr.size() - num;
			vStr.insert(it, vStr.end() - n, vStr.end());
			vStr.erase(vStr.end() - n, vStr.end());
			vector<string >::iterator it01 = find(vStr.begin(), vStr.end(), str);
			vStr.erase(it01);
			return true;
		}
		return false;
	}
	int SplitBaseOnMultiGropChar(string str, vector<string > split, vector<string >&vStr)
	{
		if(split.size() <= 0)
			return 0;

		//第一次分割
		if(0 == SplitBaseOnGropChar(str, *split.begin(), vStr))
			return 0;

		int num = 0;
		if(split.size() >= 2)
		{
			for(vector<string >::size_type i = 1; i<split.size(); ++i)
			{
				for(vector<string >::size_type j = 0; j<vStr.size(); ++j)
				{   
					num = vStr.size();
					SplitBaseOnGropChar(vStr[j], split[i], vStr);
					IsSplit(vStr[j], vStr, num);
				}
			}
		}
		return vStr.size();
	}
	

	double RoundOf(double num, int n)
	{
		if(n < 0)
			return num;
		if(n>=  5)
			n = 5;

		double unit = 0.5;
		int begin = 1;

		for(int i = 0; i<n ; ++i)
		{
			unit *= 0.1;
			begin *= 10;
		}

		return ((int)((num + unit)*begin))/(begin * 1.0);
	}

	/***数字转字符***/
	string ItoString(long double value, int precision)
	{  
		char DECIMAL_POINT = '.';
		int prec =  std::numeric_limits<long double>::digits10; 
		std::ostringstream out;
		out.precision(prec);//覆盖默认精度  
		out<<value;

		string str = out.str(); //从流中取出字符串 
		string::size_type n = str.find(DECIMAL_POINT);  
		string::size_type len = str.length();
		if ((n != string::npos) && (len > (n + precision))) 
		{   
			str[ n + precision] = '\0';//覆盖第一个多余的数  
			str.swap(string(str.c_str()));//删除nul之后的多余字符
			return str;
		} 
		else if((n != string::npos) && len <= (n + precision))
		{
			string st;
			int count = precision - len;
			//for(int i = 0; i<= (precision - len) ; ++i)   //死循环，数据类型不一致
			for(int i = 0; i<= count ; ++i)
				st.push_back('0');
			return (str + st);
		}
		else if(n == string::npos)// value是个整数
		{
			string st(".");
			for(int i = 0; i< precision - 1 ; ++i)
				st.push_back('0');
			return (str + st);
		}
		else
			return str;
	}
	string do_fraction(long double value, int decplaces)
	{
		std::ostringstream out; 
		char DECIMAL_POINT = '.';
		int prec =  std::numeric_limits<long double>::digits10; 
		out.precision(prec);//覆盖默认精度  
		out<<value;  
		string str = out.str(); //从流中取出字符串 
		size_t n = str.find(DECIMAL_POINT);  
		if ((n != string::npos) 
			&& (str.size()> n+decplaces)) //后面至少还有decplaces位吗？
		{   
			str[n+decplaces]='\0';//覆盖第一个多余的数  
		}  
		str.swap(string(str.c_str()));//删除nul之后的多余字符 
		return str;
	}

	/***------------------------字符个数统计----------------------------***/
	map<char, int> CalChar(char const *pCh)
	{
		int a[CHAR_COUNT] = {0};
		int num = strlen(pCh);
		for(int i = 0; i < num; ++i)
		{
			a[pCh[i]]++;
		}

		map<char, int> countMap;
		for(int j = 0; j<CHAR_COUNT; ++j)
		{
			if(a[j] != 0)
			{
				countMap.insert(map<char, int>::value_type(j, a[j]));
			}
		}

		return countMap;
	}

	string CharToHex(const char *pCh)
	{
		string temStr;
		//TODO: 20是个阀值
		char buf[20] = {'\0'};
		while(*pCh != '\0')
		{
			int tempInt = (int)*pCh++;
			sprintf(buf, "%x", tempInt);
			//itoa(tempInt, buf, 16);
			
			for(int i = 0; i<2; ++i)
				temStr += buf[i];
		}
		return temStr;
	}

	unsigned long HexToDec(const char* pCh)
	{
		const string strNum = "0123456789ABCDEFabcdef";
		string strSrc(pCh);
		if(string::npos != strSrc.find_first_not_of(strNum))
			return 0;
		int length = strlen(pCh);
		int i = 0;
		unsigned long sum = 0;
		unsigned  long base = 16;
		while(*pCh != '\0')
		{
			int tempInt = (int)*pCh++;
			unsigned long tempBase = 1;
			for(int j = 0; j < length - i - 1; ++j)
			{
				tempBase *= base; 
			}

			if(tempInt >= 48 && tempInt <= 57) // 0~9
			{
				sum += (tempInt - 48) * tempBase;
			}
			if(tempInt >= 65 && tempInt <= 70) //a~f
			{
				sum += ((tempInt - 65) + 10) * tempBase;
			}
			if(tempInt >= 97 && tempInt <= 102) //A~F
			{
				sum += ((tempInt - 97) + 10) * tempBase;
			}
			++i;
		}
		return sum;
	}

	bool multi_to_wide(const std::string& multi, std::wstring& unicode)
	{
		if(multi.empty())
			return true;
#ifdef _MSC_VER
		int needLen = MultiByteToWideChar(CP_ACP, 0, multi.c_str(), multi.length(), NULL, 0);
		if(needLen < 1)
			return false;
		unicode.resize(needLen);
		int convertLen = MultiByteToWideChar(CP_ACP, 0, multi.c_str(), multi.length(), (wchar_t*)unicode.c_str(), unicode.length());
		if(convertLen != needLen)
			return false;
		return true;
#else
		iconv_t conv = iconv_open("WCHAR_T", "ASCII");
		unicode.resize(multi.length());
		char* from = (char*)multi.c_str();
		size_t fromLen = multi.length();
		char* to = (char*)unicode.c_str();
		size_t toLen = unicode.length() * sizeof(wchar_t);
		if(iconv(conv, &from, &fromLen, &to, &toLen) == (size_t)-1)
		{
			iconv_close(conv);
			unicode.clear();
			return false;
		}
		else
		{
			iconv_close(conv);
			unicode.resize(unicode.length() - toLen/sizeof(wchar_t));
			return true;
		}
#endif
	}

	bool wide_to_multi(const std::wstring& unicode, std::string& multi)
	{
		if(unicode.empty())
			return true;
#ifdef _MSC_VER
		int needLen = WideCharToMultiByte(CP_ACP, 0, unicode.c_str(), unicode.size(), NULL, 0, NULL, NULL);
		if(needLen < 1)
			return false;
		multi.resize(needLen);
		int convertLen = WideCharToMultiByte(CP_ACP, 0, unicode.c_str(), unicode.length(), (char*)multi.c_str(), multi.length(), NULL, NULL);
		if(convertLen != needLen)
			return false;
		return true;
#else
		iconv_t conv = iconv_open("ASCII", "WCHAR_T");
		multi.resize(unicode.length() * 4);
		char* from = (char*)unicode.c_str();
		size_t fromLen = unicode.length() * sizeof(wchar_t);
		char* to = (char*)multi.c_str();
		size_t toLen = multi.length();
		if(iconv(conv, &from, &fromLen, &to, &toLen) == (size_t)-1)
		{
			iconv_close(conv);
			multi.clear();
			return false;
		}
		else
		{
			iconv_close(conv);
			multi.resize(multi.length() - toLen);
			return true;
		}
#endif
	}
	
	bool unicode_to_utf8(const std::wstring& unicode, std::string& utf8)
	{
		if(unicode.empty())
			return true;
#ifdef _MSC_VER
		int needLen = WideCharToMultiByte(CP_UTF8, 0, unicode.c_str(), unicode.length(), NULL, 0, NULL, NULL);
		if(needLen < 1)
			return false;
		utf8.resize(needLen);
		int convertLen = WideCharToMultiByte(CP_UTF8, 0, unicode.c_str(), unicode.length(), (char*)utf8.c_str(), utf8.length(), NULL, NULL);
		if(convertLen != needLen)
			return false;
		return true;
#else
		iconv_t conv = iconv_open("UTF-8", "WCHAR_T");
		utf8.resize(unicode.length() * 6);
		char* from = (char*)unicode.c_str();
		size_t fromLen = unicode.length() * sizeof(wchar_t);
		char* to = (char*)utf8.c_str();
		size_t toLen = utf8.length();
		if(iconv(conv, &from, &fromLen, &to, &toLen) == (size_t)-1)
		{
			iconv_close(conv);
			utf8.clear();
			return false;
		}
		else
		{
			iconv_close(conv);
			utf8.resize(utf8.length() - toLen);
			return true;
		}
#endif
	}

	bool utf8_to_unicode(const std::string& utf8, std::wstring& unicode)
	{
		if(utf8.empty())
			return true;
#ifdef _MSC_VER
		int needLen = MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), utf8.length(), NULL, 0);
		if(needLen < 1)
			return false;
		unicode.resize(needLen);
		int convertLen = MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), utf8.length(), (wchar_t*)unicode.c_str(), unicode.length());
		if(convertLen != needLen)
			return false;
		return true;
#else
		iconv_t conv = iconv_open("WCHAR_T", "UTF-8");
		unicode.resize(utf8.length());
		char* from = (char*)utf8.c_str();
		size_t fromLen = utf8.length();
		char* to = (char*)unicode.c_str();
		size_t toLen = unicode.length() * sizeof(wchar_t);
		if(iconv(conv, &from, &fromLen, &to, &toLen) == (size_t)-1)
		{
			iconv_close(conv);
			unicode.clear();
			return false;
		}
		else
		{
			iconv_close(conv);
			unicode.resize(unicode.length() - toLen/sizeof(wchar_t));
			return true;
		}
#endif
	}
	
END_ZTC_NAMESPACE