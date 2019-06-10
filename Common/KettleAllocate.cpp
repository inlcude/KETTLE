#include"KettleAllocate.h"
/////////////////////////////////////////////////////////////

KETTLE::KettleAllocate::KettleAllocate(std::shared_ptr<IAllocate> mempool)
:m_MemoryPool(mempool){

}

void* KETTLE::KettleAllocate::allocate(size_t nSize){
    return m_MemoryPool->allocate(nSize);
}

void KETTLE::KettleAllocate::deallocate(void* p){
    m_MemoryPool->deallocate(p);
}








/////////////////////////////////////////////////////////////
#ifdef __USE_MEMPOOL__
static KETTLE::KettleMemoryPool<> mempool;
void* operator new(size_t nSize){
    return mempool.allocate(nSize);
}

void* operator new[](size_t nSize){
    return mempool.allocate(nSize);
}

void operator delete(void* ptr){
    mempool.deallocate(ptr);
}

void operator delete[](void* ptr){
    mempool.deallocate(ptr);
}
#endif