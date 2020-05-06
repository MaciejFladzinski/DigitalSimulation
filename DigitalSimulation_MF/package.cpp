#include "package.h"

#include <iostream>

#include "wirelessNetwork.h"
#include "channel.h"

Package::Package(unsigned int id_package, unsigned int id_station, size_t time,
  Logger* logger, WirelessNetwork* wireless_network, Agenda* agenda)
{
  id_package_ = id_package;
  id_station_ = id_station;
  time_ = time;
  wireless_network_ = wireless_network;
  logger_ = logger;
  agenda_ = agenda;

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
        auto new_package = new Package(id_package_, id_station_, time_, logger_, wireless_network_, agenda_);
        new_package->Activ(time_ + rand() % WirelessNetwork::generate_packet_max_time);
      }

      if (transmitter->GetFirstPackageInTX()) // if (package is first)
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
        logger_->Info("Channel is free");

        if (transmitter->GetTimeOfChannelListenning() > transmitter->difs_time_)
        {
          logger_->Info("Channel is free more than 4ms");
          wireless_network_->AddPackages(this); // add package to the vector in channel
          state_ = State::Transmission;
          active = true;
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
        Activ(5, true); // process sleep for 0,5ms
        state_ = State::ChannelListening;
        active = false;
      }
      break;

    case State::Transmission:

      if (wireless_network_->GetBufferSize() == 1) // if (vector in channel have 1 package)
      {
        wireless_network_->StartTransmission(logger_); // (channel occupancy = true)
        Activ(ctpk_time_, true);// process sleep for CTPk time
        active = false;

        // check second time (if 2 packages was added to the vector in these same time)
        if (wireless_network_->GetBufferSize() == 1)
        {
          wireless_network_->GetChannel()->ChanceForTER(logger_); // check TER error (if true: collision = true)

          if (wireless_network_->GetChannel()->GetCollision() == false)
          {
            wireless_network_->EndTransmission(logger_); // channel is free (remove package from the vector in channel)
            state_ = State::ACK;
          }
          else
          {
            // prepare to retransmission
            wireless_network_->EndTransmission(logger_); // channel is free (remove package from the vector in channel)
            wireless_network_->GetChannel()->SetCollision(false);
            transmitter->SetTimeOfChannelListenning(0);
            state_ = State::Retransmission;
            active = true;
          }
        }
        else
        {
          wireless_network_->GetChannel()->SetCollision(true);
          logger_->Info("Collision detected");
          // prepare to retransmission
          wireless_network_->EndTransmission(logger_); // channel is free (remove package from the vector in channel)
          wireless_network_->GetChannel()->SetCollision(false);
          transmitter->SetTimeOfChannelListenning(0);
          state_ = State::Retransmission;
          active = true;
        }
      }
      else
      {
        wireless_network_->StartTransmission(logger_); // (channel occupancy = true)
        wireless_network_->GetChannel()->SetCollision(true);
        logger_->Info("Collision detected");
        Activ(ctpk_time_, true);// process sleep for CTPk time
        // prepare to retransmission
        wireless_network_->EndTransmission(logger_); // channel is free (remove package from the vector in channel)
        wireless_network_->GetChannel()->SetCollision(false);
        transmitter->SetTimeOfChannelListenning(0);
        state_ = State::Retransmission;
        active = false;
      }
      break;

    case State::Retransmission:

      IncrementNumberOfLR(logger_);

      if(GetNumberOfLR() <= 10)
      {
        logger_->Info("Permission for retransmission");
        transmitter->GenerateCRPTime(logger_,ctpk_time_,number_of_LR_);
        transmitter->SetTimeOfChannelListenning(0);
        Activ(transmitter->GetTimeCrp(), true); // process sleep for CRP time
        state_ = State::ChannelListening;
        active = false;
      }
      else
      {
        logger_->Info("Unable to retransmit again");
        transmitter->AddPackageLost(logger_);
        transmitter->SetTimeOfChannelListenning(0);
        state_ = State::RemovalFromTheSystem;
        active = false;
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
        Activ(transmitter->ctiz_time_, false); // process sleep for CTIZ time (1ms)
        active = false;

        //if there is only ACK (after time CTPk + CTIZ) in the channel:
        if (wireless_network_->GetBufferSize() == 1)
        {
          wireless_network_->EndTransmission(logger_); // channel is free (remove ACK from the vector in channel)
          logger_->Info("ACK delivered successfully");
          transmitter->AddPackageSuccessfullySent(logger_);

          transmitter->SetTimeOfChannelListenning(0);
          receiver->SetAcknowledgment(false);
          state_ = State::RemovalFromTheSystem;
          active = false;
        }
        else
        {
          wireless_network_->GetChannel()->SetCollision(true);
          logger_->Info("Collision detected");

          wireless_network_->EndTransmission(logger_); // channel is free (remove ACK from the vector in channel)
          transmitter->SetTimeOfChannelListenning(0);
          wireless_network_->GetChannel()->SetCollision(false);
          state_ = State::Retransmission;
        }
      }
      else
      {
        receiver->SetAcknowledgment(false); // no permission to send ACK
        logger_->Info("No permission to send ACK");
        wireless_network_->GetChannel()->SetChannelOccupancy(false);
        transmitter->SetTimeOfChannelListenning(0);
        state_ = State::Retransmission;
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
