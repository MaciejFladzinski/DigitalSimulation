#ifndef WIRELESSNETWORK_H_
#define WIRELESSNETWORK_H_

#include <vector>

#include "receiver.h"
#include "transmitter.h"
#include "channel.h"
#include "package.h"

class Package;
class Transmitter;

class WirelessNetwork
{
public:
  WirelessNetwork(Logger *logger);
  ~WirelessNetwork();

  static const size_t generate_packet_max_time = 10;
  unsigned const int k_number_of_stations_ = 10; // number of transmitters and receivers
  
  Transmitter* GetTransmitters(int i);
  Receiver* GetReceivers(int i);
  Package* GetPackages(int i);
  Channel* GetChannel();

  bool GetChannelStatus();
  double GetLambda();

  void AddPackages(Package* package); // add package to the vector
  void Init(Logger* logger); // take package from the buffer
  void GeneratePackage(Logger* logger, Package* package, Transmitter* transmitter, unsigned int id_station);
  void StartTransmission(Logger* logger);
  void EndTransmission(Logger* logger);
  bool IsBufferEmpty() { return packages_.empty(); }
  Package* GetFirstPackage() { return packages_.front(); }
  size_t GetBufferSize() { return packages_.size(); }
  void IncrementCounterOfPackagesSuccessfullySent() { ++counter_of_packages_successfully_sent_; }

  int GetCounterOfPackagesSuccessfullySent() { return counter_of_packages_successfully_sent_; }
  void SetCounterOfPackagesSuccessfullySent(int counter_of_packages_successfully_sent)
  {
    counter_of_packages_successfully_sent_ = counter_of_packages_successfully_sent;
  }

private:
  int counter_of_packages_successfully_sent_ = 0;
  double lambda = 0.08;

  std::vector<Transmitter*> transmitters_;
  std::vector<Receiver*> receivers_;
  std::vector<Package*> packages_;  // packages in channel

  Transmitter* transmitter_ = nullptr;
  Logger* logger_ = nullptr;
  Channel* channel_ = nullptr;
};
#endif