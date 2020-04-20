#include "packetprocess.h"

#include <iostream>

#include "wirelessNetwork.h"

PacketProcess::PacketProcess(size_t time, size_t* time_ptr, Logger* logger) : Process(0,time_ptr)
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

      // 2. je�li kana� transmisyjny jest wolny rozpocznij transmisj� najstarszego pakietu
      logger_->Info("Start transmission");

      state_ = State::Transmission;
      break;

    case State::Transmission:
      // Transmission operations

      // 1. przesy�aj pakiet okre�lon� jednostk� czasu (CTPk)
      logger_->Info("CTPk transmission time...");

      // 2. w przypadku niepowodzenia wykonaj retransmisj� pakietu (maksymalnie LR=10 razy)
      logger_->Info("Retransmission");

      state_ = State::RemovalFromTheSystem;
      active = true;
      break;

    case State::RemovalFromTheSystem:
      // Removal from the system operations

      // 1. zwolnij kanal
      logger_->Info("Release the channel");

      // 2. usu� pakiet z kolejki FIFO
      logger_->Info("Remove package from FIFO queue");

      // 3. je�li w kolejce znajduje si� inny pakiet, rozpocznij jego transmisj�
      logger_->Info("If there is another packet in the queue, start transmitting it");

      // 4. je�li nie - opu�� system
      logger_->Info("If no- leave the system \n");

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