#ifndef ROTATE_H
#define ROTATE_H

#include "IRotatable.h"

class Rotate
{

public:
	Rotate(IRotatable* rotatable);
	~Rotate();

	void execute();

private:
	IRotatable* rObj;
	
};

#endif
