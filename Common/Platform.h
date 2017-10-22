#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#ifdef __LINUX__
#elif __WINDOWS__
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
	typedef __int64           int64;
	typedef unsigned __int64  uint64;
	typedef float             float32;
	typedef double            double64;
#ifdef __LINUX__
	typedef int32             HANDLE;
#elif __WINDOWS__
#endif

}
#endif
