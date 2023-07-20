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

	background->setTexture(i);

	i++;

	if (i >= 34)
	{
		i = 4;
	}

	mixr::simulation::Station* station = dynamic_cast<mixr::simulation::Station*>(container());
	if (station != nullptr)
	{
		player = dynamic_cast<MyAircraft*>(station->getOwnship());
		mixr::graphics::Polygon* falconLogo = dynamic_cast<mixr::graphics::Polygon*>(findByName("falcon-logo")->object());

		if (player != nullptr)
		{
			velocity = player->getTotalVelocity();
			altitude = player->getAltitude();
			degrees = player->getHeadingD();
			lat = player->getLatitude();
			lon = player->getLongitude();
			roll = player->getRollD();
			
			if (curTime - prevTime == 1)
			{
				prevTime = time(NULL);
				vsi = altitude - prevAlt;
				prevAlt = player->getAltitude();
			}
			

			std::cout << curTime << std::endl;
			//heading = dynamic_cast<mixr::graphics::AsciiText*>(findByName("heading")->object());

			if (heading != nullptr)
			{
				if (degrees >= 0 && degrees < 90) heading->setText("N");
				else if (degrees >= 90 && degrees < 180) heading->setText("E");
				else if (degrees >= 180 && degrees < 270) heading->setText("S");
				else if (degrees >= 270 && degrees < 360) heading->setText("W");

				send("heading", UPDATE_VALUE, heading, headingSD);
			}

			/*std::cout << curRoll << std::endl;
			std::cout << roll << std::endl << std::endl;*/

			send("latitude", UPDATE_VALUE, lat, latSD);
			send("longitude", UPDATE_VALUE, lon, lonSD);
			send("degrees", UPDATE_VALUE, degrees, degreesSD);
			send("altitude", UPDATE_VALUE, altitude, altitudeSD);
			send("velocity", UPDATE_VALUE, velocity, velocitySD);
			send("vsi", UPDATE_VALUE, vsi, vsiSD);

			falconLogo->lcRotate(-curRoll + roll);

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
		const auto dynaModel = dynamic_cast<mixr::models::JSBSimModel*>(player->findByName("dynamics-model")->object());

		if(dynaModel != nullptr) dynaModel->setCommandedHeadingD(30);

		std::cout << dynaModel->getCommandedHeadingD();
	}

	return true;
}

bool MyDisplay::onRight()
{
	

	/*if (falconLogo != nullptr)
	{
		if (curAngle >= -30)
		{
			curAngle--;
			double curRoll = falconLogo->getMatrix()(0, 1) * 180 / pi;
			falconLogo->lcRotate(-curRoll + roll);
		}
	}*/

	return true;
}
