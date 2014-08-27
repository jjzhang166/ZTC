#ifndef ZTC_TEST_TESTPICTUREREAD_H
#define ZTC_TEST_TESTPICTUREREAD_H

#include <stdio.h>  
#include "stdlib.h"  
#include "math.h"  
#include <iostream>  
#include <string>
#include "../ZTC/include/ZCommonality.h"
#include "../ZTC/include/ZCommon.hpp"
#include "../ZTC/PictureRead/ZBitmapStruct.h"
#include "../ZTC/PictureRead/ZPictureFunctionPool.h"
#include "../ZTC/PictureRead/ZBitmap.h"

#define PI 3.14159//圆周率宏定义  
#define LENGTH_NAME_BMP 30//bmp图片文件名的最大长度  

using namespace std;  
using namespace ZTC;

class X
{
}; 
class TestX:public X
{
	int a;
	X x;
};

class TestY:public X
{
	int a;
};

struct NavigationResult
{
	int num;
	wstring name;
	int mId;
};

class Test
{
public:
	NavigationResult m_navigationResult;
};

int TestPictureRead()
{   
	Test test;
	test.m_navigationResult.name = L"中国人";
	wcout<<test.m_navigationResult.name<<endl;

	cout<<sizeof(TestX)<<" : "<<sizeof(TestY)<<endl;

	int arry[] = {2, 4, 1};
	InsertionSort(arry, 3);

	//变量定义  
	BitmapFileHeader bitmapHead;  
	RGBQuad strPla[256];//256色调色板  
	BitmapInfoHeader strInfo; 

	ZRGB *imagedata = NULL;//动态分配存储原图片的像素信息的二维数组  
	ZRGB *imagedataRot = NULL;//动态分配存储旋转后的图片的像素信息的二维数组  
	int width = 0; //图片的宽度
	int height = 0;//图片的高度  
	string strFile = "G:\\Dev\\Project\\C++\\PictureRead\\Picture\\bn.bmp";
	cout<<"请输入所要读取的文件名:"<<endl;  
	//cin>>strFile;  
	ifstream ifile("G:\\Dev\\Project\\C++\\PictureRead\\Picture\\bn.bmp");
	ReadBitmapFileHead(ifile, bitmapHead);

	BitmapFileHeader bitmapFileHeader;
	BitmapInfoHeader bitmapInfoHeader;
	RGBQuad quad;
	ZBitmap zBitmap("G:\\Dev\\Project\\C++\\PictureRead\\Picture\\bn.bmp");
	int m = zBitmap.GetWidth();
	zBitmap.ReadBitmapInfoHeader(bitmapInfoHeader);
	zBitmap.ReadBitmapFileHeader(bitmapFileHeader);
	zBitmap.ReadQuad(quad);
	showBmpInforHead(bitmapInfoHeader);
	showBmpHead(bitmapFileHeader);

	cout<<"文件名称："<<strFile<<endl;
	FILE *fpi = NULL;
	FILE *fpw = NULL;  
	fpi = fopen(strFile.c_str(), "rb");  
	if(fpi != NULL)
	{  
		//先读取文件类型  
		WORD bfType;  
		fread(&bfType, 1, sizeof(WORD), fpi);  
		if(0x4d42 != bfType)  
		{  
			cout<<"the file is not a bmp file!"<<endl;  
			return NULL;  
		}  
		//读取bmp文件的文件头和信息头  
		fread(&bitmapHead, 1, 14, fpi);  
		cout<<sizeof(BitmapFileHeader)<<" : "<<sizeof(DWORD)<<" : "<<sizeof(WORD)<<endl;
		showBmpHead(bitmapHead);//显示文件头  
		fread(&strInfo, 1, sizeof(BitmapInfoHeader), fpi);  
		showBmpInforHead(strInfo);//显示文件信息头  

		//读取调色板  
		for(unsigned int nCounti=0;nCounti<strInfo.biClrUsed;nCounti++)  
		{  
			fread((char *)&(strPla[nCounti].rgbBlue),1,sizeof(BYTE),fpi);  
			fread((char *)&(strPla[nCounti].rgbGreen),1,sizeof(BYTE),fpi);  
			fread((char *)&(strPla[nCounti].rgbRed),1,sizeof(BYTE),fpi);  
			fread((char *)&(strPla[nCounti].rgbReserved),1,sizeof(BYTE),fpi);  
		}  

		width = strInfo.biWidth;  
		height = strInfo.biHeight;  
		//图像每一行的字节数必须是4的整数倍  
		width = (width * sizeof(ZRGB) + 3) / 4 * 4;  
		//imagedata = (ZRGB*)malloc(width * height * sizeof(ZRGB));  
		imagedata = (ZRGB*)malloc(width * height);  
		imagedataRot = (ZRGB*)malloc(2 * width * 2 * height * sizeof(ZRGB));  
		//初始化原始图片的像素数组  
		for(int i = 0;i < height;++i)  
		{  
			for(int j = 0;j < width;++j)  
			{  
				(*(imagedata + i * width + j)).blue = 0;  
				//(*(imagedata + i * width + j)).green = 0;  
				//(*(imagedata + i *  width + j)).red = 0;  
			}  
		}  
		//初始化旋转后图片的像素数组  
		for(int i = 0;i < 2 * height;++i)  
		{  
			for(int j = 0;j < 2 * width;++j)  
			{  
				(*(imagedataRot + i * 2 * width + j)).blue = 0;  
				//(*(imagedataRot + i * 2 * width + j)).green = 0;  
				//(*(imagedataRot + i * 2 * width + j)).red = 0;  
			}  
		}  
		//fseek(fpi,54,SEEK_SET);  
		//读出图片的像素数据  
		fread(imagedata,sizeof(struct ZRGB) * width,height,fpi);  
		fclose(fpi);  
	}  
	else  
	{  
		cout<<"file open error!"<<endl;  
		return NULL;  
	}  

	//图片旋转处理  
	int RotateAngle;//要旋转的角度数  
	double angle;//要旋转的弧度数  
	int midX_pre,midY_pre,midX_aft,midY_aft;//旋转所围绕的中心点的坐标  
	midX_pre = width / 2;  
	midY_pre = height / 2;  
	midX_aft = width;  
	midY_aft = height;  
	int pre_i,pre_j,after_i,after_j;//旋转前后对应的像素点坐标  
	cout<<"输入要旋转的角度（0度到360度，逆时针旋转）："<<endl;  
	cin>>RotateAngle;  
	angle = 1.0 * RotateAngle * PI / 180;  
	for(int i = 0;i < 2 * height;++i)  
	{  
		for(int j = 0;j < 2 * width;++j)  
		{  
			after_i = i - midX_aft;//坐标变换  
			after_j = j - midY_aft;  
			pre_i = (int)(cos((double)angle) * after_i - sin((double)angle) * after_j) + midX_pre;  
			pre_j = (int)(sin((double)angle) * after_i + cos((double)angle) * after_j) + midY_pre;  
			if(pre_i >= 0 && pre_i < height && pre_j >= 0 && pre_j < width)//在原图范围内  
				*(imagedataRot + i * 2 * width + j) = *(imagedata + pre_i * width + pre_j);  
		}  
	}  

	//保存bmp图片  
	if((fpw=fopen("b.bmp","wb"))==NULL)  
	{  
		cout<<"create the bmp file error!"<<endl;  
		return NULL;  
	}  
	WORD bfType_w=0x4d42;  
	fwrite(&bfType_w,1,sizeof(WORD),fpw);  
	//fpw +=2;  
	fwrite(&bitmapHead,1,sizeof(BitmapFileHeader),fpw);  
	strInfo.biWidth = 2 * width;  
	strInfo.biHeight = 2 * height;  
	fwrite(&strInfo,1,sizeof(BitmapInfoHeader),fpw);  
	//保存调色板数据  
	for(unsigned int nCounti=0;nCounti<strInfo.biClrUsed;nCounti++)  
	{  
		fwrite(&strPla[nCounti].rgbBlue,1,sizeof(BYTE),fpw);  
		fwrite(&strPla[nCounti].rgbGreen,1,sizeof(BYTE),fpw);  
		fwrite(&strPla[nCounti].rgbRed,1,sizeof(BYTE),fpw);  
		fwrite(&strPla[nCounti].rgbReserved,1,sizeof(BYTE),fpw);  
	}  
	//保存像素数据  
	for(int i =0;i < 2 * height;++i)  
	{  
		for(int j = 0;j < 2 * width;++j)  
		{  
			fwrite( &((*(imagedataRot + i * 2 * width + j)).blue),1,sizeof(BYTE),fpw);  
			//fwrite( &((*(imagedataRot + i * 2 * width + j)).green),1,sizeof(BYTE),fpw);  
			//fwrite( &((*(imagedataRot + i * 2 * width + j)).red),1,sizeof(BYTE),fpw);  
		}  
	}  
	fclose(fpw);  

	//释放内存  
	delete[] imagedata;  
	delete[] imagedataRot;  
}  

#endif //ZTC_TEST_TESTPICTUREREAD_H