#ifndef __MyAircraft_H__
#define __MyAircraft_H__

#include "mixr/models/player/air/Aircraft.hpp"

class MyAircraft : public mixr::models::Aircraft
{
	DECLARE_SUBCLASS(MyAircraft, mixr::models::Aircraft)

public:
	MyAircraft();

	void updateData(const double dt = 0.0) final;
};


#endif
