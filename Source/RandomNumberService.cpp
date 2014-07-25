//--------------------------------------------------------------------------------------------------
//
//  File:       RandomNumberService.cpp
//
//  Project:    M+M
//
//  Contains:   The class definition for the random number service (GUI vesion), based on examples/RandomNumberService
//
//  Written by: Norman Jaffe, Johnty Wang
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
//  Created:    2014-07-24
//
//--------------------------------------------------------------------------------------------------

#include "RandomNumberService.h"
//#include "ODEnableLogging.h"
#include "ODLogging.h"

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 
 @brief The class definition for the random number service. */
#if defined(__APPLE__)
# pragma clang diagnostic pop
#endif // defined(__APPLE__)

using namespace MplusM;
using namespace MplusM::Common;
using namespace MplusM::Example;

#if defined(__APPLE__)
# pragma mark Private structures, constants and variables
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Local functions
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Class methods
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Constructors and destructors
#endif // defined(__APPLE__)

RandomNumberService::RandomNumberService(const yarp::os::ConstString & launchPath,
                                         const yarp::os::ConstString & serviceEndpointName,
                                         const yarp::os::ConstString & servicePortNumber) :
    inherited(kServiceKindNormal, launchPath, true, MpM_RANDOM_CANONICAL_NAME,
              "The random number service", "random - return the number of random values requested",
              serviceEndpointName, servicePortNumber), _randomHandler(NULL)
{
    OD_LOG_ENTER(); //####
    OD_LOG_S3s("launchPath = ", launchPath, "serviceEndpointName = ", serviceEndpointName, //####
               "servicePortNumber = ", servicePortNumber); //####
    attachRequestHandlers();
    OD_LOG_EXIT_P(this); //####
} // RandomNumberService::RandomNumberService

RandomNumberService::~RandomNumberService(void)
{
    OD_LOG_OBJENTER(); //####
    detachRequestHandlers();
    OD_LOG_OBJEXIT(); //####
} // RandomNumberService::~RandomNumberService

#if defined(__APPLE__)
# pragma mark Actions
#endif // defined(__APPLE__)

void RandomNumberService::attachRequestHandlers(void)
{
    OD_LOG_OBJENTER(); //####
    try
    {
        _randomHandler = new RandomRequestHandler;
        if (_randomHandler)
        {
            //_randomHandler->addChangeListener(this);
            registerRequestHandler(_randomHandler);
            
        }
        else
        {
            OD_LOG("! (_randomHandler)"); //####
        }
    }
    catch (...)
    {
        OD_LOG("Exception caught"); //####
        throw;
    }
    OD_LOG_OBJEXIT(); //####
} // RandomNumberService::attachRequestHandlers

void RandomNumberService::detachRequestHandlers(void)
{
    OD_LOG_OBJENTER(); //####
    try
    {
        if (_randomHandler)
        {
            unregisterRequestHandler(_randomHandler);
            delete _randomHandler;
            _randomHandler = NULL;
        }
    }
    catch (...)
    {
        OD_LOG("Exception caught"); //####
        throw;
    }
    OD_LOG_OBJEXIT(); //####
} // RandomNumberService::detachRequestHandlers

void RandomNumberService::setMinMax(float min, float max)
{
    if (_randomHandler)
        _randomHandler->setMinMax(min, max);
}

bool RandomNumberService::start(void)
{
    OD_LOG_OBJENTER(); //####
    try
    {
        if (! isStarted())
        {
            inherited::start();
            if (isStarted())
            {
            
            }
            else
            {
                OD_LOG("! (isStarted())"); //####
            }
        }
    }
    catch (...)
    {
        OD_LOG("Exception caught"); //####
        throw;
    }
    OD_LOG_OBJEXIT_B(isStarted()); //####
    return isStarted();
} // RandomNumberService::start

bool RandomNumberService::stop(void)
{
    OD_LOG_OBJENTER(); //####
    bool result;
    
    try
    {
        result = inherited::stop();
    }
    catch (...)
    {
        OD_LOG("Exception caught"); //####
        throw;
    }
    OD_LOG_OBJEXIT_B(result); //####
    return result;
} // RandomNumberService::stop

RandomRequestHandler::RandomRequestHandler(void) :
    inherited(MpM_RANDOM_REQUEST)
{
    OD_LOG_ENTER(); //####
    _min = 0.0;
    _max = 1.0;
    OD_LOG_EXIT_P(this); //####
} // RandomRequestHandler::RandomRequestHandler

