#ifndef CHANNEL_H
#define CHANNEL_H

#include <vector>

#include "package.h"

class Channel
{
public:
  Channel();
  ~Channel();

  bool channel_occupancy_; // true/false - channel is busy/free
  bool collision_; // true - collision occurred
  std::vector<Package*> transmission_packages; // vector of transmission packages
};

#endif