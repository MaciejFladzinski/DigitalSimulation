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
  std::vector<Package*> GetPackages() { return packages_; }
  inline int GetNumberOfPackages() { return number_of_packages_; }

  // set
  void SetTransmitters(std::vector<Transmitter*> transmitters_ptr) { transmitters_ = transmitters_ptr; }
  void SetReceivers(std::vector<Receiver*> receivers_ptr) { receivers_ = receivers_ptr; }
  void SetPackages(std::vector<Package*> packages_ptr) { packages_ = packages_ptr; }
  void SetNumberOfPackages(int number_of_packages) { number_of_packages_ = number_of_packages; }

private:
  std::vector<Transmitter*> transmitters_;
  std::vector<Receiver*> receivers_;
  std::vector<Package*> packages_;
  int number_of_packages_;
};

#endif