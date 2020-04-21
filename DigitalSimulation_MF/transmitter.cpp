#include "transmitter.h"

Transmitter::Transmitter(unsigned int id_)
{
  transmitter_id_ = id_;
}

Transmitter::~Transmitter()
{
  
}

void Transmitter::GeneratePackage()
{
  static size_t id = 0;
  ++id;
  auto package = new Package(id,1);
  packages_.push_back(package);
  printf("Generate package (id: %d) \n", id);
}

void Transmitter::StartTransmission(Logger* logger, Package* package)
{
  logger->Info("Start package transmission" + std::to_string(packages_.front()->GetPackageId()));

  /*
   *logger->Info("Started transmission of packet "+ std::to_string(packets_.front()->GetPacketId()));
  GetPacketsCurrentlyTransmitting()->push_back(packet);
  Packet* pack = new Packet(3,3);
  GetPacketsCurrentlyTransmitting()->push_back(pack);
  SetChannelStatus(false);

  if (GetPacketsCurrentlyTransmitting()->size() > 1)
  {
    SetCollisionStatus(true);
    logger->Info("Collision detected");
  }
  else
  {
    logger->Info("No coliision");
  }
  */
}
