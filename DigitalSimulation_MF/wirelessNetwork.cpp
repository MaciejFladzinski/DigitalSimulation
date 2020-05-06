#include "wirelessNetwork.h"

#include <iostream>

WirelessNetwork::WirelessNetwork(Logger* logger)
{
  logger_ = logger;
	logger->Info("Create wireless network");
	int id = 0;
  channel_ = new Channel(logger);

	for (int i = 0; i < k_number_of_stations_; ++i)
	{
		auto transmitter = new Transmitter(i, logger);
		transmitters_.push_back(transmitter);

		auto receiver = new Receiver(i, logger);
		receivers_.push_back(receiver);
	}
	printf("\n");
}

WirelessNetwork::~WirelessNetwork()
{
	logger_->Info("Remove wireless network");
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

void WirelessNetwork::AddPackages(Package* package)
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

void WirelessNetwork::GeneratePackage(Logger* logger, Package* package, Transmitter* transmitter, unsigned int id_station)
{
	logger_ = logger;
	transmitter_ = transmitter;
	static size_t id = 0;
	++id;
	transmitter->AddPackageInTX(package);	// add package to the buffer in transmitter
  package->GenerateCTPkTime(logger);

	logger->Info("Generate package (id: " + std::to_string(package->GetPackageId()) + ") by transmitter (id: " +
		std::to_string(transmitter->GetTransmitterId()) + "). Package transmission time: " + std::to_string(package->GetTimeCTPk()));
}

void WirelessNetwork::StartTransmission(Logger* logger)
{
	logger_ = logger;
	channel_->SetChannelOccupancy(true);
	logger->Info("Start transmission");
}

void WirelessNetwork::EndTransmission(Logger* logger)
{
	logger_ = logger;
	channel_->SetChannelOccupancy(false);
	packages_.pop_back();
}