RandomRequestHandler::~RandomRequestHandler(void)
{
    OD_LOG_OBJENTER(); //####
    OD_LOG_OBJEXIT(); //####
} // RandomRequestHandler::~RandomRequestHandler

#if defined(__APPLE__)
# pragma mark Actions
#endif // defined(__APPLE__)

void RandomRequestHandler::setMinMax(float min, float max)
{
    _min = min;
    _max = max;
}

void RandomRequestHandler::fillInAliases(Common::StringVector & alternateNames)
{
    OD_LOG_OBJENTER(); //####
    OD_LOG_P1("alternateNames = ", &alternateNames); //####
    alternateNames.push_back("?");
    OD_LOG_OBJEXIT(); //####
} // RandomRequestHandler::fillInAliases

void RandomRequestHandler::fillInDescription(const yarp::os::ConstString & request,
                                             yarp::os::Property &          info)
{
    OD_LOG_OBJENTER(); //####
    OD_LOG_S1s("request = ", request); //####
    OD_LOG_P1("info = ", &info); //####
    try
    {
        info.put(MpM_REQREP_DICT_REQUEST_KEY, request);
        info.put(MpM_REQREP_DICT_INPUT_KEY, MpM_REQREP_INT MpM_REQREP_0_OR_1);
        info.put(MpM_REQREP_DICT_OUTPUT_KEY, MpM_REQREP_DOUBLE MpM_REQREP_1_OR_MORE);
        info.put(MpM_REQREP_DICT_VERSION_KEY, RANDOM_REQUEST_VERSION_NUMBER);
        info.put(MpM_REQREP_DICT_DETAILS_KEY, "Generate one or more random numbers\n"
                 "Input: the number of random values to generate\n"
                 "Output one or more random numbers per request");
        yarp::os::Value    keywords;
        yarp::os::Bottle * asList = keywords.asList();
        
        asList->addString(request);
        info.put(MpM_REQREP_DICT_KEYWORDS_KEY, keywords);
    }
    catch (...)
    {
        OD_LOG("Exception caught"); //####
        throw;
    }
    OD_LOG_OBJEXIT(); //####
} // RandomRequestHandler::fillInDescription

bool RandomRequestHandler::processRequest(const yarp::os::ConstString & request,
                                          const yarp::os::Bottle &      restOfInput,
                                          const yarp::os::ConstString & senderChannel,
                                          yarp::os::ConnectionWriter *  replyMechanism)
{
#if (! defined(OD_ENABLE_LOGGING))
# if MAC_OR_LINUX_
#  pragma unused(request,senderChannel)
# endif // MAC_OR_LINUX_
#endif // ! defined(OD_ENABLE_LOGGING)
    OD_LOG_OBJENTER(); //####
    OD_LOG_S3s("request = ", request, "restOfInput = ", restOfInput.toString(), //####
               "senderChannel = ", senderChannel); //####
    OD_LOG_P1("replyMechanism = ", replyMechanism); //####
    bool result = true;
    
    try
    {
        if (replyMechanism)
        {
            OD_LOG("(replyMechanism)"); //####
            yarp::os::Bottle response;
            int              count;
            
            if (0 < restOfInput.size())
            {
                yarp::os::Value number(restOfInput.get(0));
                
                if (number.isInt())
                {
                    count = number.asInt();
                }
                else
                {
                    count = -1;
                }
            }
            else
            {
                count = 1;
            }
            if (count > 0)
            {
                for (int ii = 0; ii < count; ++ii)
                {
                    double val = _min + (_max - _min) * yarp::os::Random::uniform();
                    response.addDouble(val);
                }
            }
            else
            {
                OD_LOG("! (count > 0)"); //####
            }
            OD_LOG_S1("response <- ", response.toString().c_str()); //####
            if (! response.write(*replyMechanism))
            {
                OD_LOG("(! response.write(*replyMechanism))"); //####
#if defined(MpM_StallOnSendProblem)
                Common::Stall();
#endif // defined(MpM_StallOnSendProblem)
            }
        }
    }
    catch (...)
    {
        OD_LOG("Exception caught"); //####
        throw;
    }
    OD_LOG_OBJEXIT_B(result); //####

    return result;
} // RandomRequestHandler::processRequest