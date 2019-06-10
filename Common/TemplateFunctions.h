#ifndef __TEMPLATE_FUNCTIONS_H__
#define __TEMPLATE_FUNCTIONS_H__
#include"KETTLEPlatform.h"
namespace KETTLE
{
    class CommonFunction
    {
    public:
        template <typename T>
        static KETTLE::int32 getArrayLen(T& array){
            return (sizeof(array) / sizeof(array[0]));
        }

        static void FunctionSleep(int milsec);
    };



}

#endif