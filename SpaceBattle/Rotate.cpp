#include "Rotate.h"

Rotate::Rotate(IRotatable* rotatable) : rObj(rotatable)
{
}

Rotate::~Rotate()
{
}

void Rotate::execute()
{
	rObj->setDirection(Angle::plus(*rObj->getDirection(), rObj->getAngularVelocity()));
}

