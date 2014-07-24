/*
  ==============================================================================

    RandomNumberServiceThread.cpp
    Created: 23 Jul 2014 4:56:45pm
    Author:  johnt_000

  ==============================================================================
*/

#include "RandomNumberServiceThread.h"

using namespace MplusM::Example;

RandomNumberServiceThread::RandomNumberServiceThread() : Thread("RandomNumberServiceThread")
{
}

RandomNumberServiceThread::~RandomNumberServiceThread()
{
	stopThread(2000);
}

void RandomNumberServiceThread::run()
{
	yarp::os::Network yarp;

	yarp::os::ConstString serviceEndpointName;
	yarp::os::ConstString servicePortNumber;

	const char* argv = " ";
	MplusM::Common::Initialize(argv);
	serviceEndpointName = DEFAULT_RANDOM_SERVICE_NAME; //todo: set this

	keepGoing = true;

	RandomNumberService *stuff = new RandomNumberService(argv, serviceEndpointName, servicePortNumber);

	if (stuff)
		if (stuff->start())
		{
			yarp::os::ConstString channelName(stuff->getEndpoint().getName());
			DBG("channelName = ", channelName.c_str());
			if (MplusM::Common::RegisterLocalService(channelName))
			{
				MplusM::StartRunning();
				MplusM::Common::SetSignalHandlers(MplusM::SignalRunningStop);
				stuff->startPinger();
				for ( ; MplusM::IsRunning() && stuff && !threadShouldExit(); )
				{
					yarp::os::Time::yield();
				}
				DBG("exit called; unregistering port...");
				MplusM::Common::UnregisterLocalService(channelName);
				stuff->stop();
			}
		}

	yarp.fini();
}

