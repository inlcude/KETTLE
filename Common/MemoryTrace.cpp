

#include "MemoryTrace.h"


#undef new
void* operator new(size_t size){
    return ::malloc(size);
}


void* operator new(size_t size,const char* file,int line){
    return ::malloc(size);
}

void* operator new[](size_t size){
    return ::malloc(size);
}

void* operator new[](size_t size,const char* file,int line){
    return ::malloc(size);
}

void operator delete(void* p){
    ::free(p);
}

void operator delete(void* p,const char* file,int line){
    ::free(p);
}
void operator delete[](void* p){
    ::free(p);
}

void operator delete[](void* p,const char* file,int line){
    ::free(p);
}