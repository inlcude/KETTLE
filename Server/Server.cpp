// Server.cpp : �������̨Ӧ�ó������ڵ㡣
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

