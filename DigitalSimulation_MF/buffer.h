#ifndef BUFFER_H_
#define BUFFER_H_

#include <queue>

#include "package.h"

class Buffer
{
public:
  Buffer();
  ~Buffer();

private:
  std::queue<Package*> packages_in_buffer;  // queue of packages in buffer
};

#endif