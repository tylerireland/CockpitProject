#include "MyAircraft.hpp"

IMPLEMENT_SUBCLASS(MyAircraft, "MyAircraft")
EMPTY_SLOTTABLE(MyAircraft)
EMPTY_DELETEDATA(MyAircraft)

EMPTY_COPYDATA(MyAircraft)

MyAircraft::MyAircraft()
{
	STANDARD_CONSTRUCTOR()
}

void MyAircraft::updateData(const double dt)
{
	std::cout << "Hello";
	BaseClass::updateData(dt);
}