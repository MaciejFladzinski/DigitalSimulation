#ifndef CHANNEL_H_
#define CHANNEL_H_

#include <vector>

#include "logger.h"

class Package;

class Channel
{
public:
  Channel(Logger* logger);
  ~Channel();

  // get
  bool GetChannelOccupancy();
  bool GetCollision();
  Package* GetTransmittedPackages(int i);

  // set
  void SetChannelOccupancy(bool channel_occupancy);
  void SetCollision(bool collision);
  void SetTransmittedPackages(Package* package);

private:
  bool channel_occupancy_ = false; // true/false - channel is busy/free
  bool packages_collision_ = false; // true - collision occurred

  Logger* logger_ = nullptr;
  std::vector<Package*> transmitted_packages_;  // vector of transmitted packages
};

#endif