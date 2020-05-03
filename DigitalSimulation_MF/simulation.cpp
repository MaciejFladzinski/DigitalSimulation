#include "simulation.h"

Simulation::Simulation(Logger* logger, WirelessNetwork* wireless_network)
{
  logger_ = logger;
  wireless_network_ = wireless_network;

  logger->Info("Start simulation...");

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

void Simulation::Run(Logger* logger, unsigned __int64 time)
{
  logger_ = logger;

  clock_ = 0;
  wireless_network_->Init(logger_);

  logger->Info("Started Simulation method M4 (Process Interaction):");

  auto cmp = [](Package* left, Package* right) {return left->GetTime() > right->GetTime(); };
  Package::Agenda agenda(cmp);

  // Create first package process
  size_t id = 0;
  auto package = new Package(id, id, clock_, logger, wireless_network_, &agenda);
  package->Activ(time);

  // main loop
  while (clock_ < static_cast<size_t>(time))
  {
    Package* package_process = agenda.top();
    agenda.pop();
    clock_ = package_process->GetTime();

    logger->Info("Simulation time: " + std::to_string(clock_));
    package_process->Execute();

    if(package_process->IsTerminated())
    {
      delete package_process;
    }
  }
}
