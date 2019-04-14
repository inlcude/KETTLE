#ifndef __ALLOCATE_H__
#define __ALLOCATE_H__

#include"KETTLEPlatform.h"
#include"SingltonTemplate.h"
#include"Log.h"

#include<unordered_map>
#include<values.h>
/////////////////////////////////////////////////////////////
namespace KETTLE{

typedef union MemoryNode{
    MemoryNode* pNext;
}MemoryNode;

typedef struct MemoryBlock{
    KETTLE::uint32 BlockSize;			// 需要切割的内存大小
    KETTLE::uint32 MaxNodeNum;		    // 最大的节点数量
    KETTLE::uint32 free;				// 可供分配的内存大小
    MemoryNode* pHead;			        // 头指针，指向可用内存块的头部节点
    MemoryBlock* pNext;				    // 指向下一个内存块信息节点，
    void* BlockAddr;	                // 起始地址
    MemoryBlock(){
        
    }
}MemoryBlock;


/////////////////////////////////////////////////////////////
class IAllocate{
public:
    virtual ~IAllocate(){}

    virtual void* allocate(size_t nSize) = 0;
    virtual void  deallocate(void* nSize) = 0;
};

/////////////////////////////////////////////////////////////
template<KETTLE::uint32 MAX_ALLOCATE_SIZE = 1024>
class KettleMemoryPool : public IAllocate{
    typedef std::unordered_map<size_t,MemoryBlock*> MEMORY_POOL;
    typedef MEMORY_POOL::iterator MP_ITER;
    typedef MEMORY_POOL::const_iterator CON_MP_ITER;
public:
    KettleMemoryPool() : MAX_SIZE(MAX_ALLOCATE_SIZE){
        memset(m_MemPool,0,sizeof(m_MemPool));
        for(KETTLE::uint32 i = 1; i <= MAX_POOL_SIZE;++i){
            size_t nSize = POOL_ALIGNMENT * i;
            MemoryBlock* pMemBlock = SplitMemory(nSize);
            m_MemPool[i-1] = pMemBlock;
        }
    }


    virtual void* allocate(size_t nSize) override final{
        // 调整为8的边界
        const size_t nAllignSize = nSize + ((POOL_ALIGNMENT-((nSize) % POOL_ALIGNMENT)) % POOL_ALIGNMENT);
        // 大于内存池能够分配的最大内存尺寸，直接从malloc分配
        if(nAllignSize > MAX_SIZE)
            return malloc(nSize);

        MemoryBlock* pBlock = FindBlock(nAllignSize);
        void* pMemory = pBlock->pHead;
        --pBlock->free;

        if(pBlock->free == 0)
            pBlock->pHead = NULL;
        else
            pBlock->pHead = pBlock->pHead->pNext;

        return pMemory;
    }
    virtual void  deallocate(void* p) override final{

    }
private:
    MemoryBlock* SplitMemory(size_t nSize){
        if(nSize < POOL_ALIGNMENT)
            return nullptr;

        KETTLE::int8* pMemory = (KETTLE::int8*)malloc(MAX_PAGE_SIZE);
        if(!pMemory)
            err_exit(errno,"Memory Split Memory error!");
            
        const KETTLE::uint32 split_times = MAX_PAGE_SIZE / nSize;

        MemoryBlock* pBlock = (MemoryBlock*)malloc(sizeof(MemoryBlock));
        memset(pBlock,0,sizeof(MemoryBlock));
        pBlock->BlockSize = nSize;
        pBlock->MaxNodeNum = split_times;
        pBlock->free = split_times;
        pBlock->pHead = (MemoryNode*)pMemory;
        pBlock->pNext = nullptr;
        pBlock->BlockAddr = pMemory;

        // 创建内存链表，
        for(KETTLE::uint32 i = 0; i < split_times;++i){
            MemoryNode* pNext = (MemoryNode*)(pMemory + nSize * i);

            if(i == (split_times - 1))
                pNext->pNext = nullptr;
            else
                pNext->pNext = (MemoryNode*)(pMemory + nSize * (i + 1));
        }

        return pBlock;
    }

    /**
     * 这里可以做优化，做缓存寻找可用Block快，不然太慢了，
     */
    MemoryBlock* FindBlock(const size_t nSize){

        KETTLE::int32 index = nSize / POOL_ALIGNMENT - 1;
        if(index >= MAX_POOL_SIZE)
            return NULL;
        else{
            MemoryBlock* pHeadBlock = m_MemPool[index];
            MemoryBlock* pFindBlock = pHeadBlock;
            while(pFindBlock){
                if(pFindBlock->free != 0)
                    break;
                else
                    pFindBlock = pFindBlock->pNext;
            }

            if(!pFindBlock){
                pFindBlock = SplitMemory(nSize);
                if(!pFindBlock)
                    err_exit(errno,"split Memory error!");
                pFindBlock->pNext = pHeadBlock;
                m_MemPool[index] = pFindBlock;
            }

            return pFindBlock;
        }
    }
private:


    const KETTLE::uint32 MAX_SIZE;
    const KETTLE::uint32 MAX_POOL_SIZE = MAX_SIZE / POOL_ALIGNMENT;
    static const KETTLE::uint32 MAX_PAGE_SIZE = 4096;
    static const KETTLE::uint32 POOL_ALIGNMENT = 8;
    //MEMORY_POOL     m_MemPool;
    MemoryBlock* m_MemPool[MAX_ALLOCATE_SIZE / POOL_ALIGNMENT];
};

/////////////////////////////////////////////////////////////
class KettleAllocate final : public IAllocate{
public:
    KettleAllocate(std::shared_ptr<IAllocate> mempool);

    virtual void* allocate(size_t nSize) override final;
    virtual void  deallocate(void* p) override final;
private:
    std::shared_ptr<IAllocate>          m_MemoryPool;
};


}

/////////////////////////////////////////////////////////////
#ifdef __USE_MEMPOOL__
void* operator new(size_t nSize);
void* operator new[](size_t nSize);
void operator delete(void* ptr);
void operator delete[](void* ptr);
#endif
/////////////////////////////////////////////////////////////
#endif