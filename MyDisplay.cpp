#include "MyDisplay.hpp"

IMPLEMENT_SUBCLASS(MyDisplay, "MyDisplay")
EMPTY_SLOTTABLE(MyDisplay)
EMPTY_DELETEDATA(MyDisplay)

MyDisplay::MyDisplay()
{
	STANDARD_CONSTRUCTOR()
}

void MyDisplay::copyData(const MyDisplay& org, const bool)
{
	BaseClass::copyData(org);
}

void MyDisplay::reset()
{
	BaseClass::reset();
}
