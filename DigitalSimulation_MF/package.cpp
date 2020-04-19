#include "package.h"

#include <cstdlib>
#include <iostream>

Package::Package(unsigned int id_, unsigned const __int64 time_)
{
  package_id_ = id_;
  time_ctpk_ = time_;
}

Package::~Package()
{
  
}

void Package::TimeCTPk()
{
  int ctpk = rand() % 10 + 1;  // random value <0;10>
  printf("CTPk time: %dms. \n", ctpk);
}
