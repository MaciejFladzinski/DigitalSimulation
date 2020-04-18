#include "process.h"

Process::Process(size_t time) : time_(time)
{
  
}

Process::~Process()
{
  
}

void Process::Activ(size_t time)  // when the process will activate
{
  time_ += time;
}