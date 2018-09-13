#ifndef __TEMPLATE_DELEGATE_H__
#define __TEMPLATE_DELEGATE_H__
#include"COMMONALLOC.h"
#include<list>
#include<algorithm>

namespace KETTLE
{
	template<typename T>
	class IDelegate
	{
	public:
		virtual void Invoke(T* param) = 0;
		virtual ~IDelegate() {}
	};

	template<typename T, typename U>
	class Delegate final: public IDelegate<U>
	{
	public:
		Delegate(T* _instance, void (T::*Functions)(U*)) : m_Instance(_instance), m_pFun(Functions) {}

		virtual void Invoke(U* a) override final
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
#if __cplusplus >= 201103L

			m_Pool.erase(m_Pool.remoe_if(m_Pool.begin(),
				m_Pool.end(),
				[_instance, Funtions](IDelegate<U>* lst_obj) {
				Delegate<T, U>* obj = dynamic_cast<Delegate<T, U>*>(lst_obj);
				if (!obj) return false;
				return obj->GetClassObj() == _instance && obj->GetClsFunc() == Funtions;}
			));
#else
			typename listpool::iterator iter = m_Pool.begin();
			for (;iter != m_Pool.end();)
			{
				Delegate<T, U>* obj = dynamic_cast<Delegate<T, U>*>(*iter);
				if (obj->GetClassObj() == _instance && obj->GetClsFunc() == Funtions)
				{
					SAFE_DELETE_PTR(*iter);
					iter = m_Pool.erase(iter);
				}
				else ++iter;
			}
#endif	
		}

		void Invoke(U* a)
		{
			for (const auto& iter : m_Pool) iter->Invoke(a);
			//typename listpool::iterator iter = m_Pool.begin();
			//for (;iter != m_Pool.end();++iter) (*iter)->Invoke(a);
		}
	private:
		typedef std::list<IDelegate<U>*>      listpool;
		listpool                              m_Pool;
	};
}
#endif
