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

using namespace KETTLE;

struct TestMemTrack
{
	int     a;
	float   b;
	double  c;
	TestMemTrack()
	{
		a = 1;
		b = 2.0f;
		c = 3.1;
	}
};

class CallBackParam
{
public:
private:
	int a;
};

class TestClass
{
public:
	void TestFunction(CallBackParam* param)
	{
		std::cout << "call back" << std::endl;
	}
};

int main()
{
	EventPool<CallBackParam> pool;
	TestClass testclass;
	CallBackParam param;
	pool.Attach(&testclass, &(TestClass::TestFunction));

	pool.Invoke(&param);

	return 0;
}
