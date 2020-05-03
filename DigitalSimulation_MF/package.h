#ifndef PACKAGE_H_
#define PACKAGE_H_

#include "logger.h"
#include "channel.h"
#include "package.h"


#include <functional>
#include <queue>

class WirelessNetwork;

class Package
{
public:
  typedef std::priority_queue<Package*, std::vector<Package*>, std::function<bool(Package*, Package*)>>Agenda;

  // enum class - representation of states
  enum class State { AppearanceInTheSystem, ChannelListening, Transmission, Retransmission, ACK, RemovalFromTheSystem };

  Package(unsigned int id_package, unsigned int id_station, unsigned __int64 time,
Logger* logger, WirelessNetwork* wireless_network, Agenda* agenda);
  ~Package();

  // functions
  void Execute();
  // relative false: sets the direct time, true: increments current process time
  void Activ(unsigned __int64 time, bool relative = true);
  bool IsTerminated();
  void SetTerminated();
  void IncrementNumberOfLR(Logger* logger);

  // get
  inline unsigned int GetPackageId() { return id_package_; }
  inline unsigned int GetStationId() { return id_station_; }
  inline unsigned int GetNumberOfLR() { return number_of_LR_; }
  inline unsigned int GetTimeCTPk() { return time_ctpk_; }
  inline unsigned __int64 GetTime() { return time_; }

  // set
  inline void SetPackageId(unsigned int id_package) { this->id_package_ = id_package; }
  inline void SetStationId(unsigned int id_station) { this->id_station_ = id_station; }
  inline void SetNumberOfLR(unsigned int number_of_LR) { this->number_of_LR_ = number_of_LR; }
  inline void SetTimeCTPk(unsigned __int64 time_ctpk) { this->time_ctpk_ = time_ctpk; }
  inline void SetTime(unsigned __int64 time) { time_ = time; }

private:
  unsigned int id_package_;
  unsigned int id_station_;
  unsigned int number_of_LR_ = 0; // packet retransmission number
  unsigned __int64 time_ctpk_; // random packet generation time (CTPk)
  unsigned __int64 time_ = 0; //time after which the process will start
  bool is_terminated_ = false;

  State state_ = State::AppearanceInTheSystem;

  WirelessNetwork* wireless_network_ = nullptr;
  Channel* channel_ = nullptr;
  Logger* logger_ = nullptr;
  Agenda* agenda_ = nullptr;
};
#endif