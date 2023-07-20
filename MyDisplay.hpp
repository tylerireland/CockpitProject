// Custom Glut Display Class

#ifndef __MyDisplay_H__
#define __MyDisplay_H__

#include "mixr/ui/glut/GlutDisplay.hpp"
#include "mixr/graphics/readouts/AsciiText.hpp"
#include "mixr/graphics/Polygon.hpp"
#include "MyAircraft.hpp"
#include <cmath>
#include <ctime>


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
	
	// Aircraft's Roll (Degrees)
	double roll{};
	SendData rollSD{};

	// Aircraft's lat/lon
	double lat{};
	double lon{};
	SendData latSD{};
	SendData lonSD{};

	
	double angle{ 0.0174532925 }; //0.0174532925 rad == 1 degree
	double curAngle{-1};
	double pi = 3.14159265358979323846;
	double curRoll{0};

	int i = 4;
	bool onAlt() { return true; }

	bool onLeft();
	bool onRight();

};

#endif