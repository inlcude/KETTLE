#ifndef __SINGLETON_TEMPLATE_H__
#define __SINGLETON_TEMPLATE_H__

#include"COMMONALLOC.h"

namespace KETTLE
{
    // 饿汉模式，需要做线程安全处理，双检测lock机制不是安全的，需要用一种方式处理
	template<typename T>
	class Singleton
	{
	public:
        // DCLP(double check lock pattern) is not safe
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

    // 懒汉模式，不做线程安全处理
    template<typename T>
    class Singleton2
    {
    public:
        static T* GetInstance()
        {
            return __instance;
        }

    protected:
        Singleton2() {}
        virtual ~Singleton2() { SAFE_DELETE_PTR(__instance); }
    private:
        static T* __instance;
    };

    template<typename T>
    T* Singleton2<T>::__instance = new T;
}

#endif