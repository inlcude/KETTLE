#ifndef __TEMPLATE_FUNCTIONS_H__
#define __TEMPLATE_FUNCTIONS_H__
#include"KETTLEPlatform.h"


using namespace KETTLE;
namespace KETTLE
{
    class CommonFunction
    {
    public:
        template <typename T>
        static int32 getArrayLen(T& array){
            return (sizeof(array) / sizeof(array[0]));
        }

        static void FunctionSleep(int32 milsec);
        static std::string GetAppName();
        static std::string now();
        static std::string tid();
        static pthread_t GetSelfThreadId();
        static std::string getLogHead();

    };



}

#endif