#ifndef WIRELESSNETWORK_H_
#define WIRELESSNETWORK_H_

#include <vector>

#include "receiver.h"
#include "transmitter.h"

class WirelessNetwork
{
public:
  WirelessNetwork();
  ~WirelessNetwork();

  unsigned const int k_number_of_stations_ = 10; // number of transmitters and receivers
  
  // get
  std::vector<Transmitter*> GetTransmitters() { return transmitters_; }
  std::vector<Receiver*> GetReceivers() { return receivers_; }

  // set
  void SetTransmitters(std::vector<Transmitter*> &transmitters) { transmitters_ = transmitters; }
  void SetReceivers(std::vector<Receiver*>& receivers) { receivers_ = receivers; }

private:
  std::vector<Transmitter*> transmitters_; // vector of transmitters
  std::vector<Receiver*> receivers_; // vector of receivers
};

#endif