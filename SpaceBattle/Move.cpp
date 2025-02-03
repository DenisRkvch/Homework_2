#include "Move.h"

Move::Move(IMovable* movable) : mObj(movable)
{
}
Move::~Move()
{
}

void Move::execute()
{
	mObj->setPosition(Vector2d::plus(*mObj->getPosition(), *mObj->getVelocity()));	
}
