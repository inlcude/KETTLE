#ifndef __TEMPLATE_DELEGATE_H__
#define __TEMPLATE_DELEGATE_H__
#include"COMMONALLOC.h"
#include<list>

namespace KETTLE
{
	template<typename T>
	class IDelegate
	{
	public:
		virtual void Invoke(T* param) = 0;
	};

	template<typename T, typename U>
	class Delegate : public IDelegate<U>
	{
	public:
		Delegate(T* _instance, void (T::*Functions)(U*)) : m_Instance(_instance), m_pFun(Functions) {}

		virtual ~Delegate() {}
		virtual void Invoke(U* a)
		{
			(m_Instance->*m_pFun)(a);
		}

		T*          GetClassObj()
		{
			return m_Instance;
		}

		void (T::*GetClsFunc())(U*)
		{
			return m_pFun;
		}

	private:
		T*          m_Instance;
		void        (T::*m_pFun)(U*);
	};

	template<typename U>
	class EventPool
	{
	public:
		template<typename T>
		void Attach(T* _instance, void (T::*Funtions)(U*))
		{
			IDelegate<U> *pNewFunctions = new Delegate<T,U>(_instance, Funtions);
			m_Pool.push_back(pNewFunctions);
		}

		template<typename T>
		void Detach(T* _instance, void (T::*Funtions)(U*))
		{
			typename listpool::iterator iter = m_Pool.begin();
			for (;iter != m_Pool.end();++iter)
			{
				if ((*iter)->GetClassObj() == _instance && *iter->GetClsFunc() == Funtions)
				{
					SAFE_DELETE_PTR(*iter);
					iter = m_Pool.erase(iter);
				}
			}
		}

		void Invoke(U* a)
		{
			typename listpool::iterator iter = m_Pool.begin();
			for (;iter != m_Pool.end();++iter) (*iter)->Invoke(a);
		}
	private:
		typedef std::list<IDelegate<U>*>      listpool;
		listpool                              m_Pool;
	};
}
#endif
