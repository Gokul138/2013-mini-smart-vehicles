/*
 * Copyright (c) Christian Berger and Bernhard Rumpe, Rheinisch-Westfaelische Technische Hochschule Aachen, Germany.
 *
 * The Hesperia Framework.
 */

#ifndef HESPERIA_CORE_BASE_SERVICE_H_
#define HESPERIA_CORE_BASE_SERVICE_H_

// native.h must be included as first header file for definition of _WIN32_WINNT.
#include "core/native.h"

#include "core/SharedPointer.h"
#include "core/base/Condition.h"
#include "core/base/Mutex.h"
#include "core/exceptions/Exceptions.h"
#include "core/wrapper/Runnable.h"
#include "core/wrapper/Thread.h"

namespace core {
    namespace base {

        /**
         * This class combines wrapper::Runnable and wrapper::Thread
         * for convenience:
         *
         * @code
         * class MyService : public Service {
         *     virtual void beforeStop() {
         *         // This block is executed right before the thread will be stopped.
         *     }
         *
         *     virtual void run() {
         *         // Do some initialization
         *         serviceReady();
         *         // Do something.
         *     }
         * };
         *
         * int32_t main(int32_t argc, char **argv) {
         *     MyService s;
         *     s.start();
         *     s.stop();
         * }
         * @endcode
         */
        class HESPERIA_API Service : public wrapper::Runnable {
            private:
                enum SERVICE_STATE {
                    INITIALIZED,
                    RUNNING,
                    STOPPED
                };

            private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 */
                Service(const Service &);

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the assignment operator.
                 */
                Service& operator=(const Service &);

            public:
                Service() throw (exceptions::ThreadException) ;

                virtual ~Service();

                /**
                 * This method starts the service and will block the calling
                 * thread until serviceReady() is called.
                 */
                void start();

                /**
                 * This method stops the service.
                 * A stopped service CANNOT get restarted.
                 */
                void stop();

                /**
                 * This method has to be called by the run() method to
                 * unblock the start() method when the service is fully
                 * initialized.
                 */
                void serviceReady();

            protected:
                /**
                 * This method is called right before this service gets stopped.
                 */
                virtual void beforeStop() = 0;

                virtual void run() = 0;

                virtual bool isRunning();

            private:
                SharedPointer<wrapper::Thread> m_thread;

                Mutex m_serviceStateMutex;
                SERVICE_STATE m_serviceState;
                Condition m_serviceReadyCondition;
                bool m_serviceReady;
        };

    }
} // core::base

#endif /*HESPERIA_CORE_BASE_SERVICE_H_*/
