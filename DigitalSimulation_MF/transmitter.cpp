#include "transmitter.h"

#include <fstream>
#include <iostream>

Transmitter::Transmitter(unsigned int id_, Logger* logger, int uniform_seed, int exp_seed, int r_seed)
{
  transmitter_id_ = id_;
  logger_ = logger;

  uniform_generator_ = new Generators(uniform_seed);
  exp_generator_ = new Generators(exp_seed);
  r_generator_ = new Generators(r_seed);

  logger->Info("Create transmitter nr: " + std::to_string(id_));
}

Transmitter::~Transmitter()
{
  logger_->Info("Remove transmitter nr: " + std::to_string(transmitter_id_));
}

Generators* Transmitter::GetUniformGenerator()
{
  return uniform_generator_;
}

Generators* Transmitter::GetExpGenerator()
{
  return exp_generator_;
}

Generators* Transmitter::GetRGenerator()
{
  return r_generator_;
}

unsigned int Transmitter::GetPackagesSuccessfullySent()
{
  return packages_successfully_sent_;
}

unsigned int Transmitter::GetPackagesLost()
{
  return packages_lost_;
}

void Transmitter::GenerateCRPTime(Logger* logger, size_t ctpk, unsigned int number_of_LR)
{
  logger_ = logger;

  unsigned int max_value = std::pow(2, number_of_LR);
  unsigned int R = GetRGenerator()->Rand(0, max_value);
  size_t crp_time = ctpk * R * 10;

  SetTimeCrp(crp_time);
  logger->Info("CRP time: " + std::to_string(GetTimeCrp()));
}

void Transmitter::AddPackageSuccessfullySent(Logger* logger)
{
  logger_ = logger;

  SetPackagesSuccessfullySent(GetPackagesSuccessfullySent() + 1);

  CalculationAverageNumberOfLR();
  CalculationAverageOfPackagesDelayTime();
  CalculationAverageOfPackagesWaitingTime();

  SetPackageErrorRate((double)GetPackagesLost() / (double)GetPackagesSuccessfullySent());

  logger->Info("Packages successfully sent: " + std::to_string(GetPackagesSuccessfullySent()) +
    ", by transmitter: " + std::to_string(GetTransmitterId()));

  logger->Info("Actual package error rate: " + std::to_string(GetPackageErrorRate()) +
    ", in transmitter: " + std::to_string(GetTransmitterId()));
}

void Transmitter::AddPackageLost(Logger* logger)
{
  logger_ = logger;

  SetPackagesLost(GetPackagesLost() + 1);

  CalculationAverageOfPackagesWaitingTime();

  if (GetPackagesSuccessfullySent() == 0)
  {
    SetPackageErrorRate(0);
  }
  else
  {
    SetPackageErrorRate((double)GetPackagesLost() / (double)GetPackagesSuccessfullySent());
  }

  logger->Info("Packages lost: " + std::to_string(GetPackagesLost()) +
    ", by transmitter: " + std::to_string(GetTransmitterId()));

  logger->Info("Actual package error rate: " + std::to_string(GetPackageErrorRate()) +
    ", in transmitter: " + std::to_string(GetTransmitterId()));
}

void Transmitter::CalculationMaxPackageErrorRate()
{
  if (GetPackageErrorRate() >= GetMaxPackageErrorRate())
  {
    if (GetPackagesSuccessfullySent() == 0)
    {
      SetMaxPackageErrorRate(0);
    }
    else
    {
      SetMaxPackageErrorRate(GetPackageErrorRate());
    }

    std::ofstream savePackagesSent("SavePackagesSent.txt", std::ios_base::app);

    savePackagesSent << "[Info] New max package error rate: " +
      std::to_string(GetMaxPackageErrorRate()) << std::endl;

    savePackagesSent.close();
  }
}

void Transmitter::IncTimeOfChannelListenning(Logger* logger)
{
  logger_ = logger;
  this->time_of_channel_listenning_ += 5;
  logger->Info("Time of free channel listenning: " +
    std::to_string(time_of_channel_listenning_ - 5) + ", by transmitter: " +
    std::to_string(GetTransmitterId()));
}

Package* Transmitter::GetFirstPackageInTX()
{
  return packages_in_TX_.front();
}

void Transmitter::RemoveFirstPackageInTX()
{
  packages_in_TX_.pop();
}

bool Transmitter::IsBufferInTXEmpty()
{
  return packages_in_TX_.empty();
}

void Transmitter::AddPackageInTX(Package* package)
{
  return packages_in_TX_.push(package);
}

void Transmitter::CalculationAverageNumberOfLR()
{
  SetSumOfAllLR(GetSumOfAllLR() + GetFirstPackageInTX()->GetNumberOfLR());
  SetAverageNumberOfLR(GetSumOfAllLR() / GetPackagesSuccessfullySent());
}

void Transmitter::CalculationAverageOfPackagesDelayTime()
{
  SetSumOfAllPackagesDelayTime(GetSumOfAllPackagesDelayTime() + GetFirstPackageInTX()->GetPackageDelayTime());
  SetAverageOfPackagesDelayTime(GetSumOfAllPackagesDelayTime() / GetPackagesSuccessfullySent());
}

void Transmitter::CalculationAverageOfPackagesWaitingTime()
{
  SetSumOfAllPackagesWaitingTime(GetSumOfAllPackagesWaitingTime() + GetFirstPackageInTX()->GetPackageWaitingTime());

  if ((GetPackagesSuccessfullySent() + GetPackagesLost()) != 0)
  {
    SetAverageOfPackagesWaitingTime(GetSumOfAllPackagesWaitingTime() / (GetPackagesSuccessfullySent() + GetPackagesLost()));
  }
  else
  {
    SetAverageOfPackagesWaitingTime(0);
  }
}

void Transmitter::CalculationAverageOfSystemThroughput()
{
  SetAverageOfSystemThroughput(GetFirstPackageInTX()->GetSystemThroughput());
}
