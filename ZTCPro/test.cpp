typedef unsigned long long U32;

inline unsigned int rank(const unsigned long long& n)
{
	if (n<2) return 0;

	unsigned long long k(1);
	unsigned int i=0;
	for (;i<sizeof(unsigned long long)*8;++i)
	{
		if(n<k) break;
		k <<=1;
	}
	return i-1;
}

inline unsigned int bitsOfNumber(const unsigned long long& n){return rank(n)+1;}

wstring numToWstring( U32 num, bool isTow = false)
{
	wstring unit(L"");
	switch(num % 10)
	{
	case 0:
		{
			unit = L"";			
		}break;
	case 1:
		{
			unit = L"一";
		}break;
	case 2:
		{
			if(!isTow)
				unit = L"两";
			else
				unit = L"二";
		}break;
	case 3:
		{
			unit = L"三";
		}break;
	case 4:
		{
			unit = L"四";
		}break;
	case 5:
		{
			unit = L"五";
		}break;
	case 6:
		{
			unit = L"六";
		}break;
	case 7:
		{
			unit = L"七";
		}break;
	case 8:
		{
			unit = L"八";
		}break;
	case 9:
		{
			unit = L"九";
		}break;
	}
	return unit;
}


wstring numberCovertPromptData( U32 num, bool isTow = false)
{
	wstring reStr;
	//wstring unitStr(L"十百千万零");
	//U32 len = unitStr.length();

	//wstring unitStr[] = {L"十", L"百", L"千", L"万", L"十万", L"百万",L"千万",L"亿", L"零"};
	//U32 len = 9;
	wstring unitStr[] = {L"十", L"百", L"千", L"万", L"亿", L"零"};
	U32 len = 6;

	U32 i = 0;
	wstring strNum;
	U32 tmpNum = num;
	wstring unit;
	wstring preUnit;
	while(tmpNum != 0)
	{
		U32 tmp = tmpNum % 10;
	 	tmpNum = tmpNum / 10;
		if(tmp != 0)
			strNum = numToWstring(tmp, true);
		else
			strNum = L"";
		if(i != 0 && !strNum.empty()) 
		{
			//unit = unitStr[i - 1];
			if(i >= 5 && i < 8)
			{
				unit = unitStr[i%5];
				if(i == 5)
					preUnit = L"";
			}
			else if(i >= 9 )
			{
				unit = unitStr[i%9];
			}
			else if(i == 8)
			{
				unit = unitStr[4];
				preUnit = L"";
			}
			else
				unit = unitStr[i - 1];
		}
		if(i != 0 && strNum.empty() && !reStr.empty())
		{
			if(i == 4)
				unit = unitStr[3];
			else if( i == 8)
				unit = unitStr[4];
			else if(reStr.compare(L"亿") != 0 && reStr.compare(L"万") != 0)
			{
				preUnit = unit;
				unit = unitStr[len - 1];
			}
			else
			{
				unit = L"";
			}
		}

		if(i == 8 && strNum.empty() && reStr.empty() )
		{
			preUnit = L"";
			unit = unitStr[4];
		}
		if(i == 4 && strNum.empty() && reStr.empty() )
		{
			preUnit = L"";
			unit = unitStr[3];
		}

		if(preUnit.compare(unit) == 0)
			reStr = strNum + reStr;
		else if(reStr.compare(L"万") == 0 && unit.compare(L"亿") == 0)
			reStr = strNum + unit;
		else
			reStr = strNum + unit + reStr;

		++i;
	}

	if(num >= 10 && num < 20)
		reStr = reStr.substr(1);

	if(0 == reStr.substr(0, 2).compare(L"一十")
		&& (0 == reStr.substr(reStr.length() - 1).compare(L"万") || 0 == reStr.substr(reStr.length() - 1).compare(L"亿")))
		reStr = reStr.substr(1);

	return reStr;
}

void numToChinese()
{
	setlocale(LC_ALL,"chs");
	U32 i = 100;
	U32 num[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,55,44,100,101,109,110,111,122,1000,1001
	,1011
	,1101
	,1111
	,10000
	,10001
	,10010
	,10100
	,11000
	,11100
	,11110
	,11111
	,100000
	,200000
	,111100
	,111111
	,1111111
	,10000000
	,11111111
	,100000000
	,111111111
	,1000000000
	,1111111111
	,10000000000
	,11101101010
	,100000000000
	,111011010101
	,1000000000000
	,1110110101011
	,10000000000000
	};
	U32 n = sizeof(num)/sizeof(U32);
	wstring re;
	for(U32 i = 0; i < n; ++i)
	{
		re = numberCovertPromptData(num[i]);
		//cout<<num[i]<<" : "<<re<<endl;
		wprintf(L"num: %lld , %s\n", num[i], re.c_str());
	}
	cout<<endl;
}
