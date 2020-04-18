#ifndef PACKET_PROCESS_H_
#define PACKET_PROCESS_H_

#include "process.h"
#include "logger.h"

class PacketProcess : public Process
{
public:
  enum class State { Begin, Medium, End };

  PacketProcess(size_t time, Logger* logger); // add necessary pointers np. wireless network
  ~PacketProcess();

  void Execute() override;
  // implementation function execute (how it works?)

private:
  State state_ = State::Begin;
  Logger* logger_ = nullptr;
};
#endif