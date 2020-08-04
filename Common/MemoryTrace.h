#ifndef __MEMORY_TRACE_H__
#define __MEMORY_TRACE_H__

#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <string>

#define SAFE_DELETE(p) if(p){delete p;p = nullptr;}
#define SAFE_DELETE_ARRAY(p) if(p){delete[] p;p = nullptr;}

namespace KETTLE{

}

/*
void* operator new(size_t size);
void* operator new(size_t size,const char* file,int line);
void* operator new[](size_t size);
void* operator new[](size_t size,const char* file,int line);

void operator delete(void* p);
void operator delete(void* p,const char* file,int line);
void operator delete[](void* p);
void operator delete[](void* p,const char* file,int line);
*/

#define KETTLE_NEW ::new
#define new KETTLE_NEW
#endif