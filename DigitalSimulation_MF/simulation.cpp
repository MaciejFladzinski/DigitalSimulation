#include "simulation.h"

#include <iostream>

Simulation::Simulation(Logger* logger, WirelessNetwork* wireless_network)
{
  logger_ = logger;
  wireless_network_ = wireless_network;

	Transmitter* transmitter;

	unsigned int id_number;
  for (int i = 0; i < wireless_network->k_number_of_stations_; ++i)
  {
    transmitter = wireless_network->GetTransmitters(i);
    id_number = transmitter->GetTransmitterId();
  }
}

Simulation::~Simulation()
{

}

void Simulation::RunM4(Logger* logger, size_t time)
{
  logger_ = logger;

  clock_ = 0;
  wireless_network_->Init(logger_);

  logger->Info("Started Simulation method M4 (Process Interaction):");

  auto cmp = [](Package* left, Package* right) {return left->GetTime() > right->GetTime(); };
  Package::Agenda agenda(cmp);

  // Create package process
  size_t id = 0;

  auto package = new Package(id, rand() % 10, clock_, logger, wireless_network_, &agenda);
  agenda.push(package);
  package->Activ(0);

  // main loop
  while (clock_ < static_cast<size_t>(time))
  {
    Package* package_process = agenda.top();
    agenda.pop();
    clock_ = package_process->GetTime();
    logger->Info("Simulation time: " + std::to_string(clock_));
    package_process->Execute();

    if(package_process->GetIsTerminated() == true)
    {
      logger->Info("End process package (id: " + std::to_string(package_process->GetPackageId()) + ") \n");
      delete package_process;
    }
  }
}
