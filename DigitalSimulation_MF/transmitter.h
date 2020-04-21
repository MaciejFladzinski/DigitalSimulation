#ifndef TRANSMITTER_H_
#define TRANSMITTER_H_

#include <vector>

#include "package.h"

class Transmitter
{
public:
  //constructor(id number, queue of packages in buffer)
  Transmitter(unsigned int id_);
  ~Transmitter();

  // functions
  void GeneratePackage();
  void StartTransmission();

  // const... = 0 -> it's only for definition const variable, it will be changed soon...
  unsigned const __int64 time_of_ctiz_ = 0;  // ACK transmission time

  // get
  inline unsigned int GetTransmitterId() { return transmitter_id_; }
  inline unsigned int GetPackagesSuccesfullySent() { return packages_successfully_sent_; }
  inline unsigned int GetPackagesLost() { return packages_lost_; }
  inline unsigned __int64 GetTimeOfChannelOccupancy() { return time_of_channel_occupancy_; }
  inline unsigned __int64 GetTimeOfStartTransmission() { return time_of_start_transmission_; }
  inline unsigned __int64 GetTimeCrp() { return time_crp_; }
  inline bool GetCorrectReceptionAck() { return correct_reception_ack_; }
  inline bool GetTransmissionPermission() { return transmission_permission_; }
  std::vector<Package*> GetPackages() { return packages_; }

  // set
  inline void SetTransmitterId(unsigned int transmitter_id)
  {
    this->transmitter_id_ = transmitter_id;
  }
  inline void SetPackagesSuccesfullySent(unsigned int packages_successfully_sent)
  {
    this->packages_successfully_sent_ = packages_successfully_sent;
  }
  inline void SetPackagesLost(unsigned int packages_lost)
  {
    this->packages_lost_ = packages_lost;
  }
  inline void SetTimeOfChannelOccupancy(unsigned __int64 time_of_channel_occupancy)
  {
    this->time_of_channel_occupancy_ = time_of_channel_occupancy;
  }
  inline void SetTimeOfStartTransmission(unsigned __int64 time_of_start_transmission)
  {
    this->time_of_start_transmission_ = time_of_start_transmission;
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
  void SetPackages(std::vector<Package*> &packages) { packages_ = packages; }

private:
  unsigned int transmitter_id_;  // transmitter number
  unsigned int packages_successfully_sent_;  // number of packages successfully sent
  unsigned int packages_lost_; // number of packages lost
  unsigned __int64 time_of_channel_occupancy_;  // time of channel occupancy
  unsigned __int64 time_of_start_transmission_; // time of start transmission
  unsigned __int64 time_crp_;  // random time after which retransmissions can be made
  bool correct_reception_ack_;  // true - ACK take back in less time than (CGPk + CTIZ)
  bool transmission_permission_;  // true - permission to transmit the packet
  std::vector<Package*> packages_;  // vector of packages ready to transmission
};

#endif