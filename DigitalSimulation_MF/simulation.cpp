#include "simulation.h"

Simulation::Simulation(Logger* logger)
{
	printf("Start simultion \n");

	WirelessNetwork* wireless_network = new WirelessNetwork(logger);
	Package* package;
	Transmitter* transmitter;

	int id_number;
  for (int i = 0; i < wireless_network->k_number_of_stations_; ++i)
  {
    transmitter = wireless_network->GetTransmitters(i);
    id_number = transmitter->GetTransmitterId();

    for (int j = 1; j <= 2; ++j)
    {
      package = wireless_network->GeneratePackage(logger, wireless_network, j, id_number);
      // add random generate package time
      wireless_network->SetPackages(package);
      package->Execute();
    }
  }
  delete wireless_network;
}

Simulation::~Simulation()
{
  
}
