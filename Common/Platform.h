#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#include<string.h>
#ifdef __LINUX__
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#elif __WINDOWS__
#include<Winsock2.h>
#include<windows.h>

#endif

namespace KETTLE
{
	typedef char              int8;
	typedef unsigned char     uint8;
	typedef short             int16;
	typedef unsigned short    uint16;
	typedef int               int32;
	typedef unsigned int      uint32;
#ifdef __WINDOWS__
	typedef __int64           int64;
	typedef unsigned __int64  uint64;
#elif __LINUX__
	typedef long long         int64;
	typedef unsigned long long uint64;
#endif
	typedef float             float32;
	typedef double            double64;
#ifdef __WINDOWS__
	typedef HANDLE            THREAD_ID;
#elif __LINUX__
#endif

}
using namespace KETTLE;
#endif
