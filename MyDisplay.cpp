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
#include "mixr/base/util/system_utils.hpp"

IMPLEMENT_SUBCLASS(MyDisplay, "MyDisplay")
EMPTY_SLOTTABLE(MyDisplay)
EMPTY_DELETEDATA(MyDisplay)

BEGIN_EVENT_HANDLER(MyDisplay)
	ON_EVENT(UPDATE_VALUE, onAlt)
	ON_EVENT(FORWARD_SPACE, onRight)
	ON_EVENT(BACK_SPACE, onLeft)
	ON_EVENT(UP_ARROW_KEY, onUp)
	ON_EVENT(DOWN_ARROW_KEY, onDown)
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
	angleSD.empty();

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

		if (player != nullptr)
		{
			velocity = player->getTotalVelocity();
			altitude = player->getAltitudeFt();
			degrees = player->getHeadingD();
			lat = player->getLatitude();
			lon = player->getLongitude();
			roll = player->getRollD();
			pitch = player->getPitchD();
			
			if (curTime - prevTime == 1)
			{
				prevTime = time(NULL);
				vsi = altitude - prevAlt;
				prevAlt = player->getAltitudeFt();
			}

			heading = dynamic_cast<mixr::graphics::AsciiText*>(findByName("heading")->object());

			if (heading != nullptr)
			{
				if (degrees >= 315 && degrees < 45) heading->setText("N");
				else if (degrees >= 45 && degrees < 135) heading->setText("E");
				else if (degrees >= 135 && degrees < 225) heading->setText("S");
				else if (degrees >= 225 && degrees < 315) heading->setText("W");

				send("heading", UPDATE_VALUE, heading, headingSD);
			}

			std::cout << roll << std::endl;

			send("att-display", UPDATE_VALUE2, pitch/10, pitchSD);
			send("falcon-logo", UPDATE_VALUE6, roll, rollSD);
			send("latitude",    UPDATE_VALUE, lat, latSD);
			send("longitude",   UPDATE_VALUE, lon, lonSD);
			send("degrees",     UPDATE_VALUE, degrees, degreesSD);
			send("altitude",    UPDATE_VALUE, altitude, altitudeSD);
			send("velocity",    UPDATE_VALUE, velocity, velocitySD);
			send("vsi",         UPDATE_VALUE, vsi, vsiSD);
			
			if (roll - prevRoll >= 1 || roll - prevRoll <= -1)
			{
				player->setControlStickRollInput(0.0);
			}
			if (pitch - prevPitch >= 1 || pitch - prevPitch <= -1)
			{
				player->setControlStickPitchInput(0.0);
			}
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
		if (roll <= 30)
		{
			player->setControlStickRollInput(0.1);
		}
		else
		{
			player->setControlStickRollInput(0);
		}

		prevRoll = player->getRollD();
		//std::cout << player->getRollD() << std::endl;
	}

	return true;
}

bool MyDisplay::onRight()
{
	if (player != nullptr)
	{
		if (roll >= -30)
		{
			player->setControlStickRollInput(-0.1);
		}
		else
		{
			player->setControlStickRollInput(0);
		}

		prevRoll = player->getRollD();
		//std::cout << player->getRollD() << std::endl;
	}

	return true;

}

bool MyDisplay::onUp()
{
	if (player != nullptr)
	{
		player->setControlStickPitchInput(-0.5);
		prevPitch = player->getPitchD();
	}

	return true;
}

bool MyDisplay::onDown()
{
	if (player != nullptr)
	{
		player->setControlStickPitchInput(0.5);
		prevPitch = player->getPitchD();
	}

	return true;

}