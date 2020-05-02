#include "package.h"

#include <iostream>

#include "wirelessNetwork.h"
#include "channel.h"

Package::Package(unsigned int id_package, unsigned int id_station, Logger* logger, WirelessNetwork* wireless_network)
{
  id_package_ = id_package;
  id_station_ = id_station;
  wireless_network_ = wireless_network;
  logger_ = logger;

  logger->Info("Package nr: " + std::to_string(id_package) +
    " (in station nr: " + std::to_string(id_station) + ") has been created");
}

Package::~Package()
{
  logger_->Info("Remove package");
}

void Package::IncrementNumberOfLR(Logger* logger)
{
  logger_ = logger;
  ++number_of_LR_;
  logger->Info("Package retransmission attempt... attempt nr: " + std::to_string(number_of_LR_));
}


void Package::Activ(unsigned long long time)
{
  activation_time_ += time;
}

void Package::Execute()
{
  Transmitter* transmitter = wireless_network_->GetTransmitters(id_station_);
  Receiver* receiver = wireless_network_->GetReceivers(id_station_);

  bool active = true;

  std::cout << std::endl;
  logger_->Info("Packet Process Execute:");

  while (active)
  {
    switch (state_)
    {
      // tymczasowo pakiet jest sztywno generowany przy tworzeniu obiektu Simulation

      /*
    case State::AppearanceInTheSystem:
      // Appearance in the system operations
      printf("AppearanceInTheSystem: \n");

      // 1. pojawienie sie pakietu i dodanie go do kolejki FIFO
      logger_->Info("Generate package and add it to FIFO queue");
      //GeneratePackage(logger_);

      // 2. planowanie pojawienia sie nastpenego pakietu
      logger_->Info("Planning appears the next package");

      // 3. przejdz do State::ChannelListenning
      logger_->Info("Go to ChannelListenning \n");

      // Add: if
      state_ = State::ChannelListening;
      active = true;
      break;
      */

    case State::ChannelListening:
      // Channel listening operations
      printf("Channel listening: \n");

      // 1. co 0,5ms sprawdzaj czy kanal jest wolny
      // 2. sprawdzenie, czy kanal jest wolny dluzej niz DIFS = 4ms
      // 3. jesli zalozenie jest spelnione przejdz do State::Transmission, jeœli nie kontynuuj sprawdzanie

      if (wireless_network_->GetChannelStatus() == false) // if(channel is free)
      {
        logger_->Info("Channel is free");

        // if (X > DIFS)
        if (transmitter->GetTimeOfChannelListenning() > transmitter->difs_time_)
        {
          logger_->Info("Channel is free more than 4ms");
          state_ = State::Transmission;
          active = true;
        }
        else
        {
          logger_->Info("Channel isn't free more than 4ms");
          transmitter->Wait(logger_); // Process sleep for 5ms (add: active = false ?)
          transmitter->IncTimeOfChannelListenning(logger_); // X += 5ms
          state_ = State::ChannelListening;
          active = true;
        }
      }
      else
      {
        logger_->Info("Channel is busy");
        transmitter->Wait(logger_);
        state_ = State::ChannelListening;
        active = true;
      }
      break;

    case State::Transmission:
      // Transmission operations
      printf("Transmission: \n");

      // 1. pobierz najstarszy pakiet z kolejki FIFO
      // 2. wyznacz CTPk (czas transmisji pakietu)
      // 3. wysylaj pakiet przez okreslony czas (CTPk)
      // 4. jesli po czasie CTPk+CTIZ (dla CTIZ = 1ms) odebrano ACK przejdz do RemovalFromTheSystem, jesli nie- Retransmission

      if(transmitter->GetTransmissionOfAnotherPackage() == true) // if there is another package (currently transmissing)
      {
        wireless_network_->GetChannel()->SetCollision(true);
        logger_->Info("Collision detected");
        state_ = State::Retransmission;
        active = true;
      }
      else
      {
        logger_->Info("No collision detected");

        if(wireless_network_->GetChannelStatus() == false) // if(channel is free)
        {
          wireless_network_->GetChannel()->SetChannelOccupancy(true); // now channel is busy
          transmitter->SetTransmissionOfAnotherPackage(true); // blocking transmission for another package
          logger_->Info("Package is sending, wait for ACK");
          state_ = State::ACK;
          active = true;
        }
        else
        {
          transmitter->Wait(logger_);
          transmitter->SetTimeOfChannelLitenning(0);
          state_ = State::ChannelListening;
          active = true;
        }
      }
      break;

    case State::Retransmission:
      // Retransmission operations
      printf("Retransmission: \n");

      // 1. zwieksz licznik retransmisji o 1
      // 2. sprawdz zgodnosc warunku LR <= 10
      // 3. wyznacz czas CRP
      // 4. czekaj okreslony czas CRP
      // 5. przejdz do state ChannelListenning lub RemovalFromTheSystem

      IncrementNumberOfLR(logger_);

      if(GetNumberOfLR() <= 10)
      {
        logger_->Info("Permission for retransmission");
        transmitter->CRPTime(logger_);
        transmitter->SetTimeOfChannelLitenning(0);
        active = true;
        state_ = State::ChannelListening;
      }
      else
      {
        logger_->Info("Unable to retransmit again");
        transmitter->AddPackageLost(logger_);
        logger_->Info("Packages lost: " + std::to_string(transmitter->GetPackagesLost()));
        active = true;
        state_ = State::RemovalFromTheSystem;
      }
      break;

    case State::ACK:
      // ACK operations
      printf("ACK: \n");

      // 1. wygeneruj potwierdzenie ACK
      // 2. poddaj go transmisji przez okreslona jednostke czasu (CTIZ)
      // 3. przejdz do state RemovalFromTheSystem

      transmitter->CheckTransmissionPackageTime(logger_); // checking max time of package transmission + receive ACK (CTPk+CTIZ)
      receiver->SetAcknowledgment(true);

      // check: if(ACK is received in time: CTPk+CTIZ)
      if(true)
      {
        logger_->Info("ACK successfully sent");
        wireless_network_->GetChannel()->SetChannelOccupancy(false);
        transmitter->SetTransmissionOfAnotherPackage(false);
        transmitter->AddPackageSuccessfullySent(logger_);
        logger_->Info("Packages successfully sent: "+std::to_string(transmitter->GetPackagesSuccessfullySent()));
        active = true;
        state_ = State::RemovalFromTheSystem;
      }
      else
      {
        logger_->Info("ACK wasn't received");
        wireless_network_->GetChannel()->SetChannelOccupancy(false);
        transmitter->SetTimeOfChannelLitenning(0);
        active = true;
        state_ = State::Retransmission;
      }
      break;

    case State::RemovalFromTheSystem:
      // Removal from the system operations
      printf("RemovalFromTheSystem: \n");

      // 1. zwolnij kanal
      // 2. usuñ pakiet z kolejki FIFO
      // 3. jeœli w kolejce znajduje siê inny pakiet, rozpocznij jego transmisjê

      is_terminated_ = true;
      logger_->Info("The process has completed correctly \n");
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
