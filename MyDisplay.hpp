// Custom Glut Display Class

#ifndef __MyDisplay_H__
#define __MyDisplay_H__

#include "mixr/ui/glut/GlutDisplay.hpp"
#include "mixr/graphics/readouts/AsciiText.hpp"
#include "mixr/graphics/Polygon.hpp"

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

	// Aircraft's altitude (Feet)
	int altitude{};
	SendData altitudeSD{};

	// Aircraft's heading (NSEW)
	mixr::graphics::AsciiText* heading{};
	SendData headingSD{};

	// Aircraft's heading (Degrees)
	int degrees{};
	SendData degreesSD{};
	// Aircraft's speed (Knots)
	int velocity{};
	SendData velocitySD{};

	// Aircraft's altitude/sec (Feet/Sec)
	int vsi{};
	SendData vsiSD{};

	mixr::graphics::Polygon* falconLogo;
	double angle{ 0.0174533 };
	double curAngle{0};

	int i = 4;
	bool onAlt() { return true; }

	bool onLeft();
	bool onRight();

};

#endif