#ifndef PACKET_PROCESS_H_
#define PACKET_PROCESS_H_

#include "process.h"
#include "logger.h"

class PacketProcess : public Process
{
public:
  enum class State { AppearanceInTheSystem, Transmission, RemovalFromTheSystem };

  PacketProcess(size_t time, Logger* logger); // add necessary pointers: wireless network, etc.
  ~PacketProcess();

  void Execute() override;

private:
  State state_ = State::AppearanceInTheSystem;
  Logger* logger_ = nullptr;
};
#endif