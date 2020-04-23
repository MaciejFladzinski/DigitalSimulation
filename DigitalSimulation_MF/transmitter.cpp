#include "transmitter.h"

Transmitter::Transmitter(unsigned int id_) : Package(0)
{
  transmitter_id_ = id_;
}

Transmitter::~Transmitter()
{
  
}

void Transmitter::GeneratePackage(Logger* logger)
{
  static size_t id = 0;
  ++id;
  auto package = new Package(id);
  packages_.push_back(package);
  logger->Info("Generate package (id: " + std::to_string(id) + ") and add it to FIFO queue");
}

void Transmitter::StartTransmission(Logger* logger, Package* package)
{
  logger->Info("Start transmission package (id: " + std::to_string(packages_.front()->GetPackageId()) + ")");
  GetTransmittedPackages()->push_back(package);

  // TEST collision (expected: Collision detected!)
  auto test_package = new Package(4);
  GetTransmittedPackages()->push_back(test_package); // add second package in transmitted channel
  SetChannelOccupancy(false);
  // checking collision in channel
  if(GetTransmittedPackages()->size()>1)
  {
    SetCollision(true);
    logger->Error("Collision detected !");
  }
}

void Transmitter::Retransmission(Logger* logger, Package* package)
{
  static int number_of_LR = 0;
  SetNumberOfLR(++number_of_LR);

  if(GetNumberOfLR() <= 10)
  {
    // generate CRP time
    // wait CRP time...
    logger->Info("Retransmission package (id: " + std::to_string(packages_.front()->GetPackageId()) +
      "). Number of retransmission: " + std::to_string(GetNumberOfLR()));
    // go to state::CheckingChannel
  }
  else
  {
    logger->Error("Another retransmission cannot be performed !");
    // go to state::RemovalFromTheSystem
  }
}

void Transmitter::RemovePackage(Logger* logger, Package* package)
{
  static int packages_successfully_sent = 0;
  static int packages_lost = 0;

  if (GetCorrectReceptionAck() == true)
  {
    SetPackagesSuccesfullySent(++packages_successfully_sent);
    logger->Info("Package successfully sent ! Number of packages successfully sent: " +
      std::to_string(GetPackagesSuccesfullySent()));
    packages_.pop_back();
  }
  else
  {
    SetPackagesLost(++packages_lost);
    logger->Error("Package lost. Number od packages lost: " + std::to_string(GetPackagesLost()));
    packages_.pop_back();
  }

  if(packages_.front())
  {
    // go to ChannelListenning
  }
  else
  {
    // wait for generate new package
  }
}
