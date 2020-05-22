#ifndef TRANSMITTER_H_
#define TRANSMITTER_H_

#include <vector>

#include "package.h"
#include "channel.h"
#include "generators.h"
#include "logger.h"

class Package;

class Transmitter
{
public:
  Transmitter(unsigned int id_, Logger* logger, int uniform_seed, int exp_seed, int r_seed);
  ~Transmitter();

  // functions
  void GenerateCRPTime(Logger* logger, size_t ctpk, unsigned int number_of_LR); // time before start retransmission
  void AddPackageSuccessfullySent(Logger* logger);  // Add 1 package successfully sent
  void AddPackageLost(Logger* logger);  // Add 1 package lost
  void IncTimeOfChannelListenning(Logger* logger);  // Add 0,5ms in channel listenning

  Package* GetFirstPackageInTX();
  void RemoveFirstPackageInTX();
  bool IsBufferInTXEmpty();


  Generators* GetUniformGenerator();
  Generators* GetExpGenerator();
  Generators* GetRGenerator();

  void AddPackageInTX(Package* package);

  void CalculationMaxPackageErrorRate();
  void CalculationAverageNumberOfLR();
  void CalculationAverageOfPackagesDelayTime();
  void CalculationAverageOfPackagesWaitingTime();
  void CalculationAverageOfSystemThroughput();

  // const... = 0 -> it's only for definition const variable, it will be changed soon...
  const size_t ctiz_time_ = 10;  // ACK transmission time (CTIZ = 1ms)
  const size_t difs_time_ = 40; // checking channel time (DIFS = 4ms)

  // get
  inline unsigned int GetTransmitterId() { return transmitter_id_; }
  inline unsigned int GetPackagesLost();
  inline unsigned int GetPackagesSuccessfullySent();
  inline size_t GetTimeOfChannelListenning() { return time_of_channel_listenning_; }
  inline size_t GetTimeOfChannelOccupancy() { return time_of_channel_occupancy_; }
  inline size_t GetTimeCrp() { return time_crp_; }
  inline bool GetCorrectReceptionAck() { return correct_reception_ack_; }
  inline double GetMaxPackageErrorRate() { return max_package_error_rate_; }
  inline double GetPackageErrorRate() { return package_error_rate_; }
  inline double GetAverageNumberOfLR() { return average_number_of_LR_; }
  inline double GetSumOfAllLR() { return sum_of_all_LR_; }
  inline size_t GetAverageOfPackagesDelayTime() { return average_of_packages_delay_time_; }
  inline size_t GetSumOfAllPackagesDelayTime() { return sum_of_all_packages_delay_time_; }
  inline size_t GetAverageOfPackagesWaitingTime() { return average_of_packages_waiting_time_; }
  inline size_t GetSumOfAllPackagesWaitingTime() { return sum_of_all_packages_waiting_time_; }
  inline size_t GetAverageOfSystemThroughput() { return average_of_system_throughput_; }

  // set
  inline void SetTransmitterId(unsigned int transmitter_id)
  {
    this->transmitter_id_ = transmitter_id;
  }
  inline void SetPackagesLost(unsigned int packages_lost)
  {
    this->packages_lost_ = packages_lost;
  }
  inline void SetPackagesSuccessfullySent(unsigned int packages_successfully_sent)
  {
    this->packages_successfully_sent_ = packages_successfully_sent;
  }
  inline void SetTimeOfChannelOccupancy(size_t time_of_channel_occupancy)
  {
    this->time_of_channel_occupancy_ = time_of_channel_occupancy;
  }
  inline void SetTimeCrp(size_t time_crp)
  {
    this->time_crp_ = time_crp;
  }
  inline void SetCorrectReceptionAck(bool correct_reception_ack)
  {
    this->correct_reception_ack_ = correct_reception_ack;
  }
  inline void SetTimeOfChannelListenning(size_t time_of_channel_listenning)
  {
    this->time_of_channel_listenning_ = time_of_channel_listenning;
  }
  inline void SetMaxPackageErrorRate(double max_package_error_rate)
  {
    max_package_error_rate_ = max_package_error_rate;
  }
  inline void SetPackageErrorRate(double package_error_rate)
  {
    package_error_rate_ = package_error_rate;
  }
  inline void SetAverageNumberOfLR(double average_number_of_LR)
  {
    average_number_of_LR_ = average_number_of_LR;
  }
  inline void SetSumOfAllLR(double sum_of_all_LR)
  {
    sum_of_all_LR_ = sum_of_all_LR;
  }
  inline void SetAverageOfPackagesDelayTime(size_t average_of_packages_delay_time)
  {
    average_of_packages_delay_time_ = average_of_packages_delay_time;
  }
  inline void SetSumOfAllPackagesDelayTime(size_t sum_of_all_packages_delay_time)
  {
    sum_of_all_packages_delay_time_ = sum_of_all_packages_delay_time;
  }
  inline void SetAverageOfPackagesWaitingTime(size_t average_of_packages_waiting_time)
  {
    average_of_packages_waiting_time_ = average_of_packages_waiting_time;
  }
  inline void SetSumOfAllPackagesWaitingTime(size_t sum_of_all_packages_waiting_time)
  {
    sum_of_all_packages_waiting_time_ = sum_of_all_packages_waiting_time;
  }
  inline void SetAverageOfSystemThroughput(size_t average_of_system_throughput)
  {
    average_of_system_throughput_ = average_of_system_throughput;
  }

private:
  unsigned int transmitter_id_ = 0;  // transmitter number
  unsigned int packages_successfully_sent_ = 0;  // number of packages successfully sent
  unsigned int packages_lost_ = 0; // number of packages lost
  size_t time_of_channel_listenning_ = 0; // time of checking channel
  size_t time_of_channel_occupancy_;  // time of channel occupancy
  size_t time_crp_;  // random time after which retransmissions can be made
  bool correct_reception_ack_ = false;  // true - ACK take back in less time than (CGPk + CTIZ)

  double package_error_rate_ = 0;
  double max_package_error_rate_ = 0;

  int sum_of_all_LR_ = 0;
  double average_number_of_LR_ = 0;

  size_t sum_of_all_packages_delay_time_ = 0;
  size_t average_of_packages_delay_time_ = 0;

  size_t sum_of_all_packages_waiting_time_ = 0;
  size_t average_of_packages_waiting_time_ = 0;

  size_t average_of_system_throughput_ = 0; // average of system throughput in one station

  std::queue<Package*> packages_in_TX_; // packages in buffer (in transmitter)

  Generators* uniform_generator_ = nullptr;
  Generators* exp_generator_ = nullptr;
  Generators* r_generator_ = nullptr;
  Logger* logger_ = nullptr;
};

#endif