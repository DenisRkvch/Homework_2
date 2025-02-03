#ifndef ANGLE_H
#define ANGLE_H

class Angle
{
public:
	Angle(int dir, int num);
	~Angle();

	void add(const Angle &ang);
	void add(int dir);
	bool isEqual(const Angle &ang) const;

	static Angle plus(const Angle &ang1, const Angle &ang2);
	static Angle plus(const Angle &ang1, int dir);
	static bool isEqual(const Angle &ang1, const Angle &ang2);

	bool operator==(const Angle &other) const;

private:
	int d, n;
	
};
#endif


