#include "transmitter.h"

#include <iostream>

#include "channel.h"

Transmitter::Transmitter(unsigned int id_)
{
  transmitter_id_ = id_;
}

Transmitter::~Transmitter()
{
  
}

void Transmitter::GeneratePackage()
{
  static size_t package_id = 0;
  ++package_id;
  auto package = new Package(package_id,0); // add function which calculating CTPk 
  packages_.push_back(package);
}

void Transmitter::StartTransmission()
{
  if (GetChannelOccupancy() == false && !packages_.empty())
  {
    std::cout << "Start packet transmission. Package nr: " << packages_.front()->GetPackageId() << std::endl;
  }
}
