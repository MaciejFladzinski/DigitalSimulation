#include "wirelessNetwork.h"

#include "transmitter.h"
#include "receiver.h"
#include "channel.h"
#include "package.h"

WirelessNetwork::WirelessNetwork()
{
	for (int i = 0; i < k_number_of_stations_; i++)
	{
		//auto transmitter = new Transmitter(i);
		//transmitters_ptr_.push_back(transmitter);

		//auto receiver = new Receiver(i);
		//receivers_ptr_.push_back(receiver);

		//auto package = new Package(i, 0);
		//packages_.push_back(package);
	}
	//auto channel = new Channel();
}

WirelessNetwork::~WirelessNetwork()
{
  
}
