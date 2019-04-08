#ifndef __SINGLETON_TEMPLATE_H__
#define __SINGLETON_TEMPLATE_H__

#include"COMMONALLOC.h"

namespace KETTLE
{
    // singleton not thread safe
	template<typename T>
	class Singleton{
	public:
        // DCLP(double check lock pattern) is not safe
		static T*    GetInstance(){
			if (!__instance){
				// dd check
				if (!__instance)
					__instance = new T();
			}

			return __instance;
		}

		~Singleton(){
			SAFE_DELETE_PTR(__instance);
		}
	protected:
		Singleton() {};
        static T*   __instance;
	};

	template<typename T>
	T* Singleton<T>::__instance = NULL;

////////////////////////////////////////////////////////////////
    // singleton with thread safe
    template<typename T>
    class Singleton2{
    public:
        static T* GetInstance(){
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