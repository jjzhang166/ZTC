#include "../include/ZCommonality.h"
#include <sstream>
#include <limits>
#include <ctype.h>
#include <cstdio>

namespace ZTC
{
	int SplitBaseOnSingleChar(const string &desStr, const string &split, vector<string > &vStr)
	{
		string::size_type pos = 0;
		string::size_type numBegin = 0;
		string str = desStr;
		str += split.substr(0, 1);    //ȷ�����ָ���ַ���ĩβ�зָ���
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
		string::size_type length = str.length(); //str��ʵ�ʳ���
		str += split;    //ȷ�����ָ���ַ���ĩβ�зָ���
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

	int SplitBaseOnMultiGropChar(string str, vector<string > split, vector<string >&vStr)
	{
		if(split.size() <= 0)
			return 0;

		//��һ�ηָ�
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
	bool IsSplit(string str, vector<string >&vStr, int num)
	{
		if(0 == str.compare((*(vStr.end()-1)))) //	û�зָ���Ӵ�
		{
			vStr.erase(vStr.end() -1); //ɾ��ĩβԪ��
			return false;
		}

		//�ַ������ָ��ˣ�ɾ��vStr��Դ�ַ��������ָ����ַ�������Դ�ַ�����λ��
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

	/***����ת�ַ�***/
	string ItoString(long double value, int precision)
	{  
		char DECIMAL_POINT = '.';
		int prec =  std::numeric_limits<long double>::digits10; 
		std::ostringstream out;
		out.precision(prec);//����Ĭ�Ͼ���  
		out<<value;

		string str = out.str(); //������ȡ���ַ��� 
		string::size_type n = str.find(DECIMAL_POINT);  
		string::size_type len = str.length();
		if ((n != string::npos) && (len > (n + precision))) 
		{   
			str[ n + precision] = '\0';//���ǵ�һ���������  
			str.swap(string(str.c_str()));//ɾ��nul֮��Ķ����ַ�
			return str;
		} 
		else if((n != string::npos) && len <= (n + precision))
		{
			string st;
			int count = precision - len;
			//for(int i = 0; i<= (precision - len) ; ++i)   //��ѭ�����������Ͳ�һ��
			for(int i = 0; i<= count ; ++i)
				st.push_back('0');
			return (str + st);
		}
		else if(n == string::npos)// value�Ǹ�����
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
		out.precision(prec);//����Ĭ�Ͼ���  
		out<<value;  
		string str = out.str(); //������ȡ���ַ��� 
		size_t n = str.find(DECIMAL_POINT);  
		if ((n != string::npos) 
			&& (str.size()> n+decplaces)) //�������ٻ���decplacesλ��
		{   
			str[n+decplaces]='\0';//���ǵ�һ���������  
		}  
		str.swap(string(str.c_str()));//ɾ��nul֮��Ķ����ַ� 
		return str;
	}

	/***------------------------�ַ�����ͳ��----------------------------***/
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
		//TODO: 20�Ǹ���ֵ
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
}