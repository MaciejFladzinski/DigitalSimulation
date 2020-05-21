#ifndef PACKAGE_H_
#define PACKAGE_H_

#include "logger.h"
#include "channel.h"
#include "package.h"

#include <functional>
#include <queue>

#include "simulation.h"

class Simulation;
class WirelessNetwork;

class Package
{
public:
  typedef std::priority_queue<Package*, std::vector<Package*>, std::function<bool(Package*, Package*)>>Agenda;

  // enum class - representation of states
  enum class State {
    AppearanceInTheSystem, ChannelListening, Transmission, Collision, ReceivePackage, Retransmission, ACK,
    ReceiveACK, RemovalFromTheSystem
  };

  Package(unsigned int id_package, unsigned int id_station, size_t time,
    Logger* logger, WirelessNetwork* wireless_network, Agenda* agenda, Simulation* simulation);

  Package(unsigned int id_package, unsigned int id_station, size_t time);

  ~Package();

  // functions
  void Execute();
  // relative false: sets the direct time, true: increments current process time
  void Activ(size_t time, bool relative = true);

  Generators* GetGenerators();

  void IncrementNumberOfLR(Logger* logger);
  void GenerateCTPkTime(Logger* logger);

  void SaveNumberOfLR();

  void SaveTimeOfAddedToBuffer();
  void SaveTimeSuccessfullySentPackage();
  void SaveTimeRemoveFromBuffer();
  void SaveWaitingTime();
  void SaveThroughputOfSystem();
  void SavePackagesSuccessfullySent();
  void SavePackagesLost();

  void PackageDelayTime();
  void IncrementCounter();
  void AddSumOfAllRetransmissions();

  // get
  inline unsigned int GetPackageId() { return id_package_; }
  inline unsigned int GetStationId() { return id_station_; }
  inline unsigned int GetNumberOfLR() { return number_of_LR_; }
  inline size_t GetTimeCTPk() { return ctpk_time_; }
  inline size_t GetTime() { return time_; }
  bool GetIsTerminated();
  inline size_t GetTimeAddedToBuffer() { return time_added_to_buffer_; }
  inline size_t GetTimeSuccessfullySentPackage() { return time_successfully_sent_package_; }
  inline size_t GetTimeRemoveFromBuffer() { return time_remove_from_buffer_; }
  inline int GetCounter() { return counter_; }
  inline int GetSumOfAllRetransmissions() { return sum_of_all_retransmissions_; }
  inline size_t GetPackageDelayTime() { return package_delay_time_; }
  inline size_t GetPackageWaitingTime() { return package_waiting_time_; }
  inline size_t GetSystemThroughput() { return system_throughput_; }

  // set
  inline void SetPackageId(unsigned int id_package);
  inline void SetStationId(unsigned int id_station);
  inline void SetNumberOfLR(unsigned int number_of_LR);
  inline void SetTimeCTPk(size_t ctpk_time);
  inline void SetTime(size_t time);
  void SetTerminated();
  inline void SetTimeAddedToBuffer(size_t time_added_to_buffer)
  {
    this->time_added_to_buffer_ = time_added_to_buffer;
  }
  inline void SetTimeSuccessfullySentPackage(size_t time_successfully_sent_package)
  {
    this->time_successfully_sent_package_ = time_successfully_sent_package;
  }
  inline void SetTimeRemoveFromBuffer(size_t time_remove_from_buffer)
  {
    this->time_remove_from_buffer_ = time_remove_from_buffer;
  }
  inline void SetCounter(int counter)
  {
    counter_ = counter;
  }
  inline void SetSumOfAllRetransmissions(int sum_of_all_retransmissions)
  {
    sum_of_all_retransmissions_ = sum_of_all_retransmissions;
  }
  inline void SetPackageDelayTime(size_t package_delay_time)
  {
    this->package_delay_time_ = package_delay_time;
  }
  inline void SetPackageWaitingTime(size_t package_waiting_time)
  {
    this->package_waiting_time_ = package_waiting_time;
  }
  inline void SetSystemThroughput(size_t system_throughput)
  {
    this->system_throughput_ = system_throughput;
  }

private:
  unsigned int id_package_;
  unsigned int id_station_;
  unsigned int number_of_LR_ = 0; // packet retransmission number
  size_t ctpk_time_ = 0; // random packet generation time (CTPk)
  size_t time_; //time after which the process will start
  size_t time_added_to_buffer_ = 0; // time, when package is added to the buffer
  size_t time_successfully_sent_package_ = 0; // time, when package is successfully sent
  size_t time_remove_from_buffer_ = 0; // time, when package is remove from buffer
  bool is_terminated_ = false;
  int counter_ = 0; // package counter with quantity of LR
  int sum_of_all_retransmissions_ = 0;
  size_t package_delay_time_ = 0;
  size_t package_waiting_time_ = 0;
  size_t system_throughput_ = 0;


  State state_ = State::AppearanceInTheSystem;

  Simulation* simulation_ = nullptr;
  WirelessNetwork* wireless_network_ = nullptr;
  Logger* logger_ = nullptr;
  Agenda* agenda_ = nullptr;
};
#endif