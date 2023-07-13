
#include "factory.hpp"

#include "mixr/base/Object.hpp"

#include "MyStation.hpp"
#include "MyDisplay.hpp"
#include "MySimulation.hpp"
#include "MyAircraft.hpp"

#include "xpanel/factory.hpp"

// factories
#include "xzmq/factory.hpp"
#include "mixr/base/factory.hpp"
#include "mixr/graphics/factory.hpp"
#include "mixr/interop/dis/factory.hpp"
#include "mixr/instruments/factory.hpp"
#include "mixr/linkage/factory.hpp"
#include "mixr/ighost/cigi/factory.hpp"
#include "mixr/models/factory.hpp"
#include "mixr/terrain/factory.hpp"
#include "mixr/simulation/factory.hpp"
#include "mixr/ui/glut/factory.hpp"


#include <string>

mixr::base::Object* factory(const std::string& name)
{
    mixr::base::Object* obj{};

    if (name == MyStation::getFactoryName()) {
        obj = new MyStation();
    }
    else if (name == MyDisplay::getFactoryName()) {
        obj = new MyDisplay();
    }
    else if (name == MySimulation::getFactoryName()) {
        obj = new MySimulation();
    }
    else if (name == MyAircraft::getFactoryName()) {
        obj = new MyAircraft();
    }

    // example libraries
    if (obj == nullptr) obj = mixr::xpanel::factory(name);
    if (obj == nullptr) obj = mixr::xzmq::factory(name);

    // framework libraries
    if (obj == nullptr) obj = mixr::simulation::factory(name);
    if (obj == nullptr) obj = mixr::instruments::factory(name);
    if (obj == nullptr) obj = mixr::linkage::factory(name);
    if (obj == nullptr) obj = mixr::instruments::factory(name);
    if (obj == nullptr) obj = mixr::models::factory(name);
    if (obj == nullptr) obj = mixr::terrain::factory(name);
    if (obj == nullptr) obj = mixr::cigi::factory(name);
    if (obj == nullptr) obj = mixr::dis::factory(name);
    if (obj == nullptr) obj = mixr::graphics::factory(name);
    if (obj == nullptr) obj = mixr::glut::factory(name);
    if (obj == nullptr) obj = mixr::base::factory(name);

    return obj;
}
