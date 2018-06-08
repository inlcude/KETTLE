// Server.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include"KETTLEPlatform.h"
#include"SingltonTemplate.h"
#include"TemplateDelegate.h"
#include"TemplateFunctions.h"
#include"TcpSocket.h"


#include"VarList.h"
#include"MemTrack.h"
#include"Thread.h"

//#include<iostream>
//#include<boost/shared_ptr.hpp>
//#include<boost/timer.hpp>
#include<boost/timer/timer.hpp>
//#include<boost/progress.hpp>
//#include<boost/date_time/gregorian/gregorian.hpp>
//#include<boost/date_time/posix_time/posix_time.hpp>
//#include<boost/smart_ptr.hpp>
//#include<boost/optional.hpp>
//#include<boost/typeof/typeof.hpp>
//#include<boost/typeof/decltype.hpp>
//#include<boost/pool/singleton_pool.hpp>
//#include<boost/serialization/singleton.hpp>
#include<boost/flyweight/flyweight.hpp>


#include<map>
#include<vector>
#include<string>
#include<atomic>

using namespace KETTLE;
using namespace std;

struct Base
{
	virtual void vfunc(float) {}
};

struct Derived : public Base
{
	virtual void vfunc(int)  {}
	virtual void vfunc(float) override {}
};
class CallBackParam
{
public:
	CallBackParam()
	{

	}
private:
	int         m_a;
	int         m_b;
};

class CallBackParamChild : public CallBackParam
{
public:
	CallBackParamChild()
	{

	}
};

class TestCallBack
{
public:
	void cb_func(CallBackParam*) { cout << "call back" << endl; }
};
template<typename T1,typename T2>
auto add(T1 x, T2 y)->decltype(x + y);

__int64 sqrt(__int64 n) { return n * n; }

__int64 pow2(int n)
{
	if (n > 0) return n&1 ? sqrt(pow2(n >> 1)) << 1: sqrt(pow2(n >> 1));
	else return 1;
}

__int64 pow2_1(int n)
{
	__int64 nvalue = 1;
	while (n--) nvalue <<= 1;
	return nvalue;
}

class TestDelete
{
public:
	TestDelete()
	{
		CallBackParamChild* p = new CallBackParamChild;
		p->~CallBackParamChild();
	}
	~TestDelete()
	{
		CallBackParamChild t;
	}
};

namespace binary_search
{
	int binary_search(const vector<int>& array, int& lo,int& hi,int nvalue)
	{
		if(lo < hi)
		{
			int mid = (lo + hi) >> 1;
			(array[mid] <= nvalue) ? lo = mid + 1 : hi = mid;
			binary_search(array, lo, hi, nvalue);
		}

		return hi - 1;
	}

	void test_binary_search()
	{
		std::cout << "begin binary search" << std::endl;
		std::vector<int> test_array;
		for (int i = 0; i < 100;++i) test_array.push_back(rand());

		std::sort(test_array.begin(), test_array.end());

		int n = rand();
		int lo = 0;
		int hi = test_array.size();
		for (auto i : test_array) std::cout << i << std::endl;
		int nPos = binary_search(test_array, lo, hi, n);
		std::cout << "value = " << n << ", pos = " << nPos << endl;
	}
}

namespace mergesort
{
	void sort(std::vector<int>& array,int lo,int hi,int mid)
	{
		int lo_len = mid - lo;
		int hi_len = hi - mid;

		int* A = new int[lo_len];

		for (int i = 0; i < lo_len;++i) A[i] = array[lo + i];
		for (int i = 0, j = 0,k = 0; (i < lo_len || j < hi_len);)
		{
			if (A[i] <= array[mid + j]) array[lo + k++] = A[i++];
			else array[lo + k++] = array[mid + j++];
		}

		delete[] A;
	}

	void mergsort(std::vector<int>& array,int lo,int hi)
	{
		if (hi - lo < 2) return;
		int mi = (lo + hi) >> 2;
		mergsort(array, lo, mi);
		mergsort(array, mi, hi);

		sort(array, lo, hi, mi);
	}

	void test_mergesort()
	{

	}
}
int main()
{
	{
		//boost::timer::auto_cpu_timer t;
		////std::cout << __cplusplus << std::endl;
		//EventPool<CallBackParam>      event_pool;
		//TestCallBack test_cls;
		//event_pool.Attach(&test_cls, &TestCallBack::cb_func);
		//CallBackParam param;

		//CallBackParam* pParam = new CallBackParamChild();

		//event_pool.Invoke(&param);
		//event_pool.Detach(&test_cls, &TestCallBack::cb_func);
	}

	{
		std::cout << "pow2:" << std::endl;
		boost::timer::auto_cpu_timer t;
		std::cout << pow2(50) << std::endl;
	}

	{
		std::cout << "pow2_1:" << std::endl;
		boost::timer::auto_cpu_timer t;
		std::cout << pow2_1(50) << std::endl;
	}


	//std::vector<boost::flyweight<std::string>> dir;

	//char tmp[10];
	//memset(tmp, 0, sizeof(tmp));
	//for (int i = 0; i < 100000;++i)
	//{
	//	sprintf(tmp, "in%d", i % 100);
	//	dir.push_back(boost::flyweight<std::string>(tmp));
	//}

	{
		binary_search::test_binary_search();
	}

	
	return 0;
}
