/*
 * Copyright (c) Christian Berger.
 *
 * The Hesperia Framework.
 */

#include <iostream>

#include "core/macros.h"
#include "core/base/KeyValueConfiguration.h"
#include "core/base/Thread.h"
#include "core/data/Container.h"

#include "hesperia/data/environment/EgoState.h"
#include "hesperia/data/environment/VehicleData.h"
#include "hesperia/data/environment/Point3.h"
#include "hesperia/data/control/ForceControl.h"

#include "Vehicle.h"
#include "LinearBicycleModel.h"

namespace vehicle {

    using namespace std;
    using namespace core::base;
    using namespace core::data;
    using namespace hesperia::data::control;
    using namespace hesperia::data::environment;

    Vehicle::Vehicle(const int32_t &argc, char **argv) :
        ConferenceClientModule(argc, argv, "Vehicle") {}

    Vehicle::~Vehicle() {}

    void Vehicle::setUp() {}

    void Vehicle::tearDown() {}

    ModuleState::MODULE_EXITCODE Vehicle::body() {
        LinearBicycleModel lbm(getKeyValueConfiguration());

        KeyValueDataStore &kvs = getKeyValueDataStore();

        while (getModuleState() == ModuleState::RUNNING) {
            // Get current ForceControl.
            Container c = kvs.get(Container::FORCECONTROL);
            ForceControl fc = c.getData<ForceControl>();
            cerr << "ForceControl: '" << fc.toString() << "'" << endl;

        	lbm.accelerate(fc.getAccelerationForce());
        	lbm.brake(fc.getBrakeForce());
        	lbm.steer(fc.getSteeringForce());

            if (fc.getBrakeLights()) {
                cout << "Turn ON brake lights." << endl;
            }
            else {
            }

            if (fc.getLeftFlashingLights()) {
                cout << "Turn ON left flashing lights." << endl;
            }
            else {
            }

            if (fc.getRightFlashingLights()) {
                cout << "Turn ON right flashing lights." << endl;
            }
            else {
            }
           
            EgoState es = lbm.computeEgoState();
            
            // Get vehicle data.
            VehicleData vd = lbm.getVehicleData();
            cerr << "VehicleData: '" << vd.toString() << "'" << endl;

            Container container(Container::EGOSTATE, es);
            getConference().send(container);

            // Send vehicledata.
            Container c2(Container::VEHICLEDATA, vd);
            getConference().send(c2);
        }
        return ModuleState::OKAY;
    }

} // vehicle
