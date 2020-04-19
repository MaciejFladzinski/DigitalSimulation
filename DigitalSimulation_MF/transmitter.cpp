#include "transmitter.h"

#include <iostream>

#include "receiver.h"
#include "channel.h"
#include "package.h"

Transmitter::Transmitter(unsigned int id_) : Receiver(0), Channel()
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
    static size_t package_id = 0;
    ++package_id;
    auto package = new Channel();
    // transmitted_packages_.push_back(package);
    std::cout << "Start packet transmission. Package nr: " << packages_.front()->GetPackageId() << std::endl;
  }
}

void Transmitter::Retransmission()
{
  int number_of_retransmission = 1;

  if (GetErrorTransmission() == true)
  {
    
    int R = rand() % (2 ^ number_of_retransmission - 1);
    int CRP = R * 1;  // 1 -> CTPk
    // wait CRP time...
    StartTransmission();
  }
}
