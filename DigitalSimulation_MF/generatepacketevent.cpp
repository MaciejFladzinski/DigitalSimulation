#include "generatepacketevent.h"

GeneratePacketEvent::GeneratePacketEvent(size_t time, Logger* logger) : Process(time), logger_(logger)
{
  
}

GeneratePacketEvent::~GeneratePacketEvent()
{

}

void GeneratePacketEvent::Execute()
{
  logger_->Info("Generate Packet Event");

  // add wirelessnetwork -> generatepacket
  // implementation 
}
