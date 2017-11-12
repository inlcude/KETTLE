// Server.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include"Platform.h"
#include"SingltonTemplate.h"
#include"TemplateDelegate.h"
#include"TemplateFunctions.h"
#include"TcpSocket.h"

#include"VarList.h"

#include<iostream>
#include<boost/shared_ptr.hpp>
#include<boost/timer.hpp>
#include<boost/progress.hpp>
using namespace KETTLE;
int main()
{
	int32 a[] = {2,3,100,40,20,30,20,4004};
	float32 b[] = {1.4646,3.2341,3.45646453,4.13213,5.846456};
	double64 c[] = { 564351313.12313,51312.84641854,464651231.1231645,84632123.2184651,231684.846123 };
	int8* d[] = { "gwaefasfawe","2rfqwefasgaweg","fbaergaweg" ,"fbaegawfgasdf","bhwfgasefasfsd","fbaegasdas"};
	CVarList var;

	for (int32 i = 0; i < 1000; ++i)
	{
		int32 index = rand();
		int32 len = getArrayLen(a);
		index = index % len;
		var << a[index];

		index = rand();
		len = getArrayLen(b);
		index = index % len;
		var << b[index];

		index = rand();
		len = getArrayLen(c);
		index = index % len;
		var << c[index];

		index = rand();
		len = getArrayLen(d);
		index = index % len;
		var << d[index];
	}

	boost::timer t;
	std::cout << "max timespane:" << t.elapsed_max() / 3600 << "h" << std::endl;
	std::cout << "min timespane" << t.elapsed_min() << "s" << std::endl;
	std::cout << "now time elapsed:" << t.elapsed() << "s" << std::endl;
	{
		boost::progress_timer t2;
	}
	
	boost::shared_ptr<CVarList> ptr;
	ptr.reset(&var);
	printf("var size is %d\n", ptr->GetSize());
	CVarList otherVar;
	printf("before other var size is %d\n", otherVar.GetSize());
	otherVar.Serialize(var.Serialize());
	printf("after other var size is %d\n", otherVar.GetSize());
	
    return 0;
}
