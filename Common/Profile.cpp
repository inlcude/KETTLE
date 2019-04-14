#include"Profile.h"

#include<iostream>

KETTLE::KettleProfile::KettleProfile(){
    startTime = clock();
}

KETTLE::KettleProfile::~KettleProfile(){
    clock_t endTime = clock();
    clock_t during = endTime - startTime;
    
    std::cout << "use time: " << during << std::endl;
}