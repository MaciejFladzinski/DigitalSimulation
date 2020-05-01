#include "wirelessNetwork.h"
#include "package.h"

#include <iostream>

WirelessNetwork::WirelessNetwork(Logger* logger)
{
  logger_ = logger;
	logger->Info("Creating a Wireless Network \n");

  channel_ = new Channel(logger);
	std::cout << "Create Channel \n";

	for (int i = 0; i < k_number_of_stations_; ++i)
	{
		auto transmitter = new Transmitter(i, logger);
		transmitters_.push_back(transmitter);
		std::cout << "Create transmitter nr: " << i << std::endl;

		auto receiver = new Receiver(i, logger);
		receivers_.push_back(receiver);
		std::cout << "Create receiver nr: " << i << std::endl;
	}

}

WirelessNetwork::~WirelessNetwork()
{
	logger_->Info("Deleting a Wireless Network \n");
	delete channel_;

	for (int i = 0; i < k_number_of_stations_; ++i)
  {
		delete transmitters_[i];
		delete receivers_[i];
  }
}

Transmitter* WirelessNetwork::GetTransmitters(int i)
{
	return transmitters_[i];
}

Receiver* WirelessNetwork::GetReceivers(int i)
{
	return receivers_[i];
}

Package* WirelessNetwork::GeneratePackage(Logger* logger, WirelessNetwork* wireless_network, unsigned id_package, unsigned id_station)
{
	Package* new_package = new Package(id_package, id_station, logger, wireless_network);
	return new_package;
}

void WirelessNetwork::SetPackages(Package* package)
{
	return packages_.push_back(package);
}
