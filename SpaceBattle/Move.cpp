#include "Move.h"

Move::Move(IMovable* movable) : mObj(movable)
{
}
Move::~Move()
{
}

void Move::execute()
{
	Vector *result = Vector::plus(*mObj->getPosition(), *mObj->getVelocity());
	mObj->setPosition(result);
	delete result;

}
