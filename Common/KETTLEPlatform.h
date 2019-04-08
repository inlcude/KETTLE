#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#include<string.h>
#include<iostream>
#include<memory>

#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/in_systm.h>
#include<netinet/ip.h>
#include<netinet/ip_icmp.h>
#include<pthread.h>
#include<errno.h>
#include<sys/time.h>
#include<sys/mman.h>
#include<sys/types.h>
#include<stdlib.h>
#include<stddef.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>
#include<stdio.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<aio.h>
#include<ctype.h>
#include<sys/socket.h>
#include<netdb.h>
#include<sys/un.h>
#include<time.h>
#include<stddef.h>
#include<pthread.h>
#include<stdarg.h>

#pragma pack(push,1)
namespace KETTLE{
	typedef char              int8;
	typedef unsigned char     uint8;
	typedef short             int16;
	typedef unsigned short    uint16;
	typedef int               int32;
	typedef unsigned int      uint32;
	typedef long long         int64;
	typedef unsigned long long uint64;
	typedef float             float32;
	typedef double            double64;
	typedef int32             THREAD_HANDLE;
	typedef uint32            THREAD_ID;

}

#pragma pack(pop)
#endif
