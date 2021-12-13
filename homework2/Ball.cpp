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

	void KudaUpal();

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

void Ball::KudaUpal() {

	if (interval.empty()) {
		std::cout << "0" << std::endl;
		fall_interval = 0;
		return;
	}

	//Полет вправо -> -> ->
	std::map<double, double>::iterator it1;
	for (it1 = std::next(walls.begin()); it1 != walls.end(); ++it1) {
		if (yMove(time(it1->first, x0)) < it1->second && yMove(time(it1->first, x0)) > 0) { //если y_шарика < h0
			wall_x = it1->first; wall_y = it1->second;
			ymove = yMove(time(it1->first, x0)); //задаем высоту столкновения

			h0 = yMove(time(it1->first, x0)); //задаем новую h0 как высоту столкновения
			x0 = it1->first; //задаем новый x0 как x_стенки

			number_of_hits++;
			break; //дальше перебирать стенки нам не нужно - выходим из цикла
		}

		else if (yMove(time(it1->first, x0)) < 0)
		{
			std::cout << interval.find(it1->first)->second << std::endl; //вывод интервала
			fall_interval = interval.find(it1->first)->second;
			return;
		}
	}

	if (number_of_hits == 0) {
		std::cout << std::prev(interval.end())->second + 1 << std::endl; //вывод интервала
		fall_interval = std::prev(interval.end())->second + 1;
		return;
	}
	
	//С помощью итератора чистим наше дерево от стенок, стоящих правее той, с которой было столкновение
	//erase делаем так, чтобы итератор не терялся и не указывал на пустой блок памяти
	//После чистки лишние стенки удалились справа и мы можем идти с конца дерева
	if (it1 != walls.end()) {
		std::map<double, double>::iterator it2 = std::next(it1);
		while (it2 != walls.end()) {
			if (it2->first != NULL)
				it2 = walls.erase(it2);
			else
				it2++;
		}
	}

	//Полет влево <- <- <-
	if (ymove < wall_y && ymove > 0) {
		std::map<double, double>::reverse_iterator it3;
		for (it3 = std::next(walls.rbegin()); it3 != walls.rend(); ++it3) {
			velocity.v_y = velocity.v_y - EarthGravity * time(it3->first, x0);
			if (yMove(time(it3->first, x0)) < it3->second && yMove(time(it3->first, x0)) > 0) {
				wall_x = it3->first; wall_y = it3->second;
				ymove = yMove(time(it3->first, x0));

				h0 = yMove(time(it3->first, x0));
				x0 = it3->first;
				velocity.v_x = -velocity.v_x;
				velocity.v_y = velocity.v_y - EarthGravity * time(it3->first, x0);

				number_of_hits++;
				break; //Нашли столкновение - выходим из цикла
			}

			else if (yMove(time(it3->first, x0)) < 0)
			{
				std::cout << interval.find(it1->first)->second << std::endl;
				fall_interval = interval.find(it1->first)->second;
				return;
			}

			else {
				std::cout << "0" << std::endl;
				fall_interval = 0;
				return;
			}
		}

		//По тем тем же правилам чистим стенки левее, используя реверсивный итератор контейнера
		std::map<double, double>::reverse_iterator it4 = std::next(it3);
		while (it4 != walls.rend()) {
			if (it4->first != NULL)
			{
				walls.erase(std::next(it4).base());
			}
			else
				it4++;
		} 
	} 

	if (ymove < wall_y && ymove > 0) {
		KudaUpal();
	}

}

int main(int argc, char** argv) {

	Ball ball("in.txt");
	ball.KudaUpal();

	return 0;
}
