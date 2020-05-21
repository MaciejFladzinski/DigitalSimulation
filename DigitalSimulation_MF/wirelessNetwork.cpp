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
	package->SetTimeAddedToBuffer(package->GetTime());
	package->SaveTimeOfAddedToBuffer();
	package->GenerateCTPkTime(logger);

	logger->Info("Generate package (id: " + std::to_string(package->GetPackageId()) + ") by transmitter (id: " +
		std::to_string(transmitter->GetTransmitterId()) + "). Package transmission time: " + std::to_string(package->GetTimeCTPk()));
}

void WirelessNetwork::StartTransmission(Logger* logger)
{
	logger_ = logger;
	channel_->SetChannelOccupancy(true);
	//logger->Info("Start transmission");
}

void WirelessNetwork::EndTransmission(Logger* logger)
{
	logger_ = logger;
	//channel_->SetChannelOccupancy(false);
	packages_.pop_back();
}

double WirelessNetwork::GetLambda()
{
	return lambda;
}

void WirelessNetwork::TotalMaxPackageErrorRate()
{
	for (int i = 0; i < k_number_of_stations_; ++i)
	{
		SetTotalMaxPackageErrorRate(GetTotalMaxPackageErrorRate() + GetTransmitters(i)->GetMaxPackageErrorRate());
	}

	SetTotalMaxPackageErrorRate(GetTotalMaxPackageErrorRate() / k_number_of_stations_);
}

void WirelessNetwork::TotalNumberOfPackagesSuccessfullySent()
{
	for (int i = 0; i < k_number_of_stations_; ++i)
	{
		SetTotalNumberOfPackagesSuccessfullySent(GetTotalNumberOfPackagesSuccessfullySent() +
			GetTransmitters(i)->GetPackagesSuccessfullySent());
	}
}

void WirelessNetwork::TotalNumberOfPackagesLost()
{
	for (int i = 0; i < k_number_of_stations_; ++i)
	{
		SetTotalNumberOfPackagesLost(GetTotalNumberOfPackagesLost() + GetTransmitters(i)->GetPackagesLost());
	}
}

void WirelessNetwork::TotalPackageErrorRate()
{
	for (int i = 0; i < k_number_of_stations_; ++i)
	{
		SetTotalPackageErrorRate(GetTotalPackageErrorRate() + GetTransmitters(i)->GetPackageErrorRate());
	}

	SetTotalPackageErrorRate(GetTotalPackageErrorRate() / k_number_of_stations_);
}

void WirelessNetwork::TotalAverageNumberOfLR()
{
	for (int i = 0; i < k_number_of_stations_; ++i)
	{
		SetTotalAverageNumberOfLR(GetTotalAverageNumberOfLR() + GetTransmitters(i)->GetAverageNumberOfLR());
	}

	SetTotalAverageNumberOfLR(GetTotalAverageNumberOfLR() / k_number_of_stations_);
}

void WirelessNetwork::TotalAverageOfPackagesDelayTime()
{
	for (int i = 0; i < k_number_of_stations_; ++i)
	{
		SetTotalAverageOfPackagesDelayTime(GetTotalAverageOfPackagesDelayTime() +
			GetTransmitters(i)->GetAverageOfPackagesDelayTime());
	}

	SetTotalAverageOfPackagesDelayTime(GetTotalAverageOfPackagesDelayTime() / (10 * k_number_of_stations_));
}

void WirelessNetwork::TotalAverageOfPackagesWaitingTime()
{
	for (int i = 0; i < k_number_of_stations_; ++i)
	{
		SetTotalAverageOfPackagesWaitingTime(GetTotalAverageOfPackagesWaitingTime() +
			GetTransmitters(i)->GetAverageOfPackagesWaitingTime());
	}

	SetTotalAverageOfPackagesWaitingTime(GetTotalAverageOfPackagesWaitingTime() / (10 * k_number_of_stations_));
}

void WirelessNetwork::TotalAverageOfSystemThroughput()
{
	for (int i = 0; i < k_number_of_stations_; ++i)
	{
		SetTotalAverageOfSystemThroughput(GetTotalAverageOfSystemThroughput() + GetTransmitters(i)->GetAverageOfSystemThroughput());
	}
	SetTotalAverageOfSystemThroughput(GetTotalAverageOfSystemThroughput() / k_number_of_stations_);
}

void WirelessNetwork::TotalStatistics(Logger* logger)
{
	logger_ = logger;

	logger->Info("\n\nTotal statistics:");

	TotalNumberOfPackagesSuccessfullySent();
	logger->Info("Total number of packages successfully sent: " +
		std::to_string(GetTotalNumberOfPackagesSuccessfullySent()));

	TotalNumberOfPackagesLost();
	logger->Info("Total number of packages lost: " + std::to_string(GetTotalNumberOfPackagesLost()));

	TotalMaxPackageErrorRate();
	logger->Info("Total average of package error rate: " + std::to_string(GetTotalPackageErrorRate()));

	logger->Info("Max package error rate in system: " + std::to_string(GetTotalMaxPackageErrorRate()));

	TotalAverageNumberOfLR();
	logger->Info("Total average number of LR: " + std::to_string(GetTotalAverageNumberOfLR()));

	TotalAverageOfSystemThroughput();
	logger->Info("Total average of throughput in system: " + std::to_string(GetTotalAverageOfSystemThroughput())
		+ "/s");

	TotalAverageOfPackagesDelayTime();
	logger->Info("Total average of package delay time: " + std::to_string(GetTotalAverageOfPackagesDelayTime())
		+ "ms");

	TotalAverageOfPackagesWaitingTime();
	logger->Info("Total average of package waiting time: " + std::to_string(GetTotalAverageOfPackagesWaitingTime())
		+ "ms");
}
