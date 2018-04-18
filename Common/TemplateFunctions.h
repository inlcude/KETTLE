#ifndef __TEMPLATE_FUNCTIONS_H__
#define __TEMPLATE_FUNCTIONS_H__
#include"KETTLEPlatform.h"
namespace KETTLE
{
	template <typename T>
	KETTLE::int32 getArrayLen(T& array)
	{
		return (sizeof(array) / sizeof(array[0]));
	}
}

#endif