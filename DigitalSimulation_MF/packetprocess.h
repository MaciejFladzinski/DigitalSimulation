#ifndef PACKET_PROCESS_H_
#define PACKET_PROCESS_H_

#include "logger.h"
#include "process.h"

class PacketProcess : public Process
{
public:
  // enum class - representation of states
  enum class State { AppearanceInTheSystem, Transmission, RemovalFromTheSystem };

  PacketProcess(size_t time, size_t* time_ptr, Logger* logger); // add necessary pointers: wireless network, etc.
  ~PacketProcess();

  void Execute() override;

private:
  State state_ = State::AppearanceInTheSystem;
  Logger* logger_ = nullptr;
  size_t activation_time_ = 0; //time after which the process will start
};
#endif