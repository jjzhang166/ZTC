#ifndef ZTC_PICTUREREAD_FUNCTIONPOOL_H
#define ZTC_PICTUREREAD_FUNCTIONPOOL_H

#include <fstream>
#include "ZBitmapStruct.h"

using std::ofstream;
using std::ifstream;

namespace ZTC
{
	bool ReadBitmapFileHead(ifstream &file, BitmapFileHeader &bitmapFileHead);
	void showBmpHead(BitmapFileHeader pBmpHead);
	void showBmpInforHead(BitmapInfoHeader pBmpInforHead);
}

#endif //ZTC_PICTUREREAD_FUNCTIONPOOL_H