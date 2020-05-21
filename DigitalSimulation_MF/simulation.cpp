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

void Simulation::StepInto()
{
  printf("\nPress Enter to continue... \n\n");
  getchar();
}

bool Simulation::SelectMode(int mode)
{
  if (mode == 1)
  {
    return true;
  }
  else if (mode == 2)
  {
    return false;
  }
  else
  {
    printf("Wrong number, try again \n\n");
    printf("Select simulation mode:\n1- step into\n2- step over\n");
    int key;
    std::cin >> key;
    SelectMode(key);
  }
}

size_t Simulation::GetStartTimeStatistics()
{
  return start_time_statistics_;
}

void Simulation::SetStartTimeStatistics(size_t initial_phase)
{
  start_time_statistics_ = initial_phase;
}


void Simulation::RunM4(Logger* logger, int time)
{
  logger_ = logger;

  clock_ = 0;
  wireless_network_->Init(logger_);

  printf("Set initial phase:\n");
  size_t initial_phase;
  std::cin >> initial_phase;
  SetStartTimeStatistics(initial_phase);
  printf("\n");

  printf("\nSelect simulation mode:\n1- step into\n2- step over\n");
  int key;
  std::cin >> key;
  printf("\n");

  logger->Info("Started Simulation method M4 (Process Interaction):");
  getchar();

  auto cmp = [](Package* left, Package* right) {return left->GetTime() > right->GetTime(); };
  Package::Agenda agenda(cmp);

  size_t id = 0;

  for (int i = 0; i < wireless_network_->k_number_of_stations_; ++i)
  {
    // package generate time
    int CGPk = wireless_network_->GetTransmitters(i)->GetGenerators()->RandExp(wireless_network_->GetLambda()) * 10;

    agenda.push(new Package(id, i, clock_ + CGPk, logger, wireless_network_, &agenda, this));
  }

  // main loop
  while (clock_ < static_cast<size_t>(time) && (!agenda.empty() == true))
  {
    Package* package_process = agenda.top();
    agenda.pop();
    clock_ = package_process->GetTime();

    printf("\n");
    logger->Info("Simulation time: " + std::to_string(clock_));
    package_process->Execute();

    if (package_process->GetIsTerminated() == true)
    {
      logger->Info("End process package (id: " + std::to_string(package_process->GetPackageId()) + ") \n");
      delete package_process;
    }
    if (SelectMode(key) == true) { StepInto(); }
  }
}
