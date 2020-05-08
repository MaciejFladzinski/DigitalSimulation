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

void Simulation::RunM4(Logger* logger, int time)
{
  logger_ = logger;

  clock_ = 0;
  wireless_network_->Init(logger_);

  printf("\nSelect simulation mode:\n1- step into\n2- step over\n");
  int key;
  std::cin >> key;
  std::cout << std::endl;

  logger->Info("Started Simulation method M4 (Process Interaction):");
  getchar();

  auto cmp = [](Package* left, Package* right) {return left->GetTime() > right->GetTime(); };
  Package::Agenda agenda(cmp);

  size_t id = 0;

  agenda.push(new Package(id, rand() % 10, clock_, logger, wireless_network_, &agenda));

  // main loop
  while (clock_ < static_cast<size_t>(time) && (!agenda.empty() == true))
  {
    Package* package_process = agenda.top();
    agenda.pop();
    clock_ = package_process->GetTime();

    printf("\n");
    logger->Info("Simulation time: " + std::to_string(clock_));
    package_process->Execute();

    if(package_process->GetIsTerminated() == true)
    {
      logger->Info("End process package (id: " + std::to_string(package_process->GetPackageId()) + ") \n");
      delete package_process;
    }
    if (SelectMode(key) == true) { StepInto(); }
  }
}
