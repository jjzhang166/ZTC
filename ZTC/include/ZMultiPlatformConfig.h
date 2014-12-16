#ifndef ZTC__Include__ZMultiPlatformConfig_h
#define ZTC__Include__ZMultiPlatformConfig_h

#ifdef _MSC_VER
	#include <WinSock2.h>
	#include <WS2tcpip.h>
	#include <Windows.h>
	#ifdef _WIN32_WCE
		#pragma comment(lib, "ws2.lib")
	#else
		#pragma comment(lib, "Ws2_32.lib")
	#endif
	#define Hash_map stdext::hash_map
	#define snprintf _snprintf
#elif __GNUC__
	#include <sys/time.h>
	#include <stdint.h>
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
	#include <iconv.h>
	#include <pthread.h>
	#include <netdb.h>
	#include <semaphore.h>
	#define Hash_map __gnu_cxx::hash_map
#endif

#endif //ZTC__Include__ZMultiPlatformConfig_h