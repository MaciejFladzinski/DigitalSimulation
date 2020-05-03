#include "wirelessNetwork.h"
#include "package.h"

#include <iostream>

WirelessNetwork::WirelessNetwork(Logger* logger)
{
  logger_ = logger;
	logger->Info("Create Wireless Network");

  channel_ = new Channel(logger);

	for (int i = 0; i < k_number_of_stations_; ++i)
	{
		auto transmitter = new Transmitter(i, logger);
		transmitters_.push_back(transmitter);

		auto receiver = new Receiver(i, logger);
		receivers_.push_back(receiver);
	}
}

WirelessNetwork::~WirelessNetwork()
{
	logger_->Info("Remove Wireless Network");
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

class Package* WirelessNetwork::GetPackages(int i)
{
	return packages_[i];
}

Channel* WirelessNetwork::GetChannel()
{
	return channel_;
}

bool WirelessNetwork::GetChannelStatus()
{
	return channel_->GetChannelOccupancy();
}

/*
Package* WirelessNetwork::GeneratePackage(Logger* logger, WirelessNetwork* wireless_network,
	unsigned id_package, unsigned id_station)
{
	//Package* new_package = new Package(id_package, id_station, logger, wireless_network);
	//return new_package;
}
*/

void WirelessNetwork::SetPackages(Package* package)
{
	return packages_.push_back(package);
}

void WirelessNetwork::Init(Logger* logger)
{
	logger_ = logger;

  while (!packages_.empty()) // while buffer isn't empty
  {
		delete packages_.front(); // delete actual
		packages_.pop_back(); // pop next
  }
	channel_->SetChannelOccupancy(false);	// channel is free
}

void WirelessNetwork::GeneratePackage(Logger* logger, Package* package)
{
	logger_ = logger;
	packages_.push_back(package);
	logger->Info("Generate package (id: " + std::to_string(package->GetPackageId()) +
		") in transmitter (id: " + std::to_string(package->GetStationId()) + ")");
}

void WirelessNetwork::StartTransmission(Logger* logger)
{
	logger_ = logger;
	channel_->SetChannelOccupancy(true);
	logger->Info("Started transmission of packet: " + std::to_string(packages_.front()->GetPackageId()));
}

void WirelessNetwork::EndTransmission(Logger* logger)
{
	logger_ = logger;
	channel_->SetChannelOccupancy(false);
	logger->Info("Ended transmission of packet: " + std::to_string(packages_.front()->GetPackageId()));
	packages_.pop_back();
}