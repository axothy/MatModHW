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

//���������� ��������� � ������ � � ��������� �
typedef std::map<double, double> Walls;
typedef std::map<double, int> Interval;

//��������� - ���������� �������� ��
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
	Interval interval;
	Velocity velocity;

	void setVelocity();
	void BuildWalls();
	void KudaUpal();

private:
	double h0;
	double x0;

	double ymove, wall_x, wall_y, number_of_interval; //�������

	inline double time(double x, double x0) { return (x - x0) / velocity.v_x; }
	inline double xMove(double t) { return x0 + velocity.v_x * t; }
	inline double yMove(double t) { return h0 + velocity.v_y * t - (EarthGravity * t * t) / 2; }
};

Ball::Ball(const std::string& filename) {
	x0 = 0;
	number_of_interval = 0;
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
	walls.insert(std::make_pair(-1, -1)); /*��� ���� �������*/
	int i = 0;
	do {
		file >> tmpx >> tmpy;
		walls.insert(std::make_pair(tmpx, tmpy));
		interval.insert(std::make_pair(tmpx, i));
		i++;
	} while (!file.eof());

} 

void Ball::KudaUpal() {

	//����� ������ -> -> ->
	std::map<double, double>::iterator it1;
	for (it1 = std::next(walls.begin()); it1 != walls.end(); ++it1) {
		number_of_interval++;
		if (yMove(time(it1->first, x0)) < it1->second && yMove(time(it1->first, x0)) > 0) { //���� y_������ < h0
			wall_x = it1->first; wall_y = it1->second;
			ymove = yMove(time(it1->first, x0)); //������ ������ ������������

			h0 = yMove(time(it1->first, x0)); //������ ����� h0 ��� ������ ������������
			x0 = it1->first; //������ ����� x0 ��� x_������
			break; //������ ���������� ������ ��� �� ����� - ������� �� �����
		}

		else if (yMove(time(it1->first, x0)) < 0)
		{
			std::cout << interval.find(it1->first)->second << std::endl; //����� ���������
			return;
		}
	}
	
	//� ������� ��������� ������ ���� ������ �� ������, ������� ������ ���, � ������� ���� ������������
	//erase ������ ���, ����� �������� �� ������� � �� �������� �� ������ ���� ������
	//����� ������ ������ ������ ��������� ������ � �� ����� ���� � ����� ������
	std::map<double, double>::iterator it2 = std::next(it1);
	while (it2 != walls.end()) {
		if (it2->first != NULL)
			it2 = walls.erase(it2);
		else
			it2++;
	}

	//����� ����� <- <- <-
 	if (ymove < wall_y && ymove > 0) {
		std::map<double, double>::reverse_iterator it3;
		for (it3 = std::next(walls.rbegin()); it3 != walls.rend(); ++it3) {
			number_of_interval--;
			velocity.v_y = velocity.v_y - EarthGravity * time(it3->first, x0);
			if (yMove(time(it3->first, x0)) < it3->second && yMove(time(it3->first, x0)) > 0) {
				wall_x = it3->first; wall_y = it3->second;
				ymove = yMove(time(it3->first, x0));

				h0 = yMove(time(it3->first, x0));
				x0 = it3->first;
				velocity.v_x = -velocity.v_x;
				velocity.v_y = velocity.v_y - EarthGravity * time(it3->first, x0);

				number_of_interval--;
				break; //����� ������������ - ������� �� �����
			}

			else if (yMove(time(it3->first, x0)) < 0)
			{
				std::cout << interval.find(it1->first)->second << std::endl;
				return;
			}
		}

		//�� ��� ��� �� �������� ������ ������ �����, ��������� ����������� �������� ����������
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

int main(void) {
	Ball ball("in.txt");
	ball.KudaUpal();

	return 0;
}