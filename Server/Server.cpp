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

#include<iostream>
#include<boost/shared_ptr.hpp>
#include<boost/timer.hpp>
#include<boost/progress.hpp>
#include<boost/date_time/gregorian/gregorian.hpp>
#include<boost/date_time/posix_time/posix_time.hpp>
#include<boost/smart_ptr.hpp>
#include<boost/optional.hpp>
#include<boost/typeof/typeof.hpp>
#include<boost/typeof/decltype.hpp>
#include<boost/pool/singleton_pool.hpp>
#include<boost/serialization/singleton.hpp>

#include<map>
#include<string>

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

int main()
{
	std::cout << __cplusplus << std::endl;
	EventPool<CallBackParam>      event_pool;
	TestCallBack test_cls;
	event_pool.Attach(&test_cls, &TestCallBack::cb_func);
	CallBackParam param;

	CallBackParam* pParam = new CallBackParamChild();

	event_pool.Invoke(&param);
	event_pool.Detach(&test_cls, &TestCallBack::cb_func);

	return 0;
}
