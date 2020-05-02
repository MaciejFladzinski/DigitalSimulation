#ifndef WIRELESSNETWORK_H_
#define WIRELESSNETWORK_H_

#include <vector>

#include "receiver.h"
#include "transmitter.h"
#include "package.h"
#include "channel.h"

class WirelessNetwork
{
public:
  WirelessNetwork(Logger *logger);
  ~WirelessNetwork();

  unsigned const int k_number_of_stations_ = 10; // number of transmitters and receivers

  std::vector<Transmitter*> transmitters_;
  std::vector<Receiver*> receivers_;

  Package* GeneratePackage(Logger* logger, WirelessNetwork* wireless_network, unsigned int id_package, unsigned int id_station);
  Transmitter* GetTransmitters(int i);
  Receiver* GetReceivers(int i);
  Package* GetPackages(int i);
  Channel* GetChannel();

  bool GetChannelStatus();

  void SetPackages(Package* package);

  // get
  inline int GetNumberOfPackages() { return number_of_packages_; }

  // set
  void SetNumberOfPackages(int number_of_packages) { number_of_packages_ = number_of_packages; }

private:
  std::vector<Package*> packages_;
  int number_of_packages_;
  Logger* logger_ = nullptr;
  Channel* channel_;
};
#endif