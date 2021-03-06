#ifndef CHANNEL_H_
#define CHANNEL_H_

#include "logger.h"
#include "generators.h"

class Channel
{
public:
  Channel(Logger* logger, int seed_uniform);
  ~Channel();

  Generators* GetGeneratorTER();

  // functions
  void ChanceForTER(Logger* logger);

  // get
  bool GetChannelOccupancy();
  bool GetCollision();
  bool GetMorePackagesInChannel();
  // set
  void SetChannelOccupancy(bool channel_occupancy);
  void SetCollision(bool collision);
  void SetMorePackagesInBuffer(bool more_packages_in_channel);

private:
  bool channel_occupancy_ = false; // true/false - channel is busy/free
  bool packages_collision_ = false; // true - collision occurred
  bool more_packages_in_channel_ = false;

  Generators* uniform_generator_ = nullptr;
  Logger* logger_ = nullptr;
};

#endif