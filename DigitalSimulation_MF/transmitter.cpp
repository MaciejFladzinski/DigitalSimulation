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

void Transmitter::StartTransmission()
{
  
}
