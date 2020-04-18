#ifndef PACKET_PROCESS_H_
#define PACKET_PROCESS_H_

#include "process.h"

class PacketProcess : public Process
{
public:
  enum class State { Begin, Medium, End };

  PacketProcess();
  ~PacketProcess();

  void Execute() override;

private:
  State state_ = State::Begin;
};
#endif