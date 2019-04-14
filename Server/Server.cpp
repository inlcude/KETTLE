// Server.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include"KETTLEPlatform.h"
#include"KettleAllocate.h"
#include "Profile.h"

using namespace KETTLE;
using namespace std;

#define __USE_MEMPOOL__ 1

int main()
{
	{
		std::vector<size_t> allocateSize{8,16,32,64,128,256,512,1024};

		KettleProfile profile;
		for(int i = 0; i < 1000000;++i){
			size_t nSize = random() % 1025;
			if(0 == nSize)
				continue;
			char* pMemopry = new char[nSize];
		}
	}

	return 0;
}
