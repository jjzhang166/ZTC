#ifndef ZTC_PICTUREREAD_BITMAP_H
#define ZTC_PICTUREREAD_BITMAP_H

namespace ZTC
{
	typedef unsigned char BYTE;  
	typedef unsigned short WORD;  
	typedef unsigned long DWORD;  
	typedef signed int LONG;
	typedef DWORD COLORREF;

	const int BitmapFileHeaderSize = 14;
	const int BitmapInfoHeaderSize = 40;
	const int RGBQuadSize = 4;

	//位图文件头定义;    
	struct BitmapFileHeader
	{  
		WORD bfType; //文件类型，必须是0x424D，即字符“BM”  
		DWORD bfSize; //文件大小  
		WORD bfReserved1; //保留字,必须为0  
		WORD bfReserved2; //保留字，必须为0
		DWORD bfOffBits; //从文件头到实际位图数据的偏移字节数  
	};  

	struct BitmapInfoHeader
	{  
		DWORD biSize;//信息头大小  
		LONG biWidth;//图像宽度  
		LONG biHeight;//图像高度  
		WORD biPlanes;//位平面数，必须为1  
		WORD biBitCount;//每像素二进制位数  
		DWORD biCompression; //压缩类型  
		DWORD biSizeImage; //压缩图像大小字节数  
		LONG biXPelsPerMeter; //水平分辨率  
		LONG biYPelsPerMeter; //垂直分辨率  
		DWORD biClrUsed; //位图实际用到的色彩数（多少种颜色）  
		DWORD biClrImportant; //本位图中重要的色彩数，如果为0，则认为所有颜色都是重要的  
	}; //位图信息头定义  

	struct RGBQuad
	{  
		BYTE rgbBlue; //该颜色的蓝色分量  
		BYTE rgbGreen; //该颜色的绿色分量  
		BYTE rgbRed; //该颜色的红色分量  
		BYTE rgbReserved; //保留值  
	};//调色板定义  

	//像素信息  
	struct ZRGB  
	{  
		BYTE red;
		BYTE green;  
		BYTE blue;
	};  
}
#endif //ZTC_PICTUREREAD_BITMAP_H