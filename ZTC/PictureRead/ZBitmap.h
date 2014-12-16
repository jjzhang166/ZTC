#ifndef ZTC_PICTUREREAD_ZBITMAP_H
#define ZTC_PICTUREREAD_ZBITMAP_H

#include "ZBitmapStruct.h"

#include <stdio.h>
#include <fstream>

using std::ifstream;
using std::ofstream;

namespace ZTC
{
	/*struct BitmapFileHeader;
	struct BitmapInfoHeader;
	struct RGBQuad;*/

	class ZBitmap
	{
	public:
		ZBitmap(const char *pFileName);
		~ZBitmap();

		bool IsValid();
		bool ReadBitmapFileHeader(BitmapFileHeader &bitmapFileHeader);
		bool ReadBitmapInfoHeader(BitmapInfoHeader &bitmapInfoHeader);
		bool ReadQuad(RGBQuad &quad);
		int GetWidth();
		int GetHeight();
		COLORREF GetPixel(int x, int y);
	private:
		//FILE *m_pFile;
		ifstream m_ifstream;
		//BitmapFileHeader m_bitmapFileHeader;
		BitmapInfoHeader *m_pBitmapInfoHeader;

	};
}

#endif //ZTC_PICTUREREAD_ZBITMAP_H