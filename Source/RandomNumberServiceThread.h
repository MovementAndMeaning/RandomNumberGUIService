//--------------------------------------------------------------------------------------------------
//
//  File:       RandomNumberServiceThread.h
//
//  Project:    M+M
//
//  Contains:   The class declaration for the random number service thread for the GUI example.
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

#ifndef RANDOMNUMBERSERVICETHREAD_H_INCLUDED
#define RANDOMNUMBERSERVICETHREAD_H_INCLUDED
#include "mpm/M+MEndpoint.h"
#include "RandomNumberService.h"
#include "../JuceLibraryCode/JuceHeader.h"

using namespace MplusM::Example;

class RandomNumberServiceThread : public Thread, public ChangeBroadcaster {

public:
    RandomNumberServiceThread();
    ~RandomNumberServiceThread();

    void setMinMax(float min, float max);
    void run();

    SpinLock lock;
    int myState;

private:
    RandomNumberService *stuff;
    bool keepGoing;
    
};




#endif  // RANDOMNUMBERSERVICETHREAD_H_INCLUDED
