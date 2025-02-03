#ifndef MOVE_H
#define MOVE_H

#include "IMovable.h"

class Move
{
private:

	IMovable* mObj;

public:

	Move(IMovable* movable);
	~Move();

	void execute();
};


#endif
