#include "wirelessNetwork.h"

#include "transmitter.h"
#include "receiver.h"
#include "channel.h"

WirelessNetwork::WirelessNetwork()
{
	for (int i = 0; i < k_number_of_stations_; i++)
	{
		auto transmitter = new Transmitter(i);
		transmitters.push_back(transmitter);
		auto receiver = new Receiver(i);
		receivers.push_back(receiver);
	}
	auto channel = new Channel();
}

WirelessNetwork::~WirelessNetwork()
{
  
}
