#ifndef MemTrack_H_
#define MemTrack_H_

#include <typeinfo>

namespace MemTrack
{
    /* ---------------------------------------- class MemStamp */

    class MemStamp
    {
        public:        // member variables
            char const * const filename;
            int const lineNum;
        public:        // construction/destruction
            MemStamp(char const *filename, int lineNum)
                : filename(filename), lineNum(lineNum) {}
            ~MemStamp() { }
    };

    /* ---------------------------------------- memory allocation and stamping prototypes */

	class MemoryDumpInfo
	{
	public:
		static void *TrackMalloc(size_t size);
		static void TrackFree(void *p);
		static void TrackStamp(void *p, const MemStamp &stamp, char const *typeName);
		static void TrackDumpBlocks();
		static void TrackListMemoryUsage();
	};
//#ifdef __cplusplus
//	extern "C" {
//#endif
//		void *TrackMalloc(size_t size);
//		void TrackFree(void *p);
//		void TrackStamp(void *p, const MemStamp &stamp, char const *typeName);
//		void TrackDumpBlocks();
//		void TrackListMemoryUsage();
//#ifdef __cplusplus
//	}
//#endif
		/* ---------------------------------------- operator * (MemStamp, ptr) */

		template <class T> inline T *operator*(const MemStamp &stamp, T *p)
		{
			MemoryDumpInfo::TrackStamp(p, stamp, typeid(T).name());
			return p;
		}


}    // namespace MemTrack

/* ---------------------------------------- new macro */

#define MEMTRACK_NEW MemTrack::MemStamp(__FILE__, __LINE__) * new
#define new MEMTRACK_NEW

#endif    // MemTrack_H_
