// Custom Glut Display Class

#ifndef __MyDisplay_H__
#define __MyDisplay_H__

#include "mixr/ui/glut/GlutDisplay.hpp"
#include "mixr/graphics/readouts/AsciiText.hpp"
#include "mixr/graphics/Polygon.hpp"
#include "mixr/graphics/Rotators.hpp"
#include "MyAircraft.hpp"
#include <cmath>
#include <string>
#include <ctime>
#include <time.h>

class MyDisplay : public mixr::glut::GlutDisplay
{
	DECLARE_SUBCLASS(MyDisplay, mixr::glut::GlutDisplay)

	
public:
	MyDisplay();
	
	void updateTC(const double dt = 0.0) final;
	void updateData(const double dt = 0.0) final;
	bool event(const int event, mixr::base::Object* const obj = nullptr) override;
	void reset() final;

private:

	MyAircraft* player;

	time_t prevTime = time(NULL);
	time_t curTime = time(NULL);

	//struct tm newtime;
	//time_t now = time(0);
	//localtime_s(&newtime, &now);

	//int year = 1900 + ltm->tm_year;
	//int month = 1 + ltm->tm_mon;
	//int day = ltm->tm_mday;
	//int hour = 5 + ltm->tm_hour;
	//int min = 30 + ltm->tm_min;



	// Aircraft's altitude (Feet)
	double altitude{};
	SendData altitudeSD{};

	// Aircraft's heading (NSEW)
	mixr::graphics::AsciiText* heading{};
	SendData headingSD{};

	// Aircraft's heading (Degrees)
	double degrees{};
	SendData degreesSD{};

	// Aircraft's speed (Knots)
	double velocity{};
	SendData velocitySD{};

	// Aircraft's altitude/sec (Feet/Sec)
	double prevAlt{};
	double vsi{};
	SendData vsiSD{};
	
	// Aircraft's Pitch (Degrees)
	double prevPitch{};
	double pitch{};
	SendData pitchSD{};

	// Aircraft's Roll (Degrees)
	double prevRoll{};
	double roll{};
	SendData rollSD{};

	// Aircraft's lat/lon
	double lat{};
	double lon{};
	SendData latSD{};
	SendData lonSD{};

	
	double angleR{ 0.0174532925 }; //0.0174532925 rad == 1 degree
	double angleD{ 0 };
	SendData angleSD{};

	double curAngle{-1};
	double pi = 3.14159265358979323846;
	double curRoll{0};

	double yPos{};

	int i = 5;
	bool onAlt() { return true; }

	bool onLeft();
	bool onRight();
	bool onUp();
	bool onDown();

	double var;

};

#endif