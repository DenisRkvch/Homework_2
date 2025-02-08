#ifndef VECTOR2D_H
#define VECTOR2D_H

class Vector
{
public:
	Vector(int x, int y);
	Vector(int x, int y, int z);
	Vector(int _coords[], int len);
	Vector(const Vector& p);
	~Vector();

	void add(const Vector& vec);
	bool isEqual(const Vector &vec) const;

	static Vector* plus(const Vector &vec1, const Vector &vec2);
	static bool isEqual(const Vector &vec1, const Vector &vec2);

	bool operator==(const Vector& other) const;

private:

	int* coords;
	int dim;
};


#endif
