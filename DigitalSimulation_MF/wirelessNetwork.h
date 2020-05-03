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

  static const size_t generate_packet_max_time = 10;
  static const size_t transmission_max_time = 25;

  unsigned const int k_number_of_stations_ = 10; // number of transmitters and receivers

  std::vector<Transmitter*> transmitters_;
  std::vector<Receiver*> receivers_;

  //Package* GeneratePackage(Logger* logger, WirelessNetwork* wireless_network, unsigned int id_package, unsigned int id_station);
  Transmitter* GetTransmitters(int i);
  Receiver* GetReceivers(int i);
  Package* GetPackages(int i);
  Channel* GetChannel();

  bool GetChannelStatus();

  void SetPackages(Package* package); // add package to the vector
  void Init(Logger* logger); // take package from the buffer
  void GeneratePackage(Logger* logger, Package* package, unsigned int id_station);
  void StartTransmission(Logger* logger);
  void EndTransmission(Logger* logger);
  bool IsBufferEmpty() { return packages_.empty(); }
  Package* GetFirstPackage() { return packages_.front(); }
  size_t GetBufferSize() { return packages_.size(); }

private:
  std::vector<Package*> packages_;  // packages in buffer

  Transmitter* transmitter_ = nullptr;
  Logger* logger_ = nullptr;
  Channel* channel_ = nullptr;
};
#endif