// Server.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include"KETTLEPlatform.h"
#include"KettleAllocate.h"
#include "Profile.h"
#include "Acceptor.h"

using namespace KETTLE;
using namespace std;

int main(){

	KETTLE::Acceptor* acceptor = new Acceptor("0.0.0.0",9527);

	return 0;
}
