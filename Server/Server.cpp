// Server.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include"SingltonTemplate.h"

class testclass :public Singleton<testclass>
{
public:
	void Invoke()
	{
		printf("abcd");
	}
};
int main()
{
	testclass::GetInstance()->Invoke();
    return 0;
}

