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

int main()
{
	int32 a[] = {2,3,100,40,20,30,20,4004};
	float32 b[] = {1.4646,3.2341,3.45646453,4.13213,5.846456};
	double64 c[] = { 564351313.12313,51312.84641854,464651231.1231645,84632123.2184651,231684.846123 };
	int8* d[] = { "gwaefasfawe","2rfqwefasgaweg","fbaergaweg" ,"fbaegawfgasdf","bhwfgasefasfsd","fbaegasdas"};
	CVarList var;

	boost::progress_display pd(1000);
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
		++pd;
	}

	boost::timer t;
	std::cout << "max timespane:" << t.elapsed_max() / 3600 << "h" << std::endl;
	std::cout << "min timespane" << t.elapsed_min() << "s" << std::endl;
	std::cout << "now time elapsed:" << t.elapsed() << "s" << std::endl;
	{
		boost::progress_timer t2;
	}
	
	CVarList otherVar;
	printf("before other var size is %d\n", otherVar.GetSize());
	otherVar.Serialize(var.Serialize());
	printf("after other var size is %d\n", otherVar.GetSize());

	boost::gregorian::date d1;
	boost::gregorian::date d2(2010, 1, 1);
	boost::gregorian::date d3(2000, boost::gregorian::Jan, 1);
	boost::gregorian::date d4(d2);

	std::cout << boost::gregorian::to_simple_string(d2) << std::endl;

	boost::posix_time::time_duration timd_d;
	boost::posix_time::hours h(1);
	boost::posix_time::minutes m(10);
	boost::posix_time::seconds s(10);
	boost::posix_time::millisec ms(1);
	timd_d = h + m + s + ms;

	boost::scoped_ptr<boost::gregorian::date> date_ptr;
	boost::scoped_array<KETTLE::int32> PTR_ARRAY(new int(32));
	boost::shared_ptr<KETTLE::int32> PTR_SHARE;
	KETTLE::int32* pShare = new KETTLE::int32;
	PTR_SHARE.reset(pShare);
	printf("%d", PTR_SHARE.use_count());

	BOOST_TYPEOF(2.0 * 3) x = 2.0 * 3;
	BOOST_AUTO(y, 2 + 3);
	boost::optional<KETTLE::int32> A;
	boost::serialization::singleton<boost::gregorian::date> ts;

	MemTrack::MemoryDumpInfo::TrackDumpBlocks();
	MemTrack::MemoryDumpInfo::TrackListMemoryUsage();
	while (true)
	{

	}
	auto anum = 3;
    return 0;
}
