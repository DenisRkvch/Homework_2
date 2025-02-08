#ifndef IMOVABLE_H
#define IMOVABLE_H

#include "Vector.h"

class IMovable
{

protected:
	virtual ~IMovable() = default; // защищенный деструктор

public:
	virtual Vector* getPosition() = 0;
	virtual Vector* getVelocity() = 0;
	virtual void setPosition(Vector *pos) = 0;

};

#endif
