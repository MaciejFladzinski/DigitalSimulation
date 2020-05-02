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
        transmitter->CheckDIFSTime(logger_);

        // if (channel is free > 4ms), but now "true/false" only for simulation test
        if (true)
        {
          logger_->Info("Channel is free more than 4ms");
          state_ = State::Transmission;
          active = true;
        }
        else
        {
          logger_->Info("Channel isn't free more than 4ms");
          transmitter->Wait(logger_);
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

      if (wireless_network_->GetChannel()->GetCollision() == true)
      {
        logger_->Info("Collision detected");
        state_ = State::Retransmission;
        active = true;
      }
      else
      {
        logger_->Info("No collision detected");

        if(wireless_network_->GetChannelStatus() == false) // if(channel is free)
        {
          wireless_network_->GetChannel()->SetChannelOccupancy(true); // now: channel is busy
          // add: package to vector in channel (package currently transmitted)
          logger_->Info("Package is sending, wait for ACK");
          state_ = State::ACK;
          active = true;
        }
        else
        {
          transmitter->Wait(logger_);
          state_ = State::ChannelListening;
          active = true;
        }
      }
      break;

    case State::Retransmission:
      // Retransmission operations
      printf("Retransmission: \n");

      // 1. zwieksz licznik retransmisji o 1
      logger_->Info("++number_of_retransmission");

      // 2. sprawdz zgodnosc warunku LR <= 10
      logger_->Info("If number_of_retransmission > 10: go to RemovalFromTheSystem");

      // 3. wyznacz czas CRP
      logger_->Info("Calculating CRP time");

      // 4. czekaj okreslony czas CRP
      logger_->Info("Wait CRP time...");

      // Test: incrementation number of LR, Error when LR>10
      for (int i = 0; i < 10; i++)
      {
        //Retransmission(logger_, 0);
      }
      printf("Tested error: \n");
      //Retransmission(logger_, 0);

      // 5. przejdz do state ChannelListenning lub RemovalFromTheSystem
      logger_->Info("Go to ChannelListenning \n");

      active = true;
      state_ = State::ACK; // it's only for compilation
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
        transmitter->AddPackageSuccessfullySent(logger_);
        logger_->Info("Packages successfully sent: "+std::to_string(transmitter->GetPackagesSuccessfullySent()));
        active = true;
        state_ = State::RemovalFromTheSystem;
      }
      else
      {
        logger_->Info("ACK wasn't received");
        wireless_network_->GetChannel()->SetChannelOccupancy(false);
        active = true;
        state_ = State::Retransmission;
      }
      break;

    case State::RemovalFromTheSystem:
      // Removal from the system operations
      printf("RemovalFromTheSystem: \n");

      // 1. zwolnij kanal
      logger_->Info("Release the channel");

      // 2. usuñ pakiet z kolejki FIFO
      logger_->Info("Remove package from FIFO queue");

      // Test: success
      printf("Test correct transmission: \n");
      //SetCorrectReceptionAck(true);
      //RemovePackage(logger_, 0);
      // Test: error
      printf("Test error transmission: \n");
      //SetCorrectReceptionAck(false);
      //RemovePackage(logger_, 0);

      // 3. jeœli w kolejce znajduje siê inny pakiet, rozpocznij jego transmisjê
      logger_->Info("If there is another packet in the queue: go to state ChannelListenning, if no: end the transmission \n");

      is_terminated_ = true;
      active = false;
      break;

    default:
      logger_->Error("In PacketProcess Execute !\n");

      active = false;
      break;
    }
  }
}
