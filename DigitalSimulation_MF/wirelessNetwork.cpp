#include "wirelessNetwork.h"

#include <fstream>
#include <iostream>
#include <iterator>

WirelessNetwork::WirelessNetwork(Logger* logger, int wireless_network_seed)
{
  logger_ = logger;
	seed = wireless_network_seed;

	seeds_generator = new Generators(seed);

  for (int i = 0; i < kNumberOfSeeds * kSeedSaveStep; ++i)
  {
		seeds_generator->Rand();

		if(i % kSeedSaveStep == 0)
		{
			seeds_.push_back(seeds_generator->GetKernel());
		}
  }

	// Save data to file
	std::ofstream output_file("./example.txt");

	std::ostream_iterator<double> output_iterator(output_file, "\n");

	std::copy(seeds_.begin(), seeds_.end(), output_iterator);

	auto seed_uniform = seeds_.back();
	seeds_.pop_back();

	logger->Info("Create wireless network");
	int id = 0;
  channel_ = new Channel(logger, seed_uniform);

	for (int i = 0; i < k_number_of_stations_; ++i)
	{
		auto seed_uniform = seeds_.back();
		seeds_.pop_back();

		auto seeds_exp = seeds_.back();
		seeds_.pop_back();

		auto seed_r = seeds_.back();
		seeds_.pop_back();

		auto transmitter = new Transmitter(i, logger, seed_uniform, seeds_exp, seed_r);
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
}

void WirelessNetwork::EndTransmission(Logger* logger)
{
	logger_ = logger;
	packages_.pop_back();
}

double WirelessNetwork::GetLambda()
{
	return lambda;
}

void WirelessNetwork::IncrementCounterOfPackagesSuccessfullySent()
{
	SetCounterOfPackagesSuccessfullySent(GetCounterOfPackagesSuccessfullySent() + 1);
}


void WirelessNetwork::TotalMaxPackageErrorRate()
{
  for (int i = 0; i < k_number_of_stations_; ++i)
  {
		if (GetTotalMaxPackageErrorRate() <= GetTransmitters(i)->GetMaxPackageErrorRate())
		{
			SetTotalMaxPackageErrorRate(GetTransmitters(i)->GetMaxPackageErrorRate());
		}
	}
}

void WirelessNetwork::TotalNumberOfPackagesSuccessfullySent()
{
	SetTotalNumberOfPackagesSuccessfullySent(0);

	for (int i = 0; i < k_number_of_stations_; ++i)
	{
		SetTotalNumberOfPackagesSuccessfullySent(GetTotalNumberOfPackagesSuccessfullySent() +
			GetTransmitters(i)->GetPackagesSuccessfullySent());
	}
}

void WirelessNetwork::TotalNumberOfPackagesLost()
{
	SetTotalNumberOfPackagesLost(0);

	for (int i = 0; i < k_number_of_stations_; ++i)
	{
		SetTotalNumberOfPackagesLost(GetTotalNumberOfPackagesLost() + GetTransmitters(i)->GetPackagesLost());
	}
}

void WirelessNetwork::TotalPackageErrorRate()
{
	SetTotalPackageErrorRate((double)GetTotalNumberOfPackagesLost() / (double)GetTotalNumberOfPackagesSuccessfullySent());
}

void WirelessNetwork::TotalAverageNumberOfLR()
{
  for (int i = 0; i < k_number_of_stations_; ++i)
  {
		SetTotalAverageNumberOfLR(GetTotalAverageNumberOfLR() + GetTransmitters(i)->GetAverageNumberOfLR());
  }

	SetTotalAverageNumberOfLR(GetTotalAverageNumberOfLR() / (double)k_number_of_stations_);
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
		SetTotalAverageOfSystemThroughput(GetTotalAverageOfSystemThroughput() +
			GetTransmitters(i)->GetAverageOfSystemThroughput());
  }
	SetTotalAverageOfSystemThroughput(GetTotalAverageOfSystemThroughput() / k_number_of_stations_);
}

void WirelessNetwork::TransmittersStatistic(Logger* logger)
{
	logger_ = logger;

	for (int i = 0; i < k_number_of_stations_; ++i)
	{
		printf("\n");
		logger->Info("Transmitter (id: " + std::to_string(i) + ") statistics:");

		logger->Info("Number of packages successfully sent: " +
			std::to_string(GetTransmitters(i)->GetPackagesSuccessfullySent()));

		logger->Info("Number of packages lost: " +
			std::to_string(GetTransmitters(i)->GetPackagesLost()));

		logger->Info("Average of package error rate: " +
			std::to_string(GetTransmitters(i)->GetPackageErrorRate() * 100) + "%");

		logger->Info("Max package error rate in station: " +
			std::to_string(GetTransmitters(i)->GetMaxPackageErrorRate() * 100) + "%");

		logger->Info("Average number of LR: " +
			std::to_string(GetTransmitters(i)->GetAverageNumberOfLR()));

		logger->Info("Average of throughput in system: " +
			std::to_string(GetTransmitters(i)->GetAverageOfSystemThroughput()) + "/s");

		logger->Info("Average of package delay time: " +
			std::to_string(GetTransmitters(i)->GetAverageOfPackagesDelayTime()) + "ms");

		logger->Info("Average of package waiting time: " +
			std::to_string(GetTransmitters(i)->GetAverageOfPackagesWaitingTime()) + "ms");
	}
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

	TotalPackageErrorRate();
	logger->Info("Total average of package error rate: " + std::to_string(GetTotalPackageErrorRate() * 100) + "%");

	TotalMaxPackageErrorRate();
	logger->Info("Max package error rate in system: " + std::to_string(GetTotalMaxPackageErrorRate() * 100) + "%");

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
