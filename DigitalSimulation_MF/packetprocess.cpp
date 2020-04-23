#include "packetprocess.h"

PacketProcess::PacketProcess(unsigned __int64 time, Logger* logger, WirelessNetwork* wireless_network)
  : Transmitter(0), Receiver(0)
{
  activation_time_ = time;
  logger_ = logger;
}

PacketProcess::~PacketProcess()
{
  
}

void PacketProcess::Activ(unsigned long long time)
{
  activation_time_ += time;
}


void PacketProcess::Execute()
{
  bool active = true;

  logger_->Info("Packet Process Execute: \n");

  while(active)
  {
    switch(state_)
    {
      // before all break set active = true/false + Activ(time) if it's required

    case State::AppearanceInTheSystem:
      // Appearance in the system operations
      printf("AppearanceInTheSystem: \n");

      // 1. pojawienie sie pakietu i dodanie go do kolejki FIFO
      logger_->Info("Generate package and add it to FIFO queue");
      GeneratePackage(logger_);
      // test incrementation package ID
      GeneratePackage(logger_);
      GeneratePackage(logger_);

      // 2. planowanie pojawienia sie nastpenego pakietu
      logger_->Info("Planning appears the next package");

      // 3. przejdz do State::ChannelListenning
      logger_->Info("Go to ChannelListenning \n");

      // Add: if
      state_ = State::ChannelListening;
      active = true;
      break;

    case State::ChannelListening:
      // Channel listening operations
      printf("ChannelListenning: \n");

      // 1. co 0,5ms sprawdzaj czy kanal jest wolny
      logger_->Info("Checking channel every 0,5ms");

      CheckingChannel(logger_);

      // 2. sprawdzenie, czy kanal jest wolny dluzej niz DIFS = 4ms
      logger_->Info("Checking if the channel is free for more than DIFS = 4ms");

      // 3. jesli zalozenie jest spelnione przejdz do State::Transmission, jeœli nie kontynuuj sprawdzanie
      logger_->Info("If true: go to Transmission, if false: go to ChannelListenning \n");

      if (GetChannelOccupancy() == false)
      {
        active = true;
        state_ = State::Transmission;
      }
      else
      {
        active = false; // process sleep
      }

      break;

    case State::Transmission:
      // Transmission operations
      printf("Transmission: \n");

      // 1. pobierz najstarszy pakiet z kolejki FIFO
      logger_->Info("Pull the oldest package from the FIFO queue");

      // 2. wyznacz CTPk (czas transmisji pakietu)
      logger_->Info("Calculation CTPk time");

      // 3. wysylaj pakiet przez okreslony czas (CTPk)
      logger_->Info("Send package for a CTPk time");

      StartTransmission(logger_,0);

      // 4. jesli po czasie CTPk+CITZ (gdzie CITZ = 1ms) odebrano ACK przejdz do RemovalFromTheSystem, jesli nie to do Retransmission
      logger_->Info("Wait CTIZ time...");
      logger_->Info("If received ACK in these time: go to state RemovalFromTheSystem, if no: go to state Retransmission \n");

      // Add: if...

      active = true;
      state_ = State::Retransmission;
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
        Retransmission(logger_, 0);
      }
      printf("Tested error: \n");
      Retransmission(logger_, 0);

      // 5. przejdz do state ChannelListenning lub RemovalFromTheSystem
      logger_->Info("Go to ChannelListenning \n");

      active = true;
      state_ = State::ACK; // it's only for compilation
      break;

    case State::ACK:
      // ACK operations
      printf("ACK: \n");

      // 1. wygeneruj potwierdzenie ACK
      logger_->Info("Generate ACK");
      GenerateACK(logger_);

      // 2. poddaj go transmisji przez okreslona jednostke czasu (CTIZ)
      logger_->Info("Send ACK for a CTIZ time");

      // 3. przejdz do state RemovalFromTheSystem
      logger_->Info("Go to state RemovalFromTheSystem \n");

      active = true;
      state_ = State::RemovalFromTheSystem;
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
      SetCorrectReceptionAck(true);
      RemovePackage(logger_, 0);
      // Test: error
      printf("Test error transmission: \n");
      SetCorrectReceptionAck(false);
      RemovePackage(logger_, 0);

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