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

#define PI 3.14159//Բ���ʺ궨��  
#define LENGTH_NAME_BMP 30//bmpͼƬ�ļ�������󳤶�  

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
	test.m_navigationResult.name = L"�й���";
	wcout<<test.m_navigationResult.name<<endl;

	cout<<sizeof(TestX)<<" : "<<sizeof(TestY)<<endl;

	int arry[] = {2, 4, 1};
	InsertionSort(arry, 3);

	//��������  
	BitmapFileHeader bitmapHead;  
	RGBQuad strPla[256];//256ɫ��ɫ��  
	BitmapInfoHeader strInfo; 

	ZRGB *imagedata = NULL;//��̬����洢ԭͼƬ��������Ϣ�Ķ�ά����  
	ZRGB *imagedataRot = NULL;//��̬����洢��ת���ͼƬ��������Ϣ�Ķ�ά����  
	int width = 0; //ͼƬ�Ŀ��
	int height = 0;//ͼƬ�ĸ߶�  
	string strFile = "G:\\Dev\\Project\\C++\\PictureRead\\Picture\\bn.bmp";
	cout<<"��������Ҫ��ȡ���ļ���:"<<endl;  
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

	cout<<"�ļ����ƣ�"<<strFile<<endl;
	FILE *fpi = NULL;
	FILE *fpw = NULL;  
	fpi = fopen(strFile.c_str(), "rb");  
	if(fpi != NULL)
	{  
		//�ȶ�ȡ�ļ�����  
		WORD bfType;  
		fread(&bfType, 1, sizeof(WORD), fpi);  
		if(0x4d42 != bfType)  
		{  
			cout<<"the file is not a bmp file!"<<endl;  
			return NULL;  
		}  
		//��ȡbmp�ļ����ļ�ͷ����Ϣͷ  
		fread(&bitmapHead, 1, 14, fpi);  
		cout<<sizeof(BitmapFileHeader)<<" : "<<sizeof(DWORD)<<" : "<<sizeof(WORD)<<endl;
		showBmpHead(bitmapHead);//��ʾ�ļ�ͷ  
		fread(&strInfo, 1, sizeof(BitmapInfoHeader), fpi);  
		showBmpInforHead(strInfo);//��ʾ�ļ���Ϣͷ  

		//��ȡ��ɫ��  
		for(unsigned int nCounti=0;nCounti<strInfo.biClrUsed;nCounti++)  
		{  
			fread((char *)&(strPla[nCounti].rgbBlue),1,sizeof(BYTE),fpi);  
			fread((char *)&(strPla[nCounti].rgbGreen),1,sizeof(BYTE),fpi);  
			fread((char *)&(strPla[nCounti].rgbRed),1,sizeof(BYTE),fpi);  
			fread((char *)&(strPla[nCounti].rgbReserved),1,sizeof(BYTE),fpi);  
		}  

		width = strInfo.biWidth;  
		height = strInfo.biHeight;  
		//ͼ��ÿһ�е��ֽ���������4��������  
		width = (width * sizeof(ZRGB) + 3) / 4 * 4;  
		//imagedata = (ZRGB*)malloc(width * height * sizeof(ZRGB));  
		imagedata = (ZRGB*)malloc(width * height);  
		imagedataRot = (ZRGB*)malloc(2 * width * 2 * height * sizeof(ZRGB));  
		//��ʼ��ԭʼͼƬ����������  
		for(int i = 0;i < height;++i)  
		{  
			for(int j = 0;j < width;++j)  
			{  
				(*(imagedata + i * width + j)).blue = 0;  
				//(*(imagedata + i * width + j)).green = 0;  
				//(*(imagedata + i *  width + j)).red = 0;  
			}  
		}  
		//��ʼ����ת��ͼƬ����������  
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
		//����ͼƬ����������  
		fread(imagedata,sizeof(struct ZRGB) * width,height,fpi);  
		fclose(fpi);  
	}  
	else  
	{  
		cout<<"file open error!"<<endl;  
		return NULL;  
	}  

	//ͼƬ��ת����  
	int RotateAngle;//Ҫ��ת�ĽǶ���  
	double angle;//Ҫ��ת�Ļ�����  
	int midX_pre,midY_pre,midX_aft,midY_aft;//��ת��Χ�Ƶ����ĵ������  
	midX_pre = width / 2;  
	midY_pre = height / 2;  
	midX_aft = width;  
	midY_aft = height;  
	int pre_i,pre_j,after_i,after_j;//��תǰ���Ӧ�����ص�����  
	cout<<"����Ҫ��ת�ĽǶȣ�0�ȵ�360�ȣ���ʱ����ת����"<<endl;  
	cin>>RotateAngle;  
	angle = 1.0 * RotateAngle * PI / 180;  
	for(int i = 0;i < 2 * height;++i)  
	{  
		for(int j = 0;j < 2 * width;++j)  
		{  
			after_i = i - midX_aft;//����任  
			after_j = j - midY_aft;  
			pre_i = (int)(cos((double)angle) * after_i - sin((double)angle) * after_j) + midX_pre;  
			pre_j = (int)(sin((double)angle) * after_i + cos((double)angle) * after_j) + midY_pre;  
			if(pre_i >= 0 && pre_i < height && pre_j >= 0 && pre_j < width)//��ԭͼ��Χ��  
				*(imagedataRot + i * 2 * width + j) = *(imagedata + pre_i * width + pre_j);  
		}  
	}  

	//����bmpͼƬ  
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
	//�����ɫ������  
	for(unsigned int nCounti=0;nCounti<strInfo.biClrUsed;nCounti++)  
	{  
		fwrite(&strPla[nCounti].rgbBlue,1,sizeof(BYTE),fpw);  
		fwrite(&strPla[nCounti].rgbGreen,1,sizeof(BYTE),fpw);  
		fwrite(&strPla[nCounti].rgbRed,1,sizeof(BYTE),fpw);  
		fwrite(&strPla[nCounti].rgbReserved,1,sizeof(BYTE),fpw);  
	}  
	//������������  
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

	//�ͷ��ڴ�  
	delete[] imagedata;  
	delete[] imagedataRot;  
}  

#endif //ZTC_TEST_TESTPICTUREREAD_H