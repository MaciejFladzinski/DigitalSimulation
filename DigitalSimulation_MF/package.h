#ifndef PACKAGE_H_
#define PACKAGE_H_

#include "logger.h"
#include "channel.h"
#include "package.h"

#include <functional>
#include <queue>

#include "simulation.h"

class WirelessNetwork;

class Package
{
public:
  typedef std::priority_queue<Package*, std::vector<Package*>, std::function<bool(Package*, Package*)>>Agenda;

  // enum class - representation of states
  enum class State { AppearanceInTheSystem, ChannelListening, Transmission, Retransmission, ACK, RemovalFromTheSystem };

  Package(unsigned int id_package, unsigned int id_station, size_t time,
Logger* logger, WirelessNetwork* wireless_network, Agenda* agenda);

  Package(unsigned int id_package, unsigned int id_station, size_t time);

  ~Package();

  // functions
  void Execute();
  // relative false: sets the direct time, true: increments current process time
  void Activ(size_t time, bool relative = true);

  void IncrementNumberOfLR(Logger* logger);
  void GenerateCTPkTime(Logger* logger);

  // get
  inline unsigned int GetPackageId() { return id_package_; }
  inline unsigned int GetStationId() { return id_station_; }
  inline unsigned int GetNumberOfLR() { return number_of_LR_; }
  inline size_t GetTimeCTPk() { return ctpk_time_; }
  inline size_t GetTime() { return time_; }
  bool GetIsTerminated();

  // set
  inline void SetPackageId(unsigned int id_package);
  inline void SetStationId(unsigned int id_station);
  inline void SetNumberOfLR(unsigned int number_of_LR);
  inline void SetTimeCTPk(size_t ctpk_time);
  inline void SetTime(size_t time);
  void SetTerminated();

private:
  unsigned int id_package_;
  unsigned int id_station_;
  unsigned int number_of_LR_ = 0; // packet retransmission number
  size_t ctpk_time_ = 0; // random packet generation time (CTPk)
  size_t time_; //time after which the process will start
  bool is_terminated_ = false;

  State state_ = State::AppearanceInTheSystem;

  WirelessNetwork* wireless_network_ = nullptr;
  Logger* logger_ = nullptr;
  Agenda* agenda_ = nullptr;
};
#endif