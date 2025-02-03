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
// ��� �������, ������������ � ����� (12, 5) � ����������� �� ��������� (-7, 3) �������� ������ ��������� ������� �� (5, 8)
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

// ������� �������� ������, � �������� ���������� ��������� ��������� � ������������, �������� � ������
TEST(TestMove, getPosition_exception)
{
	testing::NiceMock<MovableMock> mock;
	Move move(&mock);

	EXPECT_CALL(mock, getPosition()).WillOnce(Throw(std::runtime_error("Can't give position!")));
	ON_CALL(mock, getVelocity()).WillByDefault(Return(new Vector2d(10, 10)));
	EXPECT_CALL(mock, setPosition(testing::_)).Times(0);

	EXPECT_THROW(move.execute(), std::runtime_error);
}

// ������� �������� ������, � �������� ���������� ��������� �������� ���������� ��������, �������� � ������
TEST(TestMove, getVelocity_exception)
{
	testing::NiceMock<MovableMock> mock;
	Move move(&mock);

	ON_CALL(mock, getPosition()).WillByDefault(Return(new Vector2d(10, 10)));
	EXPECT_CALL(mock, getVelocity()).WillOnce(Throw(std::runtime_error("Can't give velocity!")));
	EXPECT_CALL(mock, setPosition(testing::_)).Times(0);

	EXPECT_THROW(move.execute(), std::runtime_error);
}

// ������� �������� ������, � �������� ���������� �������� ��������� � ������������, �������� � ������
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

// ��� �������, �������� ������� ��������� 65 ���� � ����������������� �� ��������� -7, 
// �������� ������ ��������� ������� �� 58
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

// ���� ����������� ������� ����� (360 ����) : 300 + 100 => 40
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


// ������� ������� ������, � �������� ���������� ��������� ����, �������� � ������
TEST(TestRotate, getDirection_exception)
{
	testing::NiceMock<RotatableMock> mock;
	Rotate rotate(&mock);

	EXPECT_CALL(mock, getDirection()).WillOnce(Throw(std::runtime_error("Can't give direction!")));
	ON_CALL(mock, getAngularVelocity()).WillByDefault(Return((int)100));
	EXPECT_CALL(mock, setDirection(testing::_)).Times(0);

	EXPECT_THROW(rotate.execute(), std::runtime_error);
}

// ������� ������� ������, � �������� ���������� ��������� ������� ��������, �������� � ������
TEST(TestRotate, getAngularVelocity_exception)
{
	testing::NiceMock<RotatableMock> mock;
	Rotate rotate(&mock);

	ON_CALL(mock, getDirection()).WillByDefault(Return(new Angle(10, 10)));
	EXPECT_CALL(mock, getAngularVelocity()).WillOnce(Throw(std::runtime_error("Can't give anguular velocity!")));
	EXPECT_CALL(mock, setDirection(testing::_)).Times(0);

	EXPECT_THROW(rotate.execute(), std::runtime_error);
}

// ������� ������� ������, � �������� ���������� �������� ����, �������� � ������
TEST(TestRotate, setDirection_exception)
{
	testing::NiceMock<RotatableMock> mock;
	Rotate rotate(&mock);

	EXPECT_CALL(mock, getDirection()).WillOnce(Return(new Angle(90, 1000)));
	EXPECT_CALL(mock, getAngularVelocity()).WillOnce(Return((int)200));
	EXPECT_CALL(mock, setDirection(testing::_)).WillOnce(Throw(std::runtime_error("Can't move!")));

	EXPECT_THROW(rotate.execute(), std::runtime_error);
}