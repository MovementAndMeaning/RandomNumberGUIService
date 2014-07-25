//--------------------------------------------------------------------------------------------------
//
//  File:       RandomNumberServiceThread.cpp
//
//  Project:    M+M
//
//  Contains:   The class source for the random number service thread for the GUI Random Number example.
//
//  Written by: Johnty Wang
//
//  Copyright:  (c) 2014 by HPlus Technologies Ltd. and Simon Fraser University.
//
//              All rights reserved. Redistribution and use in source and binary forms, with or
//              without modification, are permitted provided that the following conditions are met:
//                * Redistributions of source code must retain the above copyright notice, this list
//                  of conditions and the following disclaimer.
//                * Redistributions in binary form must reproduce the above copyright notice, this
//                  list of conditions and the following disclaimer in the documentation and/or
//                  other materials provided with the distribution.
//                * Neither the name of the copyright holders nor the names of its contributors may
//                  be used to endorse or promote products derived from this software without
//                  specific prior written permission.
//
//              THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
//              EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
//              OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
//              SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
//              INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
//              TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
//              BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
//              CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
//              ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
//              DAMAGE.
//
//  Created:    2014-07-23
//
//--------------------------------------------------------------------------------------------------

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
    myState = 0;
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
                myState = 1;
                sendChangeMessage();
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
    myState = 0;
    sendChangeMessage();
}

