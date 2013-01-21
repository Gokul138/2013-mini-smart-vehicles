/*
 * Copyright (c) Christian Berger and Bernhard Rumpe, Rheinisch-Westfaelische Technische Hochschule Aachen, Germany.
 *
 * The Hesperia Framework.
 */

#ifndef HESPERIA_BASE_CLIENTMODULE_H_
#define HESPERIA_BASE_CLIENTMODULE_H_

// native.h must be included as first header file for definition of _WIN32_WINNT.
#include "core/native.h"

#include "core/version.h"
#include "core/base/AbstractCIDModule.h"
#include "core/base/KeyValueConfiguration.h"
#include "core/data/TimeStamp.h"
#include "core/exceptions/Exceptions.h"

#include "hesperia/dmcp/connection/Client.h"
#include "hesperia/dmcp/SuperComponentStateListener.h"

namespace hesperia {
    namespace base {

        using namespace std;

        /**
         * This class is the abstract superclass for every client module.
         * For using this class, simply derive your class from ConferenceClientModule.
         *
         * @See ConferenceClientModule
         */
        class HESPERIA_API ClientModule : public core::base::AbstractCIDModule,
                                          protected hesperia::dmcp::SupercomponentStateListener
        {
            private:
                friend class ConferenceClientModule;

                /**
                 * Constructor.
                 *
                 * @param argc Number of command line arguments.
                 * @param argv Command line arguments.
                 * @param name Name of this module. This parameter is necessary for identifying the corresponding parts in the configuration.
                 * @throw InvalidArgumentException if the signal handler could not be registered.
                 */
                ClientModule(const int32_t &argc, char **argv, const string &name) throw (core::exceptions::InvalidArgumentException);

            private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 */
                ClientModule(const ClientModule&);

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the assignment operator.
                 */
                ClientModule& operator=(const ClientModule&);

            public:
                virtual ~ClientModule();

                virtual core::base::ModuleState::MODULE_EXITCODE runModule();

                /**
                 * This method returns the module's name.
                 *
                 * @return name of the module.
                 */
                const string getName() const;

                /**
                 * This method returns the version of the sources as
                 * computed at compile time.
                 */
                inline string getVersion() const {
                    return HESPERIA_VERSION;
                };

            protected:
                /**
                 * This method is called right before the body is executed.
                 */
                virtual void setUp() = 0;

                /**
                 * This method is called after returning from body.
                 */
                virtual void tearDown() = 0;

                /**
                 * This method contains the real module body.
                 *
                 * @return The exit code of the real body.
                 */
                virtual core::base::ModuleState::MODULE_EXITCODE body() = 0;

                /**
                 * This method returns the key/value-configuration
                 * for this client module.
                 *
                 * @return Key/value-configuration.
                 */
                const core::base::KeyValueConfiguration getKeyValueConfiguration() const;

                virtual void handleConnectionLost();

            private:
                virtual void wait();

            private:
                string m_name;
                core::base::KeyValueConfiguration m_keyValueConfiguration;
                core::SharedPointer<hesperia::dmcp::connection::Client> m_dmcpClient;
                core::data::TimeStamp m_lastCycle;
                long m_lastWaitTime;
                int32_t m_cycleCounter;
        };

    }
} // hesperia::base

#endif /*HESPERIA_BASE_CLIENTMODULE_H_*/
