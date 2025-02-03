#ifndef IROTATABLE_H
#define IROTATABLE_H

#include "Angle.h"

class IRotatable
{

protected:
	virtual ~IRotatable() = default; // защищенный деструктор

public:
	virtual Angle* getDirection() = 0;
	virtual int getAngularVelocity() = 0;
	virtual void setDirection(Angle ang) = 0;
};

#endif
