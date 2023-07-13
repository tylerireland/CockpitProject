// Custom Glut Display Class

#ifndef __MyDisplay_H__
#define __MyDisplay_H__

#include "mixr/ui/glut/GlutDisplay.hpp"

class MyDisplay : public mixr::glut::GlutDisplay
{
	DECLARE_SUBCLASS(MyDisplay, mixr::glut::GlutDisplay)

	
public:
	MyDisplay();

	void updateData(const double dt = 0.0) final;

private:



};

#endif