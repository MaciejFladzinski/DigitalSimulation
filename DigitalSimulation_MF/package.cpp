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

void Package::StepInto()
{
  //logger_->Info("Simulation time: " + std::to_string(clock_));
  printf("\nPress any key to continue... \n\n");
  getchar();
}

bool Package::SelectMode(int mode)
{
  if (mode == 1)
  {
    return true;
  }
  else if (mode == 2)
  {
    return false;
  }
  else
  {
    printf("Wrong number, try again \n\n");
    printf("Select simulation mode:\n1- step into\n2- step over\n");
    int key;
    std::cin >> key;
    SelectMode(key);
  }
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

  printf("\nSelect simulation mode:\n1- step into\n2- step over\n");
  int key;
  std::cin >> key;
  std::cout << std::endl;

  if (SelectMode(key) == true) { StepInto(); }
  logger_->Info("Packet Process Execute:");

  while (active)
  {
    switch (state_)
    {
    case State::AppearanceInTheSystem:
      // Appearance in the system operations

      // 1. pojawienie sie pakietu i dodanie go do kolejki FIFO
      // 2. planowanie pojawienia sie nastpenego pakietu
      // 3. dodanie pakietu do bufora
      // 4. przejdz do State::ChannelListenning

      wireless_network_->GeneratePackage(logger_, this, id_station_);
      {
        auto new_id = id_package_ + 1;
        auto new_package = new Package(new_id, id_station_, ctpk_time_, logger_, wireless_network_, agenda_);
        wireless_network_->AddPackages(new_package);  // add package to vector in buffer
        new_package->Activ(rand() % WirelessNetwork::generate_packet_max_time);
      }
      if (SelectMode(key) == true) { StepInto(); }
      state_ = State::ChannelListening;
      break;

    case State::ChannelListening:
      // Channel listening operations

      // 1. co 0,5ms sprawdzaj czy kanal jest wolny
      // 2. sprawdzenie, czy kanal jest wolny dluzej niz DIFS = 4ms
      // 3. jesli zalozenie jest spelnione przejdz do State::Transmission, jeœli nie kontynuuj sprawdzanie

      if (wireless_network_->GetChannelStatus() == false)
      {
        logger_->Info("Channel is free");

        if (transmitter->GetTimeOfChannelListenning() > transmitter->difs_time_)
        {
          logger_->Info("Channel is free more than 4ms");
          if (SelectMode(key) == true) { StepInto(); }
          state_ = State::Transmission;
        }
        else
        {
          logger_->Info("Channel isn't free more than 4ms");
          transmitter->Wait(logger_); // Process sleep for 5ms (add: active = false ?)
          Activ(5); // process sleep for 0,5ms
          transmitter->IncTimeOfChannelListenning(logger_); // X += 0,5ms
          if (SelectMode(key) == true) { StepInto(); }
          state_ = State::ChannelListening;
        }
      }
      else
      {
        logger_->Info("Channel is busy");
        transmitter->Wait(logger_); // Process sleep for 5ms
        Activ(5); // process sleep for 0,5ms
        if (SelectMode(key) == true) { StepInto(); }
        state_ = State::ChannelListening;
      }
      break;

    case State::Transmission:
      // Transmission operations

      // 1. pobierz najstarszy pakiet z kolejki FIFO
      // 2. wyznacz CTPk (czas transmisji pakietu)
      // 3. wysylaj pakiet przez okreslony czas (CTPk)

      if (wireless_network_->GetChannelStatus() == false) // if(channel is free)
      {
        logger_->Info("No collision detected");

        wireless_network_->StartTransmission(logger_);
        Activ(ctpk_time_);// process sleep for CTPk time

        wireless_network_->GetChannel()->ChanceForTER(logger_); // check TER error
        
        if (wireless_network_->GetChannel()->GetCollision() == false)
        {
          wireless_network_->GetChannel()->SetChannelOccupancy(false); // channel is free
          if (SelectMode(key) == true) { StepInto(); }
          state_ = State::ACK;
        }
        else
        {
          wireless_network_->GetChannel()->SetChannelOccupancy(false); // channel is free
          wireless_network_->GetChannel()->SetCollision(false);
          transmitter->SetTimeOfChannelListenning(0);
          if (SelectMode(key) == true) { StepInto(); }
          state_ = State::Retransmission;
        }
      }
      else
      {
        wireless_network_->GetChannel()->SetCollision(true);
        logger_->Info("Collision detected");
        wireless_network_->GetChannel()->SetChannelOccupancy(false); // channel is free
        wireless_network_->GetChannel()->SetCollision(false);
        transmitter->SetTimeOfChannelListenning(0);
        if (SelectMode(key) == true) { StepInto(); }
        state_ = State::Retransmission;
      }
      break;

    case State::Retransmission:
      // Retransmission operations

      // 1. zwieksz licznik retransmisji o 1
      // 2. sprawdz zgodnosc warunku LR <= 10
      // 3. wyznacz czas CRP
      // 4. czekaj okreslony czas CRP
      // 5. przejdz do state ChannelListenning lub RemovalFromTheSystem

      IncrementNumberOfLR(logger_);

      if(GetNumberOfLR() <= 10)
      {
        logger_->Info("Permission for retransmission");
        transmitter->GenerateCRPTime(logger_,ctpk_time_,number_of_LR_);
        Activ(transmitter->GetTimeCrp()); // process sleep for CRP time
        transmitter->SetTimeOfChannelListenning(0);
        if (SelectMode(key) == true) { StepInto(); }
        state_ = State::ChannelListening;
      }
      else
      {
        logger_->Info("Unable to retransmit again");
        transmitter->AddPackageLost(logger_);
        transmitter->SetTimeOfChannelListenning(0);
        if (SelectMode(key) == true) { StepInto(); }
        state_ = State::RemovalFromTheSystem;
      }
      break;

    case State::ACK:
      // ACK operations

      // 1. wygeneruj potwierdzenie ACK
      // 2. poddaj go transmisji przez okreslona jednostke czasu (CTIZ)
      // 3. jesli po czasie CTPk+CTIZ (dla CTIZ = 1ms) odebrano ACK przejdz do RemovalFromTheSystem, jesli nie- Retransmission

      if (wireless_network_->GetChannelStatus() == false)
      {
        logger_->Info("Package successfully sent");
        receiver->SetAcknowledgment(true); // permission to send ACK
        logger_->Info("Permission to send ACK");
        wireless_network_->GetChannel()->SetChannelOccupancy(true); // ACK in channel
        logger_->Info("CTIZ time: 1ms");
        Activ(transmitter->ctiz_time_); // process sleep for CTIZ time (1ms)

        //if there is no collision after time CTPk + CTIZ in the channel:
        if (wireless_network_->GetChannel()->GetCollision() == false)
        {
          wireless_network_->GetChannel()->SetChannelOccupancy(false); // ACK delivered
          logger_->Info("ACK delivered successfully");
          transmitter->AddPackageSuccessfullySent(logger_);
          transmitter->SetTimeOfChannelListenning(0);
          receiver->SetAcknowledgment(false);
          if (SelectMode(key) == true) { StepInto(); }
          state_ = State::RemovalFromTheSystem;
        }
        else
        {
          wireless_network_->GetChannel()->SetCollision(true);
          logger_->Info("Collision detected");
          wireless_network_->GetChannel()->SetChannelOccupancy(false); // ACK not delivered
          transmitter->SetTimeOfChannelListenning(0);
          wireless_network_->GetChannel()->SetCollision(false);
          if (SelectMode(key) == true) { StepInto(); }
          state_ = State::Retransmission;
        }
      }
      else
      {
        receiver->SetAcknowledgment(false); // no permission to send ACK
        logger_->Info("No permission to send ACK");
        wireless_network_->GetChannel()->SetChannelOccupancy(false);
        transmitter->SetTimeOfChannelListenning(0);
        if (SelectMode(key) == true) { StepInto(); }
        state_ = State::Retransmission;
      }
      break;

    case State::RemovalFromTheSystem:
      // Removal from the system operations

      // 1. zwolnij kanal
      // 2. usuñ pakiet z kolejki FIFO
      // 3. jeœli w kolejce znajduje siê inny pakiet, rozpocznij jego transmisjê

      wireless_network_->EndTransmission(logger_);
      /*
      if(!wireless_network_->GetPackagesPtr()->empty()) // if buffer isn't empty
      {
        // wake up next packet in buffer in current time
        wireless_network_->GetPackagesPtr()->front()->Activ(time_, true);
      }
      */
      SetTerminated();
      if (SelectMode(key) == true) { StepInto(); }
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
