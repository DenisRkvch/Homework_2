#ifndef IMOVABLE_H
#define IMOVABLE_H

#include "Vector2d.h"

class IMovable
{

protected:
	virtual ~IMovable() = default; // защищенный деструктор

public:
	virtual Vector2d* getPosition() = 0;
	virtual Vector2d* getVelocity() = 0;
	virtual void setPosition(Vector2d pos) = 0;

};

#endif
