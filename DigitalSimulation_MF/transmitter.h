#ifndef TRANSMITTER_H_
#define TRANSMITTER_H_

#include <vector>

#include "package.h"
#include "channel.h"
#include "logger.h"

class Package;

class Transmitter
{
public:
  Transmitter(unsigned int id_, Logger* logger);
  ~Transmitter();

  // functions
  void GenerateCRPTime(Logger* logger, size_t ctpk, unsigned int number_of_LR); // time before start retransmission
  void AddPackageSuccessfullySent(Logger* logger);  // Add 1 package successfully sent
  void AddPackageLost(Logger* logger);  // Add 1 package lost
  void IncTimeOfChannelListenning(Logger* logger);  // Add 0,5ms in channel listenning

  Package* GetFirstPackageInTX();
  void AddPackageInTX(Package* package);

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
  
  // set
  inline void SetTransmitterId(unsigned int transmitter_id)
  {
    this->transmitter_id_ = transmitter_id;
  }
  inline void SetPackagesLost(unsigned int packages_lost)
  {
    this->packages_lost_ = packages_lost;
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

private:
  unsigned int transmitter_id_ = 0;  // transmitter number
  unsigned int packages_successfully_sent_ = 0;  // number of packages successfully sent
  unsigned int packages_lost_ = 0; // number of packages lost
  size_t time_of_channel_listenning_ = 0; // time of checking channel
  size_t time_of_channel_occupancy_;  // time of channel occupancy
  size_t time_crp_;  // random time after which retransmissions can be made
  bool correct_reception_ack_ = false;  // true - ACK take back in less time than (CGPk + CTIZ)

  std::queue<Package*> packages_in_TX_; // packages in buffer (in transmitter)

  Logger* logger_ = nullptr;
};

#endif