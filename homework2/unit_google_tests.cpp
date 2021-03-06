#include "pch.h"

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(StandartTest, FindingInvervalForBall) {
	Walls test;

	test.insert(std::make_pair(1, 1));
	test.insert(std::make_pair(2, 1));
	test.insert(std::make_pair(5, 4));
	test.insert(std::make_pair(8, 2));

	Ball ball(6.0, 5.0, 5.0, test);
	ball.KudaUpal();

	EXPECT_EQ(ball.fall_interval, 3);
}

TEST(NoWalls, FindingInvervalForBall) {
	Walls test;

	Ball ball(6.0, 5.0, 5.0, test);
	ball.KudaUpal();

	EXPECT_EQ(ball.fall_interval, 0);
}

TEST(WallsIsNegative, FindingInvervalForBall) {
	Walls test;

	test.insert(std::make_pair(-2, 1));
	test.insert(std::make_pair(-3, 1));

	Ball ball(6.0, 5.0, 5.0, test);
	ball.KudaUpal();

	EXPECT_EQ(ball.fall_interval, 0);
}


TEST(SeveralHits, FindingInvervalForBall) {
	Walls test;

	test.insert(std::make_pair(1, 1));
	test.insert(std::make_pair(5, 7));
	test.insert(std::make_pair(4, 6));
	test.insert(std::make_pair(5.5, 1));
	test.insert(std::make_pair(10, 15));

	Ball ball(6.0, 5.0, 5.0, test);
	ball.KudaUpal();

	EXPECT_EQ(ball.fall_interval, 2);
}


TEST(NoHits_Fall_between2walls, FindingInvervalForBall) {
	Walls test;

	test.insert(std::make_pair(1, 1));
	test.insert(std::make_pair(10, 15));

	Ball ball(6.0, 5.0, 5.0, test);
	ball.KudaUpal();

	EXPECT_EQ(ball.fall_interval, 1);
}

TEST(OnlyOneWall, FindingInvervalForBall) {
	Walls test;

	test.insert(std::make_pair(10, 15));

	Ball ball(6.0, 5.0, 5.0, test);
	ball.KudaUpal();

	EXPECT_EQ(ball.fall_interval, 0);
}

TEST(nohits_LongFlight, FindingInvervalForBall) {
	Walls test;

	test.insert(std::make_pair(10, 15));

	Ball ball(6.0, 5.0, 5.0, test);
	ball.KudaUpal();

	EXPECT_EQ(ball.fall_interval, 0);
}

TEST(CheckVelocity, ReadingInputFile)
{
	Velocity test_vel;
	test_vel.v_x = 5;

	Ball ball("in.txt");
	EXPECT_EQ(ball.velocity.v_x, test_vel.v_x);
}

TEST(RandomWalls, BuildWalls) {
	Walls random_walls;
	Walls sorted_walls;

	random_walls.insert(std::make_pair(5, 4));
	random_walls.insert(std::make_pair(2, 4));
	random_walls.insert(std::make_pair(1, 4));

	sorted_walls.insert(std::make_pair(1, 4));
	sorted_walls.insert(std::make_pair(2, 4));
	sorted_walls.insert(std::make_pair(5, 4));

	EXPECT_EQ(random_walls, sorted_walls);
}
