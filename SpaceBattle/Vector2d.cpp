#include "Vector2d.h"
#include <iostream>

Vector2d::Vector2d(int x, int y) : x_coord(x), y_coord(y)
{
}

void Vector2d::add(const Vector2d& vec)
{
	x_coord += vec.x_coord;
	y_coord += vec.y_coord;
}

bool Vector2d::isEqual(const Vector2d &vec) const
{
	return ((x_coord == vec.x_coord) && (y_coord == vec.y_coord)) ? true : false;
}

// statics
bool Vector2d::isEqual(const Vector2d &vec1, const Vector2d &vec2)
{
	return ((vec1.x_coord == vec2.x_coord) && (vec1.y_coord == vec2.y_coord)) ? true : false;
}

Vector2d Vector2d::plus(const Vector2d &vec1, const Vector2d &vec2)
{
	return Vector2d(vec1.x_coord + vec2.x_coord, vec1.y_coord + vec2.y_coord);
}

bool Vector2d::operator==(const Vector2d& other) const
{
	return isEqual(other);

}




