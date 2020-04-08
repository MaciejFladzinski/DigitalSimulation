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
  inline bool GetCollision() { return collision_; }

  // set
  inline void SetChannelOccupancy(bool channel_occupancy) { this->channel_occupancy_ = channel_occupancy; }
  inline void SetCollision(bool collision) { this->collision_ = collision; }

private:
  bool channel_occupancy_; // true/false - channel is busy/free
  bool collision_; // true - collision occurred

  std::vector<Package*> transmission_packages; // vector of transmission packages
};

#endif