// Custom Simulation Class

#ifndef __MySimualtion_H__
#define __MySimulation_H__

#include "mixr/models/WorldModel.hpp"

class MySimulation : public mixr::models::WorldModel
{
	DECLARE_SUBCLASS(MySimulation, mixr::models::WorldModel)


public:
	MySimulation();

	void updateTC(const double dt = 0.0) final;
	void updateData(const double dt = 0.0) final;
	void reset() final;

private:


};

#endif
