#include "Angle.h"
#include <stdexcept>

Angle::Angle(int dir, int num) : d(dir), n(num)
{
}
Angle::~Angle()
{
}

void Angle::add(const Angle &ang)
{
	if (n != ang.n)
	{
		throw std::invalid_argument("different n parametr");
	}
	d = (d + ang.d) % n;
}

void Angle::add(int dir)
{
	d = (d + dir) % n;
}

Angle Angle::plus(const Angle &ang1, const Angle &ang2)
{
	if (ang1.n != ang2.n)
	{
		throw std::invalid_argument("different n parametr");
	}
	return Angle((ang1.d + ang2.d)%ang1.n, ang1.n);
}

Angle Angle::plus(const Angle &ang, int dir)
{
	return Angle((ang.d+dir)% ang.n, ang.n);
}


bool Angle::isEqual(const Angle &ang) const
{
	return (n == ang.n) && (d == ang.d); 
}

bool Angle::isEqual(const Angle &ang1, const Angle &ang2)
{
	return (ang1.n == ang2.n) && (ang2.d == ang2.d);
}


bool Angle::operator==(const Angle& other) const
{
	return isEqual(other);
}
