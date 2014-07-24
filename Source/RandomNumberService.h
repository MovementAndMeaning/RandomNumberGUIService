//--------------------------------------------------------------------------------------------------
//
//  File:       RandomNumberService.h
//
//  Project:    RandomNumberGUIService
//
//  Contains:   The class declaration for the random number service; based on MPlusM/examples/RandomNumberService
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

#if (! defined(RandomNumberService_H_))
# define RandomNumberService_H_  /* Header guard */

# include "M+MBaseRequestHandler.h"
# include "M+MBaseService.h"

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 
 @brief The class declaration for the random number service. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

/*! @brief The channel name to use for the service if not provided. */
# define DEFAULT_RANDOM_SERVICE_NAME T_(DEFAULT_SERVICE_NAME_BASE "example/randomNumberGUI")

/*! @brief The channel-independent name of the random number service. */
# define MpM_RANDOM_CANONICAL_NAME "Random"

/*! @brief The name for the 'random' request. */
# define MpM_RANDOM_REQUEST "random"

#define RANDOM_REQUEST_VERSION_NUMBER "1.0"

namespace MplusM
{
    namespace Example
    {
        class RandomRequestHandler;
        
        /*! @brief The random number service. */
        class RandomNumberService : public Common::BaseService
        {
        public:
            
            /*! @brief The constructor.
             @param launchPath The command-line name used to launch the service.
             @param serviceEndpointName The YARP name to be assigned to the new service.
             @param servicePortNumber The port being used by the service. */
            RandomNumberService(const yarp::os::ConstString & launchPath,
                                const yarp::os::ConstString & serviceEndpointName,
                                const yarp::os::ConstString & servicePortNumber = "");
            
            /*! @brief The destructor. */
            virtual ~RandomNumberService(void);
            
            /*! @brief Start processing requests.
             @returns @c true if the service was started and @c false if it was not. */
            virtual bool start(void);
            
            /*! @brief Stop processing requests.
             @returns @c true if the service was stopped and @c false it if was not. */
            virtual bool stop(void);

            /*! @brief set range of random values generated */
            void setMinMax (float min, float max);
            
        protected:
            
        private:
            
            /*! @brief The class that this class is derived from. */
            typedef BaseService inherited;
            
            /*! @brief Copy constructor.
             
             Note - not implemented and private, to prevent unexpected copying.
             @param other Another object to construct from. */
            RandomNumberService(const RandomNumberService & other);
            
            /*! @brief Assignment operator.
             
             Note - not implemented and private, to prevent unexpected copying.
             @param other Another object to construct from. */
            RandomNumberService & operator =(const RandomNumberService & other);
            
            /*! @brief Enable the standard request handlers. */
            void attachRequestHandlers(void);
            
            /*! @brief Disable the standard request handlers. */
            void detachRequestHandlers(void);
            
            /*! @brief The request handler for the 'random' request. */
            RandomRequestHandler * _randomHandler;

        }; // RandomNumberService

        /*! @brief The 'random' request handler.
         
         The input for the request is an optional count of the number of random numbers to generate
         and the output is either a single floating point number, between 0 and 1 or a list of
         floating point numbers, between 0 and 1. */
        class RandomRequestHandler : public Common::BaseRequestHandler
        {
        public:
            
            /*! @brief The constructor. */
            RandomRequestHandler(void);
            
            /*! @brief The destructor. */
            virtual ~RandomRequestHandler(void);
            
            /*! @brief Fill in a set of aliases for the request.
             @param alternateNames Aliases for the request. */
            virtual void fillInAliases(Common::StringVector & alternateNames);
            
            /*! @brief Fill in a description dictionary for the request.
             @param request The actual request name.
             @param info The dictionary to be filled in. */
            virtual void fillInDescription(const yarp::os::ConstString & request,
                                           yarp::os::Property &          info);
            
            /*! @brief Process a request.
             @param request The actual request name.
             @param restOfInput The arguments to the operation.
             @param senderChannel The name of the channel used to send the input data.
             @param replyMechanism non-@c NULL if a reply is expected and @c NULL otherwise. */
            virtual bool processRequest(const yarp::os::ConstString & request,
                                        const yarp::os::Bottle &      restOfInput,
                                        const yarp::os::ConstString & senderChannel,
                                        yarp::os::ConnectionWriter *  replyMechanism);

            /*! @brief set the min/max value of the random numbers generated
             @param min The minimum value
             @param max The maximum value */            
            void setMinMax( float min, float max);
            
        protected:
            
        private:
            
            /*! @brief The class that this class is derived from. */
            typedef BaseRequestHandler inherited;

            /*! @brief lower bound of random numbers generated. */
            float _min;
            /*! @brief upper bound of random numbers generated. */
            float _max;
            
        }; // RandomRequestHandler
        
    } // Example
    
} // MplusM

#endif // ! defined(RandomNumberService_H_)
