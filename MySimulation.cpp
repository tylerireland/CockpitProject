#include "MySimulation.hpp"

IMPLEMENT_SUBCLASS(MySimulation, "MySimulation")
EMPTY_SLOTTABLE(MySimulation)
EMPTY_DELETEDATA(MySimulation)

MySimulation::MySimulation()
{
	STANDARD_CONSTRUCTOR()
}

void MySimulation::copyData(const MySimulation& org, const bool)
{
	BaseClass::copyData(org);
}

void MySimulation::updateTC(const double dt)
{
	BaseClass::updateTC(dt);
}

void MySimulation::updateData(const double dt)
{
	BaseClass::updateData(dt);
}

void MySimulation::reset()
{
	BaseClass::reset();
}