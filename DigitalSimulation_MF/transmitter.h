#ifndef TRANSMITTER_H_
#define TRANSMITTER_H_

#include <vector>

#include "package.h"
#include "channel.h"
#include "logger.h"

class Transmitter
{
public:
  Transmitter(unsigned int id_, Logger* logger);
  ~Transmitter();

  // functions
  void Wait(Logger* logger); // delay 0,5ms
  void CTPkTime(Logger* logger); // transmission time
  void CRPTime(Logger* logger); // time before start retransmission
  void CheckDIFSTime(Logger* logger); // DIFS > 4ms ? true : false
  void CheckTransmissionPackageTime(Logger* logger); // CTPk + CTIZ,   CTIZ = 1ms
  void AddPackageSuccessfullySent(Logger* logger);  // Add 1 package successfully sent

  // const... = 0 -> it's only for definition const variable, it will be changed soon...
  unsigned const __int64 ctiz_time_ = 1;  // ACK transmission time (CTIZ = 1ms)

  bool GetTransmissionOfAnotherPackage();
  unsigned int GetPackagesSuccessfullySent();

  void SetTransmissionOfAnotherPackage(bool transmission_of_another_package);

  // get
  inline unsigned int GetTransmitterId() { return transmitter_id_; }
  inline unsigned int GetPackagesLost() { return packages_lost_; }
  inline unsigned __int64 GetTimeOfChannelOccupancy() { return time_of_channel_occupancy_; }
  inline unsigned __int64 GetTimeFromStartTransmission() { return time_from_start_transmission_; }
  inline unsigned __int64 GetTimeCrp() { return time_crp_; }
  inline bool GetCorrectReceptionAck() { return correct_reception_ack_; }
  inline bool GetTransmissionPermission() { return transmission_permission_; }
  
  // set
  inline void SetTransmitterId(unsigned int transmitter_id)
  {
    this->transmitter_id_ = transmitter_id;
  }
  inline void SetPackagesLost(unsigned int packages_lost)
  {
    this->packages_lost_ = packages_lost;
  }
  inline void SetTimeOfChannelOccupancy(unsigned __int64 time_of_channel_occupancy)
  {
    this->time_of_channel_occupancy_ = time_of_channel_occupancy;
  }
  inline void SetTimeFromStartTransmission(unsigned __int64 time_of_start_transmission)
  {
    this->time_from_start_transmission_ = time_of_start_transmission;
  }
  inline void SetTimeCrp(unsigned __int64 time_crp)
  {
    this->time_crp_ = time_crp;
  }
  inline void SetCorrectReceptionAck(bool correct_reception_ack)
  {
    this->correct_reception_ack_ = correct_reception_ack;
  }
  inline void SetTransmissionPermission(bool transmission_permission)
  {
    this->transmission_permission_ = transmission_permission;
  }

private:
  unsigned int transmitter_id_;  // transmitter number
  unsigned int packages_successfully_sent_ = 0;  // number of packages successfully sent
  unsigned int packages_lost_ = 0; // number of packages lost
  unsigned __int64 time_of_channel_occupancy_;  // time of channel occupancy
  unsigned __int64 time_from_start_transmission_; // time od package transmission and ACK (if all is correct): CTPk + CTIZ
  unsigned __int64 time_crp_;  // random time after which retransmissions can be made
  bool correct_reception_ack_ = false;  // true - ACK take back in less time than (CGPk + CTIZ)
  bool transmission_permission_;  // true - permission to transmit the packet
  bool transmission_of_another_package_ = false; // protection against sending more than one package by transmitter

  Logger* logger_ = nullptr;
};

#endif