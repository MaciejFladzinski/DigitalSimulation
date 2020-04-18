#ifndef GENERATE_PACKET_EVENT_H_
#define GENERATE_PACKET_EVENT_H_

#include "process.h"
#include "logger.h"

class GeneratePacketEvent: public Process
{
public:
  // add pointers on WirelessNetwork
  GeneratePacketEvent(size_t time, Logger* logger); // add necessary pointers np. wireless network
  ~GeneratePacketEvent();

  void Execute() override;
  // implementation function execute (how it works?)

private:
  Logger* logger_ = nullptr;
};
#endif