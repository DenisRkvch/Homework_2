#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "../SpaceBattle/IMovable.h"
#include "../SpaceBattle/Move.h"
#include "../SpaceBattle/IRotatable.h"
#include "../SpaceBattle/Rotate.h"
#include <iostream>

using ::testing::Return;
using ::testing::Throw;

MATCHER_P(EqVec2d, other, "Equality matcher for type Vector2d") {
	return arg.isEqual(other);
}

MATCHER_P(EqAngl, other, "Equality matcher for type Angle") {
	return arg.isEqual(other);
}

class MovableMock : public IMovable {
public:
	~MovableMock() override = default;
	MOCK_METHOD((Vector2d*), getPosition, (), (override));
	MOCK_METHOD((void),	setPosition, (Vector2d), (override));
	MOCK_METHOD((Vector2d*), getVelocity, (), (override));	
};

class RotatableMock : public IRotatable {
public:
	~RotatableMock() override = default;
	MOCK_METHOD((Angle*), getDirection, (), (override));
	MOCK_METHOD((void), setDirection, (Angle), (override));
	MOCK_METHOD((int), getAngularVelocity, (), (override));
};

// =============   MOVE   ===============
// 
// 
// 
// Для объекта, находящегося в точке (12, 5) и движущегося со скоростью (-7, 3) движение меняет положение объекта на (5, 8)
TEST(TestMove, correct_moving)
{
	MovableMock mock;
	Move move(&mock);
	Vector2d expect(5,8);

	EXPECT_CALL(mock, getPosition()).WillOnce(Return(new Vector2d(12,5)));
	EXPECT_CALL(mock, getVelocity()).WillOnce(Return(new Vector2d(-7, 3)));
	EXPECT_CALL(mock, setPosition(EqVec2d(expect))).Times(1);

	move.execute();
}

// Попытка сдвинуть объект, у которого невозможно прочитать положение в пространстве, приводит к ошибке
TEST(TestMove, getPosition_exception)
{
	testing::NiceMock<MovableMock> mock;
	Move move(&mock);

	EXPECT_CALL(mock, getPosition()).WillOnce(Throw(std::runtime_error("Can't give position!")));
	ON_CALL(mock, getVelocity()).WillByDefault(Return(new Vector2d(10, 10)));
	EXPECT_CALL(mock, setPosition(testing::_)).Times(0);

	EXPECT_THROW(move.execute(), std::runtime_error);
}

// Попытка сдвинуть объект, у которого невозможно прочитать значение мгновенной скорости, приводит к ошибке
TEST(TestMove, getVelocity_exception)
{
	testing::NiceMock<MovableMock> mock;
	Move move(&mock);

	ON_CALL(mock, getPosition()).WillByDefault(Return(new Vector2d(10, 10)));
	EXPECT_CALL(mock, getVelocity()).WillOnce(Throw(std::runtime_error("Can't give velocity!")));
	EXPECT_CALL(mock, setPosition(testing::_)).Times(0);

	EXPECT_THROW(move.execute(), std::runtime_error);
}

// Попытка сдвинуть объект, у которого невозможно изменить положение в пространстве, приводит к ошибке
TEST(TestMove, setPosition_exception)
{
	testing::NiceMock<MovableMock> mock;
	Move move(&mock);

	EXPECT_CALL(mock, getPosition()).WillOnce(Return(new Vector2d(10, 10)));
	EXPECT_CALL(mock, getVelocity()).WillOnce(Return(new Vector2d(10, 10)));
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

	EXPECT_CALL(mock, getDirection()).WillOnce(Return(new Angle(65, 360)));
	EXPECT_CALL(mock, getAngularVelocity()).WillOnce(Return((int) - 7));
	EXPECT_CALL(mock, setDirection(EqAngl(expect))).Times(1);

	rotate.execute();
}

// Тест прохождения полного круга (360 град) : 300 + 100 => 40
TEST(TestRotate, correct_rotation_full_circle)
{
	RotatableMock mock;
	Rotate rotate(&mock);
	Angle expect(40, 360);

	EXPECT_CALL(mock, getDirection()).WillOnce(Return(new Angle(300, 360)));
	EXPECT_CALL(mock, getAngularVelocity()).WillOnce(Return((int)100));
	EXPECT_CALL(mock, setDirection(EqAngl(expect))).Times(1);

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

	ON_CALL(mock, getDirection()).WillByDefault(Return(new Angle(10, 10)));
	EXPECT_CALL(mock, getAngularVelocity()).WillOnce(Throw(std::runtime_error("Can't give anguular velocity!")));
	EXPECT_CALL(mock, setDirection(testing::_)).Times(0);

	EXPECT_THROW(rotate.execute(), std::runtime_error);
}

// Попытка вращать объект, у которого невозможно изменить угол, приводит к ошибке
TEST(TestRotate, setDirection_exception)
{
	testing::NiceMock<RotatableMock> mock;
	Rotate rotate(&mock);

	EXPECT_CALL(mock, getDirection()).WillOnce(Return(new Angle(90, 1000)));
	EXPECT_CALL(mock, getAngularVelocity()).WillOnce(Return((int)200));
	EXPECT_CALL(mock, setDirection(testing::_)).WillOnce(Throw(std::runtime_error("Can't move!")));

	EXPECT_THROW(rotate.execute(), std::runtime_error);
}