#ifndef VECTOR2D_H
#define VECTOR2D_H

class Vector2d
{
public:
	Vector2d(int x, int y);

	void add(const Vector2d& vec);
	bool isEqual(const Vector2d &vec) const;

	static Vector2d plus(const Vector2d &vec1, const Vector2d &vec2);
	static bool isEqual(const Vector2d &vec1, const Vector2d &vec2);

	bool operator==(const Vector2d& other) const;
private:
	int x_coord, y_coord;
};


#endif
