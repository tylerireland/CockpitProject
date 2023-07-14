#include "MyDisplay.hpp"
#include "xpanel/DspRadar.hpp"
#include "xpanel/DspRwr.hpp"
#include "xpanel/Pfd.hpp"

#include "mixr/models/player/air/AirVehicle.hpp"
#include "mixr/models/player/weapon/Missile.hpp"

#include "mixr/models/system/Jammer.hpp"
#include "mixr/models/system/Radar.hpp"
#include "mixr/models/system/Rwr.hpp"
#include "mixr/models/system/StoresMgr.hpp"
#include "mixr/models/sensor/Gmti.hpp"
#include "mixr/models/sensor/Tws.hpp"

#include "mixr/simulation/Simulation.hpp"
#include "mixr/simulation/Station.hpp"

#include "mixr/base/numeric/Boolean.hpp"
#include "mixr/base/Pair.hpp"
#include "mixr/base/PairStream.hpp"
#include "mixr/graphics/SymbolLoader.hpp"
#include "MyAircraft.hpp"
#include <GL/glut.h>

IMPLEMENT_SUBCLASS(MyDisplay, "MyDisplay")
EMPTY_SLOTTABLE(MyDisplay)
EMPTY_DELETEDATA(MyDisplay)

MyDisplay::MyDisplay()
{
	STANDARD_CONSTRUCTOR()
}

void MyDisplay::copyData(const MyDisplay& org, const bool)
{
	
	BaseClass::copyData(org);
}

void MyDisplay ::updateTC(const double dt)
{
	BaseClass::updateTC(dt);
}

void MyDisplay::updateData(const double dt)
{
	mixr::simulation::Station* station = dynamic_cast<mixr::simulation::Station*>(container());
	if (station != nullptr)
	{
		MyAircraft* player = dynamic_cast<MyAircraft*>(station->getOwnship());

		if (player != nullptr)
		{
			
			mixr::graphics::Graphic* airspeedIndicator = dynamic_cast<mixr::graphics::Graphic*>(findByName("airspeed-indicator"));



		}
	}
	BaseClass::updateData(dt);
}

void MyDisplay::reset()
{
	BaseClass::reset();
}
