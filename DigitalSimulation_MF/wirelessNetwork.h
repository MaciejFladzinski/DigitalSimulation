#ifndef WIRELESSNETWORK_H_
#define WIRELESSNETWORK_H_

#include<vector>

#include "receiver.h"
#include "transmitter.h"

class WirelessNetwork
{
public:
  WirelessNetwork();
  ~WirelessNetwork();

  unsigned const int k_number_of_stations_ = 10; // number of transmitters and receivers

private:
  std::vector<Transmitter*> transmitters; // vector of transmitters
  std::vector<Receiver*> receivers; // vector of receivers
};

#endif