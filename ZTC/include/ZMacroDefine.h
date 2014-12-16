/*
* Copyright (c) 2013 ZZ
* All rights reserved.
* 
* File Name       : ZMacroDefine.h
* File Identifier :
* Abstract        :
* 
* Current Version : 1.0
* Author          : ZZ
* Completion Date : 2013.12.2 22:15:8
*
* Replace Version : 
* Original Author :
* Completion Date : 2013.12.2 22:15:8
*/

#ifndef ZTC_INCLUDE_ZMACRODEFINE_H
#define ZTC_INCLUDE_ZMACRODEFINE_H

#define BEGIN_ZTC_NAMESPACE namespace ZTC{
#define END_ZTC_NAMESPACE }
#define USE_NAMESPACE_ZTC using namespace ZTC;


#ifdef _MSC_VER
	#ifdef ZTC_EXPORTS
		#define ZTC_CLASS __declspec(dllexport)
		#define ZTC_API extern "C" __declspec(dllexport)
	#else
		#define ZTC_CLASS __declspec(dllimport)
		#define ZTC_API extern "C" __declspec(dllimport)
		#pragma comment(lib, "ZTC.lib")
	#endif
#elif __GNUC__
	#define ZTC_CLASS
	#define ZTC_API
#else
	#error "unsupported compile!!!"
#endif

#endif //ZTC_INCLUDE_ZMACRODEFINE_H