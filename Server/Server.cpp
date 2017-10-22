// Server.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include"SingltonTemplate.h"
#include"TemplateDelegate.h"

#include"VarList.h"
using namespace KETTLE;
class testclass
{
public:
	void Invoke(int* param)
	{
		printf("abcd");
	}
};


int main()
{
	EventPool<int>     pool;
	testclass clas_obj;
	pool.Attach<testclass>(&clas_obj, &testclass::Invoke);

	int a = 0;
	pool.Invoke(&a);

	CVarList var;
	
    return 0;
}

