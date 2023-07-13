// Custom Simulation Class

#ifndef __MySimualtion_H__
#define __MySimulation_H__

#include "mixr/simulation/Simulation.hpp"

class MySimulation : mixr::simulation::Simulation
{
	DECLARE_SUBCLASS(MySimulation, mixr::simulation::Simulation)


public:
	MySimulation();

	void updateTC(const double dt = 0.0) final;
	void updateData(const double dt = 0.0) final;
	void reset() final;

private:


};

#endif
