#include "ZBitmap.h"
#include <string>
#include <exception>

#include "../include/ZCommonality.h"

namespace ZTC
{
	ZBitmap::ZBitmap(const char *pFileName):m_pBitmapInfoHeader(NULL)
	{
		m_ifstream.open(pFileName, std::ifstream::in | std::ifstream::binary);
		m_pBitmapInfoHeader = new (std::nothrow)BitmapInfoHeader();
		ReadBitmapInfoHeader(*m_pBitmapInfoHeader);
	}

	ZBitmap::~ZBitmap()
	{
		if(m_ifstream)
			m_ifstream.close();

		DELETE_PTR(m_pBitmapInfoHeader);
	}

	bool ZBitmap::IsValid()
	{
		if(!m_ifstream || !m_ifstream.is_open()|| !m_pBitmapInfoHeader)
			return false;
		else
			return true;
	}

	bool ZBitmap::ReadBitmapFileHeader(BitmapFileHeader &bitmapFileHeader)
	{
		if(!m_ifstream)
			return false;

		char buf[4] = {'\0'};
		
		int tempNum1 = sizeof(unsigned short);
		int tempNum2 = sizeof(unsigned long);

		m_ifstream.seekg(0, std::ios::beg);

		m_ifstream.read(buf, tempNum1); //文件类型
		string str = CharToHex(buf);
		bitmapFileHeader.bfType = HexToDec(str.c_str());

		m_ifstream.read(buf, tempNum2); //文件大小
		str = CharToHex(buf);
		bitmapFileHeader.bfSize = HexToDec(str.c_str());

		m_ifstream.read(buf, tempNum1); //保留字
		str = CharToHex(buf);
		bitmapFileHeader.bfReserved1 = HexToDec(str.c_str());

		m_ifstream.read(buf, tempNum1); //保留字
		str = CharToHex(buf);
		bitmapFileHeader.bfReserved2 = HexToDec(str.c_str());
		
		m_ifstream.read(buf, tempNum2); //文件头到实际位图数据的偏移字节数
		str = CharToHex(buf);
		bitmapFileHeader.bfOffBits = HexToDec(str.c_str());
		
		return true;
	}

	bool ZBitmap::ReadBitmapInfoHeader(BitmapInfoHeader &bitmapInfoHeader)
	{
		if(!m_ifstream)
			return false;

		char buf[4] = {'\0'};
		
		int tempNum1 = sizeof(WORD);
		int tempNum2 = sizeof(DWORD);
		int tempNum3 = sizeof(LONG);

		m_ifstream.seekg(0, std::ios::beg);
		//移动到信息头位置
		m_ifstream.seekg(BitmapFileHeaderSize, std::ios::beg);

		m_ifstream.read(buf, tempNum2); //信息头大小
		string str = CharToHex(buf);
		bitmapInfoHeader.biSize = HexToDec(str.c_str());

		m_ifstream.read(buf, tempNum3); //图像宽度
		str = CharToHex(buf);
		bitmapInfoHeader.biWidth = HexToDec(str.c_str()); 

		m_ifstream.read(buf, tempNum3); //图像高度
		str = CharToHex(buf);
		bitmapInfoHeader.biHeight = HexToDec(str.c_str()); 

		m_ifstream.read(buf, tempNum1); //位平面数，必须为1
		str = CharToHex(buf);
		bitmapInfoHeader.biPlanes = HexToDec(str.c_str()); 

		m_ifstream.read(buf, tempNum1); //每像素二进制位数
		str = CharToHex(buf);
		bitmapInfoHeader.biBitCount = HexToDec(str.c_str());

		m_ifstream.read(buf, tempNum2); //压缩类型
		str = CharToHex(buf);
		bitmapInfoHeader.biCompression = HexToDec(str.c_str());

		m_ifstream.read(buf, tempNum2); //压缩图像大小字节数
		str = CharToHex(buf);
		bitmapInfoHeader.biSizeImage = HexToDec(str.c_str());

		m_ifstream.read(buf, tempNum3); //水平分辨率
		str = CharToHex(buf);
		bitmapInfoHeader.biXPelsPerMeter = HexToDec(str.c_str());
		 
		m_ifstream.read(buf, tempNum3); //垂直分辨率
		str = CharToHex(buf);
		bitmapInfoHeader.biYPelsPerMeter = HexToDec(str.c_str());

		m_ifstream.read(buf, tempNum2); //位图实际用到的色彩数（多少种颜色）
		str = CharToHex(buf);
		bitmapInfoHeader.biClrUsed = HexToDec(str.c_str());
		
		m_ifstream.read(buf, tempNum2); //本位图中重要的色彩数，如果为0，则认为所有颜色都是重要的
		str = CharToHex(buf);
		bitmapInfoHeader.biClrImportant = HexToDec(str.c_str());
		
		return true;
	}

	bool ZBitmap::ReadQuad(RGBQuad &quad)
	{
		if(!IsValid())
			return false;

		char buf[4] = {'\0'};
		
		int tempNum1 = sizeof(BYTE);

		//移动到调色板头位置
		m_ifstream.seekg(BitmapFileHeaderSize, std::ios::beg);
		m_ifstream.seekg(BitmapInfoHeaderSize, std::ios::cur);
 
		m_ifstream.read(buf, tempNum1); //该颜色的蓝色分量
		string str = CharToHex(buf);
		quad.rgbBlue = HexToDec(str.c_str());

		m_ifstream.read(buf, tempNum1); //该颜色的绿色分量
		str = CharToHex(buf);
		quad.rgbGreen = HexToDec(str.c_str());

		m_ifstream.read(buf, tempNum1); //该颜色的红色分量  
		str = CharToHex(buf);
		quad.rgbRed = HexToDec(str.c_str());

		m_ifstream.read(buf, tempNum1); //保留值  
		str = CharToHex(buf);
		quad.rgbReserved = HexToDec(str.c_str());

		return true;
	}

	int ZBitmap::GetWidth()
	{
		if(!IsValid() || !m_pBitmapInfoHeader)
			return 0;
		return m_pBitmapInfoHeader->biWidth;
	}

	int ZBitmap::GetHeight()
	{
		if(!IsValid() || !m_pBitmapInfoHeader)
			return 0;
		
		return m_pBitmapInfoHeader->biHeight;
	}

	COLORREF ZBitmap::GetPixel(int x, int y)
	{
		return 0;
	}
}