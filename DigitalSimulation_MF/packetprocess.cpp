#include "packetprocess.h"

#include <iostream>

PacketProcess::PacketProcess(size_t time, Logger* logger) : Process(time), logger_(logger)
{
  
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
      // Appearance in the system operations:

      // 1. zaplanuj pojawienie sie nastepnego pakietu
      std::cout << "zaplanuj pojawienie sie nastepnego pakietu \n";

      // 2. dodaj pakiet do kolejki FIFO
      std::cout << "dodaj pakiet do kolejki FIFO \n";

      // 3. je�li kana� transmisyjny jest wolny rozpocznij transmisj� najstarszego pakietu
      std::cout << "jesli kanal transmisyjny jest wolny rozpocznij transmisje najstarszego pakietu \n\n";
      //if (channel_occupancy_ == FALSE)

      state_ = State::Transmission;
      active = true;
      break;

    case State::Transmission:
      // Transmission operations:

      // 1. przesy�aj pakiet okre�lon� jednostk� czasu (CTPk)
      std::cout << "przesylaj pakiet okre�lona jednostke czasu (CTPk) \n";

      // 2. w przypadku niepowodzenia wykonaj retransmisj� pakietu (maksymalnie LR=10 razy)
      std::cout << "w przypadku niepowodzenia wykonaj retransmisje pakietu (maksymalnie LR=10 razy) \n\n";

      state_ = State::RemovalFromTheSystem;
      active = true;
      break;

    case State::RemovalFromTheSystem:
      // Removal from the system operations:

      // 1. zwolnij kanal
      std::cout << "zwolnij kanal \n";

      // 2. usu� pakiet z kolejki FIFO
      std::cout << "usun pakiet z kolejki FIFO \n";

      // 3. je�li w kolejce znajduje si� inny pakiet, rozpocznij jego transmisj�
      std::cout << "jesli w kolejce znajduje sie inny pakiet, rozpocznij jego transmisje \n";

      // 4. je�li nie - opu�� system
      std::cout << "jesli nie - opusc system \n\n";

      //is_terminated_ = true;

      active = false;
      break;

    default:
      logger_->Error("In PacketProcess Execute !\n");

      active = false;
      break;
    }
  }
}
