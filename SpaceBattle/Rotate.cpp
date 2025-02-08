#include "Rotate.h"

Rotate::Rotate(IRotatable* rotatable) : rObj(rotatable)
{
}

Rotate::~Rotate()
{
}

void Rotate::execute()
{
	Angle* result = Angle::plus(*rObj->getDirection(), rObj->getAngularVelocity());
	rObj->setDirection(result);
	delete result;
}

