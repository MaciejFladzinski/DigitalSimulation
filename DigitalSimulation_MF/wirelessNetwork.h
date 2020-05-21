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
  WirelessNetwork(Logger* logger);
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

  void TotalMaxPackageErrorRate();
  void TotalNumberOfPackagesSuccessfullySent();
  void TotalNumberOfPackagesLost();
  void TotalPackageErrorRate();
  void TotalAverageNumberOfLR();
  void TotalAverageOfPackagesDelayTime();
  void TotalAverageOfPackagesWaitingTime();
  void TotalAverageOfSystemThroughput();

  void TotalStatistics(Logger* logger);

  // get
  inline int GetCounterOfPackagesSuccessfullySent() { return counter_of_packages_successfully_sent_; }
  inline double GetTotalMaxPackageErrorRate() { return total_max_package_error_rate_; }
  inline int GetTotalNumberOfPackagesSuccessfullySent() { return total_number_of_packages_successfully_sent_; }
  inline int GetTotalNumberOfPackagesLost() { return total_number_of_packages_lost_; }
  inline double GetTotalPackageErrorRate() { return total_package_error_rate_; }
  inline double GetTotalAverageNumberOfLR() { return total_average_number_or_LR_; }
  inline size_t GetTotalAverageOfPackagesDelayTime() { return total_average_of_packages_delay_time_; }
  inline size_t GetTotalAverageOfPackagesWaitingTime() { return total_average_of_packages_waiting_time_; }
  inline size_t GetTotalAverageOfSystemThroughput() { return total_average_of_system_throughput_; }

  // set
  void SetCounterOfPackagesSuccessfullySent(int counter_of_packages_successfully_sent)
  {
    counter_of_packages_successfully_sent_ = counter_of_packages_successfully_sent;
  }
  inline void SetTotalMaxPackageErrorRate(double total_max_package_error_rate)
  {
    total_max_package_error_rate_ = total_max_package_error_rate;
  }
  inline void SetTotalNumberOfPackagesSuccessfullySent(int total_number_of_packages_successfully_sent)
  {
    total_number_of_packages_successfully_sent_ = total_number_of_packages_successfully_sent;
  }
  inline void SetTotalNumberOfPackagesLost(int total_number_of_packages_lost)
  {
    total_number_of_packages_lost_ = total_number_of_packages_lost;
  }
  inline void SetTotalPackageErrorRate(double total_package_error_rate)
  {
    total_package_error_rate_ = total_package_error_rate;
  }
  inline void SetTotalAverageNumberOfLR(double total_average_number_or_LR)
  {
    total_average_number_or_LR_ = total_average_number_or_LR;
  }
  inline void SetTotalAverageOfPackagesDelayTime(size_t total_average_of_packages_delay_time)
  {
    total_average_of_packages_delay_time_ = total_average_of_packages_delay_time;
  }
  inline void SetTotalAverageOfPackagesWaitingTime(size_t total_average_of_packages_waiting_time)
  {
    total_average_of_packages_waiting_time_ = total_average_of_packages_waiting_time;
  }
  inline void SetTotalAverageOfSystemThroughput(size_t total_average_of_system_throughput)
  {
    total_average_of_system_throughput_ = total_average_of_system_throughput;
  }

private:
  int counter_of_packages_successfully_sent_ = 0;
  double lambda = 0.08;

  double total_max_package_error_rate_ = 0;
  int total_number_of_packages_successfully_sent_ = 0;
  int total_number_of_packages_lost_ = 0;
  double total_package_error_rate_ = 0;
  double total_average_number_or_LR_ = 0;
  size_t total_average_of_packages_delay_time_ = 0;
  size_t total_average_of_packages_waiting_time_ = 0;
  size_t total_average_of_system_throughput_ = 0; // average of system throughput in one station

  std::vector<Transmitter*> transmitters_;
  std::vector<Receiver*> receivers_;
  std::vector<Package*> packages_;  // packages in channel

  Transmitter* transmitter_ = nullptr;
  Logger* logger_ = nullptr;
  Channel* channel_ = nullptr;
};
#endif