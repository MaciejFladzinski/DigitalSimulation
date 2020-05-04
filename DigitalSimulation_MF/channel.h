#ifndef CHANNEL_H_
#define CHANNEL_H_

#include "logger.h"

class Channel
{
public:
  Channel(Logger* logger);
  ~Channel();

  // functions
  void ChanceForTER(Logger* logger);

  // get
  bool GetChannelOccupancy();
  bool GetCollision();

  // set
  void SetChannelOccupancy(bool channel_occupancy);
  void SetCollision(bool collision);

private:
  bool channel_occupancy_ = false; // true/false - channel is busy/free
  bool packages_collision_ = false; // true - collision occurred

  Logger* logger_ = nullptr;
};

#endif