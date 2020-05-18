#include "package.h"

#include <fstream>
#include <iostream>

#include "wirelessNetwork.h"
#include "channel.h"

Package::Package(unsigned int id_package, unsigned int id_station, size_t time,
  Logger* logger, WirelessNetwork* wireless_network, Agenda* agenda, Simulation* simulation)
{
  id_package_ = id_package;
  id_station_ = id_station;
  time_ = time;
  wireless_network_ = wireless_network;
  logger_ = logger;
  agenda_ = agenda;
  simulation_ = simulation;

  //logger->Info("Package nr: " + std::to_string(id_package) +
  //  " (in station nr: " + std::to_string(id_station) + ") has been created");
}

Package::Package(unsigned int id_package, unsigned int id_station, size_t time)
{
  id_package_ = id_package;
  id_station_ = id_station;
  time_ = time;
}

Package::~Package()
{
  logger_->Info("Remove package");
}

void Package::SetPackageId(unsigned int id_package)
{
  id_package_ = id_package;
}

void Package::SetStationId(unsigned int id_station)
{
  id_station_ = id_station;
}

void Package::SetNumberOfLR(unsigned int number_of_LR)
{
  number_of_LR_ = number_of_LR;
}

void Package::SetTimeCTPk(size_t ctpk_time)
{
  ctpk_time_ = ctpk_time;
}

void Package::SetTime(size_t time)
{
  time_ = time;
}

void Package::IncrementNumberOfLR(Logger* logger)
{
  logger_ = logger;
  ++number_of_LR_;
  SetNumberOfLR(number_of_LR_);
  logger->Info("Package retransmission attempt... attempt nr: " + std::to_string(GetNumberOfLR()));
}

void Package::IncrementCounter()
{
  counter_++;
}

void Package::AddSumOfAllRetransmissions()
{
  sum_of_all_retransmissions_ += GetNumberOfLR();
}

void Package::CalculationAverageNumberOfLR()
{
  average_number_of_LR_ = GetSumOfAllRetransmissions() / GetCounter();
}

void Package::SaveNumberOfLR()
{
  IncrementCounter();
  AddSumOfAllRetransmissions();
  CalculationAverageNumberOfLR();

  if (GetTime() >= simulation_->GetStartTimeStatistics())
  {
    // add to file
    std::ofstream saveNumberOfLR("SaveNumberOfLR.txt", std::ios_base::app);
    saveNumberOfLR << "[Info] Number of LR: " + std::to_string(GetNumberOfLR()) +
      " by transmitter: " + std::to_string(GetStationId()) << std::endl;

    saveNumberOfLR << "[Info] Actual average number of LR: " + std::to_string(GetAverageNumberOfLR()) +
      ", in transmitter: " + std::to_string(GetStationId()) << std::endl << std::endl;

    saveNumberOfLR.close();
  }

  logger_->Info("Actual average number of LR: " + std::to_string(GetAverageNumberOfLR()) +
    ", in transmitter: " + std::to_string(GetStationId()));
}

bool Package::GetIsTerminated()
{
  return is_terminated_;
}

void Package::SetTerminated()
{
  is_terminated_ = true;
}

void Package::GenerateCTPkTime(Logger* logger)
{
  logger_ = logger;
  size_t ctpk_time = rand() % 10 * 10 + 10;	 // time CTPk {1,...,10}ms * 10 -> {10,...,100}x 
  SetTimeCTPk(ctpk_time);
  logger->Info("Generate CTPk time... CTPk = " + std::to_string(GetTimeCTPk()));
}

void Package::SaveTimeOfAddedToBuffer()
{
  if (GetTime() >= simulation_->GetStartTimeStatistics())
  {
    // add to file
    std::ofstream saveTimeOfAddedToBuffer("SaveTimeOfAddedToBuffer.txt", std::ios_base::app);

    saveTimeOfAddedToBuffer << "[Info] Time of added package to the buffer: " +
      std::to_string(GetTimeAddedToBuffer()) +
      ", in transmitter: " + std::to_string(GetStationId()) << std::endl;

    saveTimeOfAddedToBuffer.close();
  }
}

void Package::PackageDelayTime()
{
  size_t package_delay_time = GetTimeSuccessfullySentPackage() - GetTimeAddedToBuffer();

  if (GetTime() >= simulation_->GetStartTimeStatistics())
  {
    // add to file
    std::ofstream savePackageDelayTime("SavePackageDelayTime.txt", std::ios_base::app);

    savePackageDelayTime << "[Info] Package delay time: " + std::to_string(package_delay_time) +
      ", in transmitter: " + std::to_string(GetStationId()) << std::endl;

    savePackageDelayTime.close();
  }

  logger_->Info("Package delay time: " + std::to_string(package_delay_time) +
    ", in transmitter: " + std::to_string(GetStationId()));
}

void Package::SaveTimeSuccessfullySentPackage()
{
  if (GetTime() >= simulation_->GetStartTimeStatistics())
  {
    // add to file
    std::ofstream saveTimeSuccessfullySentPackage("SaveTimeSuccessfullySentPackage.txt", std::ios_base::app);

    saveTimeSuccessfullySentPackage << "[Info] Time when package is successfully sent: " +
      std::to_string(GetTimeSuccessfullySentPackage()) +
      ", by transmitter: " + std::to_string(GetStationId()) << std::endl;

    saveTimeSuccessfullySentPackage.close();

    PackageDelayTime(); // calculation package delay time (successfully sent - generate in buffer)
  }
}

void Package::SaveTimeRemoveFromBuffer()
{
  if (GetTime() >= simulation_->GetStartTimeStatistics())
  {
    // add to file
    std::ofstream saveTimeRemoveFromBuffer("SaveTimeRemoveFromBuffer.txt", std::ios_base::app);

    saveTimeRemoveFromBuffer << "[Info] Time when package is remove from buffer: " +
      std::to_string(GetTimeRemoveFromBuffer()) + ", in transmitter: " + std::to_string(GetStationId()) << std::endl;

    saveTimeRemoveFromBuffer.close();
  }

  SaveWaitingTime();
}

void Package::SaveWaitingTime()
{
  size_t package_waiting_time = GetTimeRemoveFromBuffer() - GetTimeAddedToBuffer();

  if (GetTime() >= simulation_->GetStartTimeStatistics())
  {
    // add to file
    std::ofstream saveWaitingTime("SaveWaitingTime.txt", std::ios_base::app);

    saveWaitingTime << "[Info] Time of waiting in buffer before transmission: " +
      std::to_string(package_waiting_time) + ", in transmitter: " + std::to_string(GetStationId()) << std::endl;

    saveWaitingTime.close();
  }

  logger_->Info("Time of waiting in buffer before transmission: " +
    std::to_string(package_waiting_time) + ", in transmitter: " + std::to_string(GetStationId()));
}

void Package::SaveThroughputOfSystem()
{
  double system_throughput = (double)wireless_network_->GetCounterOfPackagesSuccessfullySent() / GetTime();
  
  if (GetTime() >= simulation_->GetStartTimeStatistics())
  {
    // add to file
    std::ofstream saveSystemThroughput("SaveSystemThroughput.txt", std::ios_base::app);

    saveSystemThroughput << "[Info] Actual system throughput: " + std::to_string(system_throughput) << std::endl;

    saveSystemThroughput.close();
  }

  logger_->Info("Actual system throughput: " + std::to_string(system_throughput));
}

void Package::SavePackagesSuccessfullySent()
{
  double package_error_rate = (double)wireless_network_->GetTransmitters(GetStationId())->GetPackagesLost() /
    wireless_network_->GetTransmitters(GetStationId())->GetPackagesSuccessfullySent();

  if (GetTime() >= simulation_->GetStartTimeStatistics())
  {
    // add to file
    std::ofstream savePackagesSent("SavePackagesSent.txt", std::ios_base::app);
    savePackagesSent << "[Info] Packages successfully sent: " +
      std::to_string(wireless_network_->GetTransmitters(GetStationId())->GetPackagesSuccessfullySent()) +
      ", by transmitter: " + std::to_string(GetStationId()) << std::endl;

    savePackagesSent << "[Info] Actual package error rate: " + std::to_string(package_error_rate) +
      ", in transmitter: " + std::to_string(GetStationId()) << std::endl << std::endl;

    savePackagesSent.close();
  }
}

void Package::SavePackagesLost()
{
  double package_error_rate = (double)wireless_network_->GetTransmitters(GetStationId())->GetPackagesLost() /
    wireless_network_->GetTransmitters(GetStationId())->GetPackagesSuccessfullySent();

  if (GetTime() >= simulation_->GetStartTimeStatistics())
  {
    // add to file
    std::ofstream savePackagesSent("SavePackagesSent.txt", std::ios_base::app);
    savePackagesSent << "[Info] Packages lost: " +
      std::to_string(wireless_network_->GetTransmitters(GetStationId())->GetPackagesLost()) +
      ", by transmitter: " + std::to_string(GetStationId()) << std::endl;

    savePackagesSent << "[Info] Actual package error rate: " + std::to_string(package_error_rate) +
      ", in transmitter: " + std::to_string(GetStationId()) << std::endl << std::endl;

    savePackagesSent.close();
  }
}

void Package::Activ(size_t time, bool relative)
{
  if (relative == true)
  {
    time_ += time;
  }
  else
  {
    time_ = time;
  }
  agenda_->push(this);
}

void Package::Execute()
{
  Transmitter* transmitter = wireless_network_->GetTransmitters(id_station_);
  Receiver* receiver = wireless_network_->GetReceivers(id_station_);

  bool active = true;

  while (active)
  {
    switch (state_)
    {
    case State::AppearanceInTheSystem:

      wireless_network_->GeneratePackage(logger_, this, transmitter, rand()%10); // generate and add package to the vector
      {
        // planning the appearance of the next package
        auto new_package = new Package(id_package_ + 1, rand() % 10, time_, logger_, wireless_network_, agenda_, simulation_);
        new_package->Activ(rand() % WirelessNetwork::generate_packet_max_time, true);
      }

      if (transmitter->GetFirstPackageInTX() == this) // if (package is first)
      {
        state_ = State::ChannelListening;
        active = true;
      }
      else
      {
        state_ = State::AppearanceInTheSystem;
        active = false;
      }
      break;

    case State::ChannelListening:

      if (wireless_network_->GetChannelStatus() == false)
      {
        if (transmitter->GetTimeOfChannelListenning() > transmitter->difs_time_)
        {
          logger_->Info("Channel is free more than 4ms");
          Activ(0); // wait for other packages in these same time
          state_ = State::Transmission;
          active = false;
        }
        else
        {
          logger_->Info("Channel isn't free more than 4ms");
          transmitter->IncTimeOfChannelListenning(logger_); // X += 0,5ms
          Activ(5, true); // process sleep for 0,5ms
          state_ = State::ChannelListening;
          active = false;
        }
      }
      else
      {
        logger_->Info("Channel is busy");
        transmitter->SetTimeOfChannelListenning(0);
        Activ(5, true); // process sleep for 0,5ms
        state_ = State::ChannelListening;
        active = false;
      }
      break;

    case State::Transmission:

      SetTimeRemoveFromBuffer(GetTime());
      SaveTimeRemoveFromBuffer();
      wireless_network_->AddPackages(transmitter->GetFirstPackageInTX()); // add package to the vector in channel
      wireless_network_->StartTransmission(logger_); // (channel occupancy = true)
      logger_->Info("Start transmission package (id: " + std::to_string(this->GetPackageId()) + ")");
      Activ(ctpk_time_, true);// process sleep for CTPk time
      state_ = State::Collision;
      active = false;
      break;

    case State::Collision:
      if (wireless_network_->GetBufferSize() == 1 && wireless_network_->GetChannel()->GetMorePackagesInChannel() == false)
      {
        wireless_network_->GetChannel()->SetCollision(false);
        logger_->Info("Collision doesn't detected");
        state_ = State::ReceivePackage;
        active = true;
      }
      else
      {
        wireless_network_->GetChannel()->SetMorePackagesInBuffer(true);
        wireless_network_->GetChannel()->SetCollision(true);
        logger_->Info("Collision detected");

        wireless_network_->EndTransmission(logger_);

        if(wireless_network_->IsBufferEmpty())
        {
          wireless_network_->GetChannel()->SetMorePackagesInBuffer(false);
          wireless_network_->GetChannel()->SetChannelOccupancy(false);
        }

        // prepare to retransmission
        wireless_network_->GetChannel()->SetCollision(false);
        transmitter->SetTimeOfChannelListenning(0);
        Activ(10, true); // wait CTIZ time before retransmission
        state_ = State::Retransmission;
        active = false;
      }
      break;

    case State::ReceivePackage:

      wireless_network_->GetChannel()->ChanceForTER(logger_); // check TER error (if true: collision = true)

      if (wireless_network_->GetChannel()->GetCollision() == false)
      {
        wireless_network_->EndTransmission(logger_); // channel is free (remove package from the vector in channel)

        if(wireless_network_->GetBufferSize() == 0)
        {
          wireless_network_->GetChannel()->SetChannelOccupancy(false);
        }
        state_ = State::ACK;
        active = true;
      }
      else
      {
        wireless_network_->GetChannel()->SetCollision(true);
        logger_->Info("Collision detected");
        // prepare to retransmission
        wireless_network_->GetChannel()->SetChannelOccupancy(false);
        wireless_network_->GetChannel()->SetCollision(false);
        transmitter->SetTimeOfChannelListenning(0);
        state_ = State::Retransmission;
        active = true;
      }
      break;

    case State::Retransmission:
      IncrementNumberOfLR(logger_);
      if (GetNumberOfLR() <= 10) //if there was only 1 package
      {
        logger_->Info("Permission for retransmission");
        transmitter->GenerateCRPTime(logger_, ctpk_time_, number_of_LR_);
        transmitter->SetTimeOfChannelListenning(0);
        Activ(transmitter->GetTimeCrp(), true); // process sleep for CRP time
        state_ = State::ChannelListening;
        active = false;
      }
      else
      {
        logger_->Info("Unable to retransmit again");
        transmitter->AddPackageLost(logger_);
        SavePackagesLost();
        SaveNumberOfLR();
        wireless_network_->GetChannel()->SetChannelOccupancy(false);
        transmitter->SetTimeOfChannelListenning(0);
        state_ = State::RemovalFromTheSystem;
        active = true;
      }
      break;

    case State::ACK:
      if (wireless_network_->GetChannelStatus() == false) // if (channel is free)
      {
        logger_->Info("Permission to send ACK");
        receiver->SetAcknowledgment(true);
        // add package (to the vector in channel) instead of ACK to simplify implementation
        wireless_network_->AddPackages(this);
        wireless_network_->StartTransmission(logger_); // start transmission
        Activ(transmitter->ctiz_time_, true); // process sleep for CTIZ time (1ms)
        state_ = State::ReceiveACK;
        active = false;
      }
      else
      {
        wireless_network_->GetChannel()->SetCollision(true);
        logger_->Info("Collision detected");
        wireless_network_->GetChannel()->SetChannelOccupancy(false);
        wireless_network_->GetChannel()->SetCollision(false);
        transmitter->SetTimeOfChannelListenning(0);
        state_ = State::Retransmission;
        active = true;
      }
      break;

    case State::ReceiveACK:
      //if there is only ACK (after time CTPk + CTIZ) in the channel:
      if (wireless_network_->GetBufferSize() == 1)
      {
        wireless_network_->EndTransmission(logger_); // channel is free (remove ACK from the vector in channel)
        wireless_network_->GetChannel()->SetChannelOccupancy(false);
        logger_->Info("ACK delivered successfully");
        SetTimeSuccessfullySentPackage(GetTime());
        transmitter->AddPackageSuccessfullySent(logger_);
        SavePackagesSuccessfullySent();
        wireless_network_->IncrementCounterOfPackagesSuccessfullySent();
        SaveTimeSuccessfullySentPackage();
        SaveNumberOfLR();
        SaveThroughputOfSystem();
        transmitter->SetTimeOfChannelListenning(0);
        receiver->SetAcknowledgment(false);
        state_ = State::RemovalFromTheSystem;
        active = true;
      }
      else
      {
        wireless_network_->GetChannel()->SetCollision(true);
        logger_->Info("Collision detected");
        wireless_network_->EndTransmission(logger_); // channel is free (remove ACK from the vector in channel)
        wireless_network_->GetChannel()->SetChannelOccupancy(false);
        transmitter->SetTimeOfChannelListenning(0);
        wireless_network_->GetChannel()->SetCollision(false);
        state_ = State::Retransmission;
        active = true;
      }
      break;

    case State::RemovalFromTheSystem:
      if(!wireless_network_->IsBufferEmpty()) // if (buffer isn't empty)
      {
        // wake up next packet in buffer in current time
        wireless_network_->GetFirstPackage()->Activ(time_, false);
      }
      SetTerminated();
      active = false;
      break;

    default:
      logger_->Error("In PacketProcess Execute !  Transmitter id: " + std::to_string(id_station_) +
        "  Package id: " + std::to_string(id_package_) + "\n");
      active = false;
      break;
    }
  }
}