#include "ZPictureFunctionPool.h"
#include <stdlib.h>
#include "../include/ZCommonality.h"
#include "../include/ZCommon.hpp"
#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::cin;
using std::endl;

namespace ZTC
{
	bool ReadBitmapFileHead(ifstream &file, BitmapFileHeader &bitmapFileHead)
	{
		char buf[4] = {'\0'};

		int tempNum1 = sizeof(unsigned short);
		int tempNum2 = sizeof(unsigned long);

		file.read(buf, tempNum1); //文件类型
		string str = CharToHex(buf);
		bitmapFileHead.bfType = HexToDec(str.c_str());

		file.read(buf, tempNum2); //文件大小
		str = CharToHex(buf);
		bitmapFileHead.bfSize = HexToDec(str.c_str());

		file.read(buf, tempNum1); //保留字
		str = CharToHex(buf);
		bitmapFileHead.bfReserved1 = HexToDec(str.c_str());

		file.read(buf, tempNum1); //保留字
		str = CharToHex(buf);
		bitmapFileHead.bfReserved2 = HexToDec(str.c_str());

		file.read(buf, tempNum2); //文件头到实际位图数据的偏移字节数
		str = CharToHex(buf);
		bitmapFileHead.bfOffBits = HexToDec(str.c_str());

		return true;
	}

	//显示位图文件头信息  
	void showBmpHead(BitmapFileHeader pBmpHead)
	{  
		cout<<"位图文件头: "<<endl; 
		cout<<"文件类型: "<<pBmpHead.bfType<<endl;
		cout<<"文件大小: "<<pBmpHead.bfSize<<endl;  
		cout<<"保留字_1: "<<pBmpHead.bfReserved1<<endl;  
		cout<<"保留字_2: "<<pBmpHead.bfReserved2<<endl;  
		cout<<"实际位图数据的偏移字节数: "<<pBmpHead.bfOffBits<<endl<<endl;  
	}  

	void showBmpInforHead(BitmapInfoHeader pBmpInforHead)
	{  
		cout<<"位图信息头: "<<endl;  
		cout<<"结构体的长度: "<<pBmpInforHead.biSize<<endl;  
		cout<<"位图宽: "<<pBmpInforHead.biWidth<<endl;  
		cout<<"位图高: "<<pBmpInforHead.biHeight<<endl;  
		cout<<"biPlanes平面数: "<<pBmpInforHead.biPlanes<<endl;  
		cout<<"biBitCount采用颜色位数: "<<pBmpInforHead.biBitCount<<endl;  
		cout<<"压缩方式: "<<pBmpInforHead.biCompression<<endl;  
		cout<<"biSizeImage实际位图数据占用的字节数: "<<pBmpInforHead.biSizeImage<<endl;  
		cout<<"X方向分辨率: "<<pBmpInforHead.biXPelsPerMeter<<endl;  
		cout<<"Y方向分辨率: "<<pBmpInforHead.biYPelsPerMeter<<endl;  
		cout<<"使用的颜色数: "<<pBmpInforHead.biClrUsed<<endl;  
		cout<<"重要颜色数: "<<pBmpInforHead.biClrImportant<<endl;  
	}  
}