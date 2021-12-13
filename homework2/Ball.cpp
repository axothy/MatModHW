#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <map>

const double EarthGravity = 9.8;

//Используем контейнер с ключом х и значением у
typedef std::map<double, double> Walls;
typedef std::map<double, int> Interval;

//Структура - компоненты скорости МТ
typedef struct Velocity {
	double v_x;
	double v_y;
};

class Ball {
public:

	//Конструкторы мячика
	Ball() {} 
	Ball(double h0, double vx, double vy, const Walls& input_walls) : h0(h0),
		velocity({ vx, vy }), walls(std::move(input_walls)), x0(0), number_of_hits(0) {
		this->walls.insert(std::make_pair(-1, -1)); checkWalls();
	}

	Ball(const std::string& filename);

	std::ifstream file;
	~Ball() { file.close(); }

	Walls walls;
	Interval interval;
	Velocity velocity;
	int fall_interval;

	void setVelocity();
	void BuildWalls();
	void checkWalls();
	void showWalls();

	int KudaUpal();

private:
	double h0;
	double x0;

	double ymove, wall_x, wall_y; //костыли
	int number_of_hits;

	inline double time(double x, double x0) { return (x - x0) / velocity.v_x; }
	inline double xMove(double t) { return x0 + velocity.v_x * t; }
	inline double yMove(double t) { return h0 + velocity.v_y * t - (EarthGravity * t * t) / 2; }
};

Ball::Ball(const std::string& filename) {
	x0 = 0;
	number_of_hits = 0;
	file.open(filename);
	setVelocity();
	BuildWalls();
}

void Ball::setVelocity() {
	file >> h0;
	file >> velocity.v_x >> velocity.v_y;
}


void Ball::BuildWalls() {
	double tmpx, tmpy;
	walls.insert(std::make_pair(-1, -1)); /*еще один костыль*/
	do {
		file >> tmpx >> tmpy;
		walls.insert(std::make_pair(tmpx, tmpy));
	} while (!file.eof());

	checkWalls();
} 

void Ball::checkWalls() {
	std::map<double, double>::iterator it0 = walls.begin();
	while (it0 != walls.end()) {
		if (it0->first != NULL && it0->first < 0)
			it0 = walls.erase(it0);
		else
			it0++;
	}

	int i = 0;
	for (auto it = walls.begin(); it != walls.end(); ++it)
	{
		interval.insert(std::make_pair(it->first, i));
		i++;
	}

	walls.insert(std::make_pair(-1, -1));
}

void Ball::showWalls() {
	for (auto i = walls.begin(); i != walls.end(); ++i) {
		std::cout << i->first << " " << i->second << std::endl;
	}
}

int Ball::KudaUpal() {

	if (interval.empty()) {
		std::cout << "0" << std::endl;
		fall_interval = 0;
		return 0;
	}

	int current = -1;
	int direction = 1;

	double point_x = 0;
	double point_y = h0;

	for (auto i = walls.begin(); i != walls.end(); ++i) {

		int m = current + direction;
		if (m < 0) {
			std::cout << 0;
			return 0;
		}
		if (m > walls.size() - 1) {
			std::cout << walls.size();
			return 0;
		}

		double x = i->first;
		double wall = i->second;
		double t = abs((x - point_y)) / abs(velocity.v_x);
		double fall_time = (velocity.v_y + sqrt(velocity.v_y * velocity.v_y + 2 * EarthGravity * point_y)) / EarthGravity;


		if (fall_time < t) {
			if (direction == 1) std::cout << m;
			else std::cout << m + 1;
			return 0;

		}
		double y = point_y + velocity.v_y * t - (EarthGravity * t * t) / 2;

		velocity.v_y = velocity.v_y - EarthGravity * t;
		point_x = x;
		point_y = y;
		current = m;

		if (y < wall) {
			velocity.v_x *= -1;
			direction = velocity.v_x / abs(velocity.v_x);
		}
	}

}

int main(int argc, char** argv) {

	Ball ball("in.txt");
    ball.KudaUpal();

	return 0;
}
