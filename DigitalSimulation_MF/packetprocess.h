#ifndef PACKET_PROCESS_H_
#define PACKET_PROCESS_H_

#include "logger.h"
#include "wirelessNetwork.h"

class PacketProcess: public Transmitter, public Receiver
{
public:
  // enum class - representation of states
  enum class State { AppearanceInTheSystem, ChannelListening, Transmission, Retransmission, ACK, RemovalFromTheSystem };

  PacketProcess(unsigned __int64 time, Logger* logger, WirelessNetwork* wireless_netowrk); // add necessary pointers: wireless network, etc.
  ~PacketProcess();

  // functions
  void Execute();
  void Activ(unsigned __int64 time); //function (process activation time)
  
  // get
  inline unsigned __int64 GetActivationTime() { return activation_time_; }

  // set
  void SetActivationTime(unsigned __int64 activation_time) { activation_time_ = activation_time; }

protected:
  bool is_terminated_;

private:
  State state_ = State::AppearanceInTheSystem;
  Logger* logger_ = nullptr;
  unsigned __int64 activation_time_ = 0; //time after which the process will start
};
#endif