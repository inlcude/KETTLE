#ifndef __SINGLETON_TEMPLATE_H__
#define __SINGLETON_TEMPLATE_H__

#include"COMMONALLOC.h"
template<typename T>
class Singleton
{
public:
	static T*    GetInstance()
	{
		if (!__instance)
		{
			// 做线程安全处理
			if (!__instance)
				__instance = new T();
		}

		return __instance;
	}

	~Singleton()
	{
		SAFE_DELETE_PTR(__instance);
	}
protected:
	Singleton() {};

	static T*   __instance;
};

template<typename T>
T* Singleton<T>::__instance = NULL;
#endif