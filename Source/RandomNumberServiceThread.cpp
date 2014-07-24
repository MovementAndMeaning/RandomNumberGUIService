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
    stuff = NULL;
}

RandomNumberServiceThread::~RandomNumberServiceThread()
{
	DBG("calling thread stop...\n");
	int ok = stopThread(2000);
	DBG("stopped:"+String(ok));
}

void RandomNumberServiceThread::setMinMax(float min, float max)
{
    if (stuff != NULL)
        stuff->setMinMax(min, max);
}

void RandomNumberServiceThread::run()
{
	yarp::os::ConstString serviceEndpointName;
	yarp::os::ConstString servicePortNumber;

	const char* argv = " ";
	MplusM::Common::Initialize(argv);
	serviceEndpointName = DEFAULT_RANDOM_SERVICE_NAME; //todo: set this

	keepGoing = true;

    if (stuff == NULL)
	    stuff = new RandomNumberService(argv, serviceEndpointName, servicePortNumber);

	if (stuff)
		if (stuff->start())
		{
 			yarp::os::ConstString channelName(stuff->getEndpoint().getName());
			
			DBG("channelName = " + String(channelName.c_str()));
			if (MplusM::Common::RegisterLocalService(channelName, NULL, NULL))
			{
				MplusM::StartRunning();
				MplusM::Common::SetSignalHandlers(MplusM::SignalRunningStop);
				stuff->startPinger();
				for ( ; MplusM::IsRunning() && stuff && !threadShouldExit(); )
				{
					yarp::os::Time::yield();
				}
				DBG("exit called; unregistering port..."+String(channelName.c_str()));
				MplusM::Common::UnregisterLocalService(channelName, NULL, NULL);
				int ok = stuff->stop();
				DBG("stuff stopped. ok=" + String(ok));
			}
		}
	delete stuff;
	stuff = NULL;
	DBG("end of serviceThread...");
}

