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