#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "../SpaceBattle/IMovable.h"
#include "../SpaceBattle/Move.h"
#include "../SpaceBattle/IRotatable.h"
#include "../SpaceBattle/Rotate.h"
#include <iostream>

using ::testing::Return;
using ::testing::Throw;

MATCHER_P(EqVec, other, "Equality matcher for type Vector2d") {
	return arg->isEqual(*other);
}

MATCHER_P(EqAngl, other, "Equality matcher for type Angle") {
	return arg->isEqual(*other);
}

class MovableMock : public IMovable {
public:
	~MovableMock() override = default;
	MOCK_METHOD((Vector*), getPosition, (), (override));
	MOCK_METHOD((void),	setPosition, (Vector*), (override));
	MOCK_METHOD((Vector*), getVelocity, (), (override));	
};

class RotatableMock : public IRotatable {
public:
	~RotatableMock() override = default;
	MOCK_METHOD((Angle*), getDirection, (), (override));
	MOCK_METHOD((void), setDirection, (Angle*), (override));
	MOCK_METHOD((int), getAngularVelocity, (), (override));
};

// =============   ДОПОЛНИТЕЛЬНЫЕ ТЕСТЫ КЛАССОВ VECTOR И ANGLE   ===============
// 
// 
// 
// некорректные параметры
TEST(TestVector, invalid_params)
{
	int param[] = { 4,5,0 };
	EXPECT_THROW(Vector(param, 0), std::invalid_argument);
	EXPECT_THROW(Vector(param, -6), std::invalid_argument);

	Vector vec2d(1, 1);
	Vector vec3d(1, 1, 1);
	EXPECT_THROW(vec2d.add(vec3d), std::invalid_argument);
}

// сравнение векторов
TEST(TestVector, vector_equality)
{
	Vector vec2d1(4, 5);
	Vector vec2d2(4, 5);
	Vector vec2d3(2, 2);

	Vector vec3d1(4, 5, 0);
	Vector vec3d2(4, 5, 0);

	int param[] = { 4,5,0,0,-1 };
	Vector vec5d1(param, 5);

	// сравнение векторорв одной размерности
	EXPECT_EQ(vec2d1, vec2d2);
	EXPECT_FALSE(vec2d1 == vec2d3);
	EXPECT_THAT(&vec3d1, EqVec(&vec3d2));

	// разной размерности
	EXPECT_TRUE(Vector::isEqual(vec2d1, vec3d1));
	EXPECT_FALSE(vec3d2.isEqual(vec5d1));
}

// сложение векторов
TEST(TestVector, vector_summ)
{
	// сложение векторорв одной размерности
	Vector* summ = Vector::plus(Vector(4, 5), Vector(-3, 0));
	EXPECT_EQ(*summ, Vector(1, 5));
	delete summ;

	// сложение векторорв разной размерности
	int param = -3;
	summ = Vector::plus(Vector(&param, 1), Vector(7, 7, 7));
	EXPECT_EQ(*summ, Vector(4, 7, 7));
	delete summ;

	Vector vec(-1, -2);
	vec.add(Vector(-4, -4));
	EXPECT_EQ(vec, Vector(-5, -6));
}

// некорректные параметры
TEST(TestAngle, invalid_params)
{
	EXPECT_THROW(Angle(10, 0), std::invalid_argument);
	EXPECT_THROW(Angle(10, -10), std::invalid_argument);

	Angle ang1(100, 300);
	Angle ang2(100, 310);
	EXPECT_THROW(ang1.add(ang2), std::invalid_argument);
	EXPECT_THROW(Angle::plus(ang1, ang2), std::invalid_argument);
}

// сравнение углов
TEST(TestAngle, angle_equality)
{
	Angle ang1(100, 300);
	Angle ang2(100, 310);
	Angle ang3(100, 300);
	Angle ang4(50, 310);

	EXPECT_THAT(&ang1, EqVec(&ang3));

	EXPECT_FALSE(ang1 == ang2);
	EXPECT_TRUE(ang1 == ang3);

	EXPECT_FALSE(ang2.isEqual(ang4));
	EXPECT_TRUE(ang1.isEqual(ang3));

	EXPECT_FALSE(Angle::isEqual(ang2, ang4));
	EXPECT_TRUE(Angle::isEqual(ang1, ang3));
}

// сложение углов
TEST(TestAngle, angle_summ)
{
	Angle* summ = Angle::plus(Angle(100, 300), Angle(50, 300));
	EXPECT_EQ(*summ, Angle(150, 300));
	delete summ;

	Angle ang(100, 300);
	ang.add(Angle(-20, 300));
	EXPECT_EQ(ang, Angle(80, 300));
}

// =============   MOVE   ===============
// 
// 
// 
// Для объекта, находящегося в точке (12, 5) и движущегося со скоростью (-7, 3) движение меняет положение объекта на (5, 8)
TEST(TestMove, correct_moving)
{
	MovableMock mock;
	Move move(&mock);
	Vector expect(5,8);
	Vector ret1(12, 5);
	Vector ret2(-7, 3);

	EXPECT_CALL(mock, getPosition()).WillOnce(Return(&ret1));
	EXPECT_CALL(mock, getVelocity()).WillOnce(Return(&ret2));
	EXPECT_CALL(mock, setPosition(EqVec(&expect))).Times(1);

	move.execute();
}

// Попытка сдвинуть объект, у которого невозможно прочитать положение в пространстве, приводит к ошибке
TEST(TestMove, getPosition_exception)
{
	testing::NiceMock<MovableMock> mock;
	Move move(&mock);
	Vector ret(10, 10);

	EXPECT_CALL(mock, getPosition()).WillOnce(Throw(std::runtime_error("Can't give position!")));
	ON_CALL(mock, getVelocity()).WillByDefault(Return(&ret));
	EXPECT_CALL(mock, setPosition(testing::_)).Times(0);

	EXPECT_THROW(move.execute(), std::runtime_error);
}

// Попытка сдвинуть объект, у которого невозможно прочитать значение мгновенной скорости, приводит к ошибке
TEST(TestMove, getVelocity_exception)
{
	testing::NiceMock<MovableMock> mock;
	Move move(&mock);
	Vector ret(10, 10);

	ON_CALL(mock, getPosition()).WillByDefault(Return(&ret));
	EXPECT_CALL(mock, getVelocity()).WillOnce(Throw(std::runtime_error("Can't give velocity!")));
	EXPECT_CALL(mock, setPosition(testing::_)).Times(0);

	EXPECT_THROW(move.execute(), std::runtime_error);
}

// Попытка сдвинуть объект, у которого невозможно изменить положение в пространстве, приводит к ошибке
TEST(TestMove, setPosition_exception)
{
	testing::NiceMock<MovableMock> mock;
	Move move(&mock);
	Vector ret(10, 10);

	EXPECT_CALL(mock, getPosition()).WillOnce(Return(&ret));
	EXPECT_CALL(mock, getVelocity()).WillOnce(Return(&ret));
	EXPECT_CALL(mock, setPosition(testing::_)).WillOnce(Throw(std::runtime_error("Can't move!")));

	EXPECT_THROW(move.execute(), std::runtime_error);
}

// =============   ROTATION   ===============
// 
// 
// 

// Для объекта, имеющего угловое положение 65 град и поворачивающегося со скоростью -7, 
// движение меняет положение объекта на 58
TEST(TestRotate, correct_rotation)
{
	RotatableMock mock;
	Rotate rotate(&mock);
	Angle expect(58, 360);
	Angle ret(65, 360);

	EXPECT_CALL(mock, getDirection()).WillOnce(Return(&ret));
	EXPECT_CALL(mock, getAngularVelocity()).WillOnce(Return((int) - 7));
	EXPECT_CALL(mock, setDirection(EqAngl(&expect))).Times(1);

	rotate.execute();
}

// Тест прохождения полного круга (360 град) : 300 + 100 => 40
TEST(TestRotate, correct_rotation_full_circle)
{
	RotatableMock mock;
	Rotate rotate(&mock);
	Angle expect(40, 360);
	Angle ret(300, 360);

	EXPECT_CALL(mock, getDirection()).WillOnce(Return(&ret));
	EXPECT_CALL(mock, getAngularVelocity()).WillOnce(Return((int)100));
	EXPECT_CALL(mock, setDirection(EqAngl(&expect))).Times(1);

	rotate.execute();
}


// Попытка вращать объект, у которого невозможно прочитать угол, приводит к ошибке
TEST(TestRotate, getDirection_exception)
{
	testing::NiceMock<RotatableMock> mock;
	Rotate rotate(&mock);

	EXPECT_CALL(mock, getDirection()).WillOnce(Throw(std::runtime_error("Can't give direction!")));
	ON_CALL(mock, getAngularVelocity()).WillByDefault(Return((int)100));
	EXPECT_CALL(mock, setDirection(testing::_)).Times(0);

	EXPECT_THROW(rotate.execute(), std::runtime_error);
}

// Попытка вращать объект, у которого невозможно прочитать угловую скорость, приводит к ошибке
TEST(TestRotate, getAngularVelocity_exception)
{
	testing::NiceMock<RotatableMock> mock;
	Rotate rotate(&mock);
	Angle ret(10, 10);

	ON_CALL(mock, getDirection()).WillByDefault(Return(&ret));
	EXPECT_CALL(mock, getAngularVelocity()).WillOnce(Throw(std::runtime_error("Can't give anguular velocity!")));
	EXPECT_CALL(mock, setDirection(testing::_)).Times(0);

	EXPECT_THROW(rotate.execute(), std::runtime_error);
}

// Попытка вращать объект, у которого невозможно изменить угол, приводит к ошибке
TEST(TestRotate, setDirection_exception)
{
	testing::NiceMock<RotatableMock> mock;
	Rotate rotate(&mock);
	Angle ret(10, 10);

	EXPECT_CALL(mock, getDirection()).WillOnce(Return(&ret));
	EXPECT_CALL(mock, getAngularVelocity()).WillOnce(Return((int)200));
	EXPECT_CALL(mock, setDirection(testing::_)).WillOnce(Throw(std::runtime_error("Can't move!")));

	EXPECT_THROW(rotate.execute(), std::runtime_error);
}


