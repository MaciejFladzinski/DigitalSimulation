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

  std::vector<Transmitter*> GetTransmittersPtr() { return *transmitters_ptr_; }
  std::vector<Receiver*> GetReceiversPtr() { return *receivers_ptr_; }
  std::vector<Package*> GetPackagesPtr() { return *packages_ptr_; }

  // set
  void SetTransmitters(std::vector<Transmitter*> &transmitters) { transmitters_ = transmitters; }
  void SetReceivers(std::vector<Receiver*>& receivers) { receivers_ = receivers; }
  void SetPackages(std::vector<Package*>& packages) { packages_ = packages; }

  void SetTransmittersPtr(std::vector<Transmitter*> *transmitters_ptr) { transmitters_ptr_ = transmitters_ptr; }
  void SetReceiversPtr(std::vector<Receiver*> *receivers_ptr) { receivers_ptr_ = receivers_ptr; }
  void SetPackagesPtr(std::vector<Package*>* packages_ptr) { packages_ptr_ = packages_ptr; }

private:
  std::vector<Transmitter*> transmitters_; // vector of transmitters
  std::vector<Receiver*> receivers_; // vector of receivers
  std::vector<Package*> packages_; // vector of packages

  std::vector<Transmitter*> *transmitters_ptr_; // pointers
  std::vector<Receiver*> *receivers_ptr_; // pointers
  std::vector<Package*>* packages_ptr_; // pointers
};

#endif