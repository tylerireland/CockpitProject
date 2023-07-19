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

BEGIN_EVENT_HANDLER(MyDisplay)
	ON_EVENT(UPDATE_VALUE, onAlt)
	ON_EVENT(FORWARD_SPACE, onRight)
	ON_EVENT(BACK_SPACE, onLeft)
END_EVENT_HANDLER()

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
	mixr::base::PairStream* textureList = getTextures();
	mixr::graphics::Polygon* background = dynamic_cast<mixr::graphics::Polygon*>(findByName("background")->object());

	background->setTexture(i);

	i++;

	if (i >= 34)
	{
		i = 4;
	}

	mixr::simulation::Station* station = dynamic_cast<mixr::simulation::Station*>(container());
	if (station != nullptr)
	{
		MyAircraft* player = dynamic_cast<MyAircraft*>(station->getOwnship());

		if (player != nullptr)
		{
			velocity = player->getTotalVelocity();
			altitude = player->getAltitude();
			degrees = player->getHeadingD();
			lat = player->getLatitude();
			lon = player->getLongitude();
			//heading = dynamic_cast<mixr::graphics::AsciiText*>(findByName("heading")->object());

			if (heading != nullptr)
			{
				if (degrees >= 0 && degrees < 90) heading->setText("N");
				else if (degrees >= 90 && degrees < 180) heading->setText("E");
				else if (degrees >= 180 && degrees < 270) heading->setText("S");
				else if (degrees >= 270 && degrees < 360) heading->setText("W");

				send("heading", UPDATE_VALUE, heading, headingSD);
			}

			std::cout << player->getLatitude() << " -- " << player->getLongitude() << std::endl;

			send("latitude", UPDATE_VALUE, lat, latSD);
			send("longitude", UPDATE_VALUE, lon, lonSD);
			send("degrees", UPDATE_VALUE, degrees, degreesSD);
			send("altitude", UPDATE_VALUE, altitude, altitudeSD);
			send("velocity", UPDATE_VALUE, velocity, velocitySD);
		}
	}
	BaseClass::updateData(dt);
}

void MyDisplay::reset()
{
	BaseClass::reset();
}

bool MyDisplay::onLeft()
{
	falconLogo = dynamic_cast<mixr::graphics::Polygon*>(findByName("falcon-logo")->object());
	
	if (falconLogo != nullptr)
	{
		if (curAngle <= 30)
		{
			curAngle++;
			std::cout << curAngle << " -- " << falconLogo->getMatrix()(0, 1) * 180 / pi << std::endl;
			falconLogo->lcRotate(angle);
			
		}
	}

	return true;
}

bool MyDisplay::onRight()
{
	falconLogo = dynamic_cast<mixr::graphics::Polygon*>(findByName("falcon-logo")->object());

	if (falconLogo != nullptr)
	{
		if (curAngle >= -30)
		{
			curAngle--;
			std::cout << curAngle << " -- " << falconLogo->getMatrix()(0, 1) * 180 / pi << std::endl;
			falconLogo->lcRotate(-angle);
		}
	}

	return true;
}
