#ifndef ZTC__INCLUDE__ZTYPE_H
#define ZTC__INCLUDE__ZTYPE_H

#include "ZMacroDefine.h"

BEGIN_ZTC_NAMESPACE
//类型定义

#ifdef _MSC_VER
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;
typedef char int8_t;
typedef short int16_t;
typedef int int32_t;
typedef long long int64_t;
#else

#endif
END_ZTC_NAMESPACE
#endif //ZTC__INCLUDE__ZTYPE_H