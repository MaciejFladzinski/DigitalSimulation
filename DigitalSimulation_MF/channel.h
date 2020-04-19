#ifndef CHANNEL_H_
#define CHANNEL_H_

#include <vector>

#include "package.h"

class Channel
{
public:
  Channel();
  ~Channel();

  // get
  inline bool GetChannelOccupancy() { return channel_occupancy_; }
  inline bool GetCollision() { return packages_collision_; }

  // set
  inline void SetChannelOccupancy(bool channel_occupancy) { this->channel_occupancy_ = channel_occupancy; }
  inline void SetCollision(bool collision) { this->packages_collision_ = collision; }

private:
  bool channel_occupancy_ = false; // true/false - channel is busy/free
  bool packages_collision_; // true - collision occurred

  std::vector<Package*> transmitted_packages;  // vector of transmitted packages
};

#endif