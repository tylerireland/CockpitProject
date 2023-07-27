#include "MyDisplay.hpp"
#include "xpanel/DspRadar.hpp"
#include "xpanel/DspRwr.hpp"
#include "xpanel/Pfd.hpp"

#include "mixr/models/player/air/AirVehicle.hpp"
#include "mixr/models/dynamics/JSBSimModel.hpp"
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

	latSD.empty();
	lonSD.empty();
	degreesSD.empty();
	altitudeSD.empty();
	velocitySD.empty();
	vsiSD.empty();
	pitchSD.empty();

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
	curTime = time(NULL);

	mixr::base::PairStream* textureList = getTextures();
	mixr::graphics::Polygon* background = dynamic_cast<mixr::graphics::Polygon*>(findByName("background")->object());

	if (background != nullptr)
	{
		background->setTexture(i);

		i++;

		if (i >= 34)
		{
			i = 5;
		}
	}

	mixr::simulation::Station* station = dynamic_cast<mixr::simulation::Station*>(container());

	if (station != nullptr)
	{
		player = dynamic_cast<MyAircraft*>(station->getOwnship());
		mixr::graphics::Polygon* falconLogo = dynamic_cast<mixr::graphics::Polygon*>(findByName("falcon-logo")->object());
		mixr::graphics::Polygon* attInd = dynamic_cast<mixr::graphics::Polygon*>(findByName("pitch")->object());

		if (player != nullptr && falconLogo != nullptr && attInd != nullptr)
		{
			velocity = player->getTotalVelocity();
			altitude = player->getAltitude();
			degrees = player->getHeadingD();
			lat = player->getLatitude();
			lon = player->getLongitude();
			roll = player->getRollD();
			pitch = player->getPitchD();
			
			if (curTime - prevTime == 1)
			{
				prevTime = time(NULL);
				vsi = altitude - prevAlt;
				prevAlt = player->getAltitude();
			}
			
			yPos = attInd->getMatrix()(3, 1);

			//std::cout << player->setFuelFreeze(true)  << std::endl;
			heading = dynamic_cast<mixr::graphics::AsciiText*>(findByName("heading")->object());

			if (heading != nullptr)
			{
				if (degrees >= 315 && degrees < 45) heading->setText("N");
				else if (degrees >= 45 && degrees < 135) heading->setText("E");
				else if (degrees >= 135 && degrees < 225) heading->setText("S");
				else if (degrees >= 225 && degrees < 315) heading->setText("W");

				send("heading", UPDATE_VALUE, heading, headingSD);
			}

			std::cout << pitch << std::endl;
			

			send("latitude",  UPDATE_VALUE, lat, latSD);
			send("longitude", UPDATE_VALUE, lon, lonSD);
			send("degrees",   UPDATE_VALUE, degrees, degreesSD);
			send("altitude",  UPDATE_VALUE, altitude, altitudeSD);
			send("velocity",  UPDATE_VALUE, velocity, velocitySD);
			send("vsi",       UPDATE_VALUE, vsi, vsiSD);

			falconLogo->lcRotate(-curRoll + roll);
			attInd->lcTranslate(0, -yPos - (pitch / 10));

			curRoll = player->getRollD();
			
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
	if (player != nullptr)
	{
		
	}

	return true;
}

bool MyDisplay::onRight()
{
	if (player != nullptr)
	{
	
	}

	return true;

}
