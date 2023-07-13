//Custom Station Class

#ifndef __MyStation_H__
#define __MyStation_H__

#include "mixr/simulation/Station.hpp"

class MyStation : public mixr::simulation::Station
{
	DECLARE_SUBCLASS(MyStation, mixr::simulation::Station)


public:
	MyStation();


	void reset() final;
	

private:


};

#endif