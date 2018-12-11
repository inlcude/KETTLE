#ifndef __MEMORY_TRACE_H__
#define __MEMORY_TRACE_H__

    #define SAFE_DELETE(p) if(p){delete p;p = nullptr;}
    #define SAFE_DELETE_ARRAY(p) if(p){delete[] p;p = nullptr;}

namespace KETTLE{

}
#endif