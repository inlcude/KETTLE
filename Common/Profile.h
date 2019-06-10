#ifndef __PROFILE_H__
#define __PROFILE_H__

#include<time.h>
namespace KETTLE{
class KettleProfile{
public:
    KettleProfile();
    ~KettleProfile();
private:
    clock_t startTime;
};
}
#endif