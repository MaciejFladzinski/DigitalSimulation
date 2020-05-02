#ifndef PACKAGE_H_
#define PACKAGE_H_

#include "logger.h"
#include "channel.h"
#include "package.h"

class WirelessNetwork;

class Package
{
public:
  Package(unsigned int id_package, unsigned int id_station, Logger* logger, WirelessNetwork* wireless_network);
  ~Package();

  // enum class - representation of states
  enum class State { ChannelListening, Transmission, Retransmission, ACK, RemovalFromTheSystem };

  // functions
  void Execute();
  void Activ(unsigned __int64 time); //function (process activation time)
  void IncrementNumberOfLR(Logger* logger);

  // get
  inline unsigned int GetPackageId() { return id_package_; }
  inline unsigned int GetStationId() { return id_station_; }
  inline unsigned int GetNumberOfLR() { return number_of_LR_; }
  inline unsigned int GetTimeCTPk() { return time_ctpk_; }
  inline unsigned __int64 GetActivationTime() { return activation_time_; }

  // set
  inline void SetPackageId(unsigned int id_package) { this->id_package_ = id_package; }
  inline void SetStationId(unsigned int id_station) { this->id_station_ = id_station; }
  inline void SetNumberOfLR(unsigned int number_of_LR) { this->number_of_LR_ = number_of_LR; }
  inline void SetTimeCTPk(unsigned __int64 time_ctpk) { this->time_ctpk_ = time_ctpk; }
  void SetActivationTime(unsigned __int64 activation_time) { activation_time_ = activation_time; }

protected:
  bool is_terminated_;

private:
  unsigned int id_package_;
  unsigned int id_station_;
  unsigned int number_of_LR_ = 0; // packet retransmission number
  unsigned __int64 time_ctpk_; // random packet generation time (CTPk)
  unsigned __int64 activation_time_ = 0; //time after which the process will start

  State state_ = State::ChannelListening;

  WirelessNetwork* wireless_network_;
  Channel* channel_;
  Logger* logger_ = nullptr;
};
#endif