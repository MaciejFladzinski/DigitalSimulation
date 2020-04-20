#include "packetprocess.h"

#include <iostream>

PacketProcess::PacketProcess(size_t time, Logger* logger)
{
  activation_time_ = time;
  logger_ = logger;
}

PacketProcess::~PacketProcess()
{
  
}

void PacketProcess::Execute()
{
  bool active = true;

  logger_->Info("Packet Process Execute");

  while(active)
  {
    switch(state_)
    {
      // before all break set active = true/false + Activ(time) if it's required

    case State::AppearanceInTheSystem:
      // Appearance in the system operations

      // 1. pojawienie sie pakietu i dodanie go do kolejki FIFO
      logger_->Info("Generate package, add to FIFO queue");

      // 2. jeœli kana³ transmisyjny jest wolny rozpocznij transmisjê najstarszego pakietu
      logger_->Info("Start transmission");

      state_ = State::Transmission;
      break;

    case State::Transmission:
      // Transmission operations

      // 1. przesy³aj pakiet okreœlon¹ jednostkê czasu (CTPk)
      logger_->Info("CTPk transmission time...");

      // 2. w przypadku niepowodzenia wykonaj retransmisjê pakietu (maksymalnie LR=10 razy)
      logger_->Info("Retransmission");

      state_ = State::RemovalFromTheSystem;
      active = true;
      break;

    case State::RemovalFromTheSystem:
      // Removal from the system operations

      // 1. zwolnij kanal
      std::cout << "zwolnij kanal \n";

      // 2. usuñ pakiet z kolejki FIFO
      std::cout << "usun pakiet z kolejki FIFO \n";

      // 3. jeœli w kolejce znajduje siê inny pakiet, rozpocznij jego transmisjê
      std::cout << "jesli w kolejce znajduje sie inny pakiet, rozpocznij jego transmisje \n";

      // 4. jeœli nie - opuœæ system
      std::cout << "jesli nie - opusc system \n\n";

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

void PacketProcess::Activ(size_t time)
{
  activation_time_ += time;
}
