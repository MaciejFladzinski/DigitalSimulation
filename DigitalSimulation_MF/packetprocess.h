#ifndef PACKET_PROCESS_H_
#define PACKET_PROCESS_H_

#include "logger.h"
#include "transmitter.h"

class PacketProcess : private Transmitter, private Package
{
public:
  // enum class - representation of states
  enum class State { AppearanceInTheSystem, Transmission, RemovalFromTheSystem };

  PacketProcess(size_t time, Logger* logger); // add necessary pointers: wireless network, etc.
  ~PacketProcess();

  void Execute();

  void Activ(size_t time); //function (process activation time)

protected:
  bool is_terminated_ = false;

private:
  State state_ = State::AppearanceInTheSystem;
  Logger* logger_ = nullptr;
  size_t activation_time_ = 0; //time after which the process will start
};
#endif