#include "packetprocess.h"

PacketProcess::PacketProcess(size_t time, Logger* logger) : Process(time), logger_(logger)
{
  
}

PacketProcess::~PacketProcess()
{
  
}

void PacketProcess::Execute()
{
  bool active = true;

  logger_->Info("Packet Process");

  while(active)
  {
    switch(state_)
    {
      // before all break: set active = true/false + Activ(time) if it's required
    case State::Begin:
      // Begin operations
      break;

    case State::Medium:
      // Medium operations
      break;

    case State::End:
      // End operations
      break;

    default:
      // assert or exeption (error)
      break;
    }
  }
}
