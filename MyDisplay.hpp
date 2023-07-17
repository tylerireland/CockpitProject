// Custom Glut Display Class

#ifndef __MyDisplay_H__
#define __MyDisplay_H__

#include "mixr/ui/glut/GlutDisplay.hpp"


class MyDisplay : public mixr::glut::GlutDisplay
{
	DECLARE_SUBCLASS(MyDisplay, mixr::glut::GlutDisplay)

	
public:
	MyDisplay();

	void updateTC(const double dt = 0.0) final;
	void updateData(const double dt = 0.0) final;
	void reset() final;

private:

	// Aircraft's altitude (Feet)
	int altitude{};
	SendData altitudeRO{};

	// Aircraft's heading (Degrees)
	int heading{};
	SendData headingRRO{};

	// Aircraft's speed (Knots)
	int knots{};
	SendData knotsRO{};

	// Aircraft's altitude/sec (Feet/Sec)
	int vsi{};
	SendData vsiRO{};




};

#endif