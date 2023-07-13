#include "MyStation.hpp"

IMPLEMENT_SUBCLASS(MyStation, "MyStation")
EMPTY_SLOTTABLE(MyStation)
EMPTY_DELETEDATA(MyStation)

MyStation::MyStation()
{
	STANDARD_CONSTRUCTOR()
}

void MyStation::copyData(const MyStation& org, const bool)
{
	BaseClass::copyData(org);
}

void MyStation::reset()
{
	BaseClass::reset();
}