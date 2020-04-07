#ifndef BUFFER_H
#define BUFFER_H

#include <queue>

#include "Package.h"

class Buffer
{
public:
  Buffer();
  ~Buffer();

  std::queue<Package*> packages_in_buffer;  // queue of packages in buffer
};

#endif