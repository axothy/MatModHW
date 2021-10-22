#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <cmath>
#include <io.h>
#include <algorithm>
#include <vector>
#include <string>
#include <map>

const double EarthGravity = 9.8;

typedef std::map<double, double> Walls;

typedef struct Velocity {
	double v_x;
	double v_y;
};

class Ball {
public:
	Ball() {}
	Ball(const std::string& filename);

	std::ifstream file;
	~Ball() { file.close(); }

	Walls walls;
	Velocity velocity;

	bool isInInterval();
	void setVelocity();
	void BuildWalls();
	void KudaUpal();

private:
	double h0;
	double x0;

	double ymove, wall_x, wall_y;

	inline double time(double x, double x0) { return (x - x0) / velocity.v_x; }
	inline double xMove(double t) { return x0 + velocity.v_x * t; }
	inline double yMove(double t) { return h0 + velocity.v_y * t - (EarthGravity * t * t) / 2; }
};

Ball::Ball(const std::string& filename) {
	file.open(filename);
	setVelocity();
	BuildWalls();
}

bool Ball::isInInterval()
{
	return true;
}

void Ball::setVelocity() {
	file >> h0;
	file >> velocity.v_x >> velocity.v_y;
	std::cout << "v_x v_y set: " << velocity.v_x << " " << velocity.v_y << std::endl;
}

void Ball::BuildWalls() {
	double tmpx, tmpy;
	do {
		file >> tmpx >> tmpy;
		walls.insert(std::make_pair(tmpx, tmpy));
	} while (!file.eof());

	std::cout << "walls succesfully built... " << std::endl;
}

void Ball::KudaUpal() {

	x0 = 0;
	std::map<double, double>::iterator itt;
	for (auto it1 = walls.begin(); it1 != walls.end(); ++it1) {
		if (yMove(time(it1->first, x0)) < it1->second && yMove(time(it1->first, x0)) > 0) {
			wall_x = it1->first; wall_y = it1->second;
			ymove = yMove(time(it1->first, x0));
			std::cout << "Ball hitted wall with x = " << it1->first << std::endl;
			std::cout << "visota udara " << yMove(time(it1->first, x0)) << std::endl;

			h0 = yMove(time(it1->first, x0));
			x0 = it1->first;

			itt = it1;
			break;
		}
	}

	for (auto it2 = std::next(itt); it2 != walls.end(); ++it2)
		walls.erase(it2);
		
	if (ymove < wall_y && ymove > 0) {
		for (auto it1 = std::next(walls.rbegin()); it1 != walls.rend(); ++it1) {
			velocity.v_y = velocity.v_y - EarthGravity * time(it1->first, x0);
			if (yMove(time(it1->first, x0)) < it1->second && yMove(time(it1->first, x0)) > 0) {
				wall_x = it1->first; wall_y = it1->second;
				ymove = yMove(time(it1->first, x0));
				std::cout << "Ball hitted another wall with x = " << it1->first << std::endl;
				std::cout << "visota udara " << yMove(time(it1->first, x0)) << std::endl;

				h0 = yMove(time(it1->first, x0));
				velocity.v_x = -velocity.v_x;
				velocity.v_y = velocity.v_y - EarthGravity * time(it1->first, x0);

				for (auto it2 = it1; it2 != walls.rend(); ++it2)
					it2 = decltype(it2){walls.erase(std::next(it2).base())};
				break;
			}
		}
	}

	for (auto it3 = walls.begin(); it3 != walls.end(); it3++)
		std::cout << it3->first << " " << it3->second << std::endl;
}

int main(void) {
}