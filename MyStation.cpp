#include "MyStation.hpp"

IMPLEMENT_SUBCLASS(MyStation, "MyStation")

BEGIN_SLOTTABLE(MyStation)
"display",          // 1) sets our display
END_SLOTTABLE(MyStation)

BEGIN_SLOT_MAP(MyStation)
	ON_SLOT(1, setSlotDisplay, MyDisplay)
END_SLOT_MAP()

MyStation::MyStation()
{
	STANDARD_CONSTRUCTOR()
}

void MyStation::copyData(const MyStation& org, const bool)
{
	BaseClass::copyData(org);

    if (display != nullptr) {
        display->unref();
        display = nullptr;
    }

    if (org.display != nullptr) {
        display = org.display;
        display->ref();
    }

    displayInit = org.displayInit;
}


void MyStation::deleteData()
{
    if (display != nullptr) {
        display->unref();
        display = nullptr;
    }
}

void MyStation::reset()
{
    if (display != nullptr && !displayInit) {
        display->createWindow();
        display->focus(display);
        displayInit = true;
    }

	BaseClass::reset();
}

bool MyStation::setSlotDisplay(MyDisplay* dis)
{
    bool ok{};
    // clear out our old display first
    if (display != nullptr) {
        display->unref();
        display = nullptr;
    }

    if (dis != nullptr) {
        display = dis;
        display->ref();
        display->container(this);
        ok = true;
    }

    return ok;
}
