#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>
#include <cmath>
#include <io.h>
#include <stdint.h>

#include <chrono>

typedef std::pair<double, double> Point;
typedef std::vector<Point> ListOfPoints;
typedef std::vector<double> Distances;
typedef std::pair<Point, double> PointAndDistance;

struct Line {
	double x0, y0;
	double xn, yn;

	double A;
	double B;
	double C;
};

class PointsSearching {

private:
	Line line;

	std::vector<double> x;
	std::vector<double> y;
	Point point;
	ListOfPoints points;

	Distances distances;
	PointAndDistance point_and_distance;

public:

	static const std::string filename;
	std::ifstream file;

	PointsSearching();
	~PointsSearching() { file.close(); }

	inline void getVectors();
	void searchLeftRight();
};

const std::string PointsSearching::filename = "in.txt";

PointsSearching::PointsSearching()
{
	file.open(filename);
	double tmpx, tmpy;

	file >> tmpx >> tmpy;
	line.x0 = 0; line.y0 = 0;
	line.xn = tmpx; line.yn = tmpy;

	line.A = line.yn - line.y0;
	line.B = line.x0 - line.xn;
	line.C = line.xn * line.y0 - line.x0 * line.yn;

	std::cout << line.A << " " << line.B << " " << line.C << " \n\n";

	do {
		file >> point.first >> point.second;
		x.push_back(point.first);
		y.push_back(point.second);
		points.push_back(point);

	} while (!file.eof());
}

inline void PointsSearching::getVectors()
{
	for (long int i = 0; i < x.size(); i++) {
		std::cout << x.at(i) << ' ';
	}

	std::cout << '\n';

	for (long int i = 0; i < y.size(); i++) {
		std::cout << y.at(i) << ' ';
	}
}

void PointsSearching::searchLeftRight()
{
	Point rightmost_point;
	Point leftmost_point;

	distances.reserve(x.size());
	double max_distance = 0, min_distance = 0;

	double sqrt_denominator = sqrt(line.A * line.A + line.B * line.B); //for algorithm efficiency

	distances.push_back(abs(line.A * x.at(0) + line.B * y.at(0) + line.C) / (sqrt_denominator));
	point_and_distance.first = points.at(0);
	point_and_distance.second = distances.at(0);
	max_distance = distances.at(0);
	min_distance = distances.at(0);

	for (int i = 1; i < x.size(); i++)
	{
		distances.push_back(abs(line.A * x.at(i) + line.B * y.at(i) + line.C) / (sqrt_denominator));
		point_and_distance.first = points.at(i);
		point_and_distance.second = distances.at(i);

		if (max_distance < distances.at(i)) { max_distance = distances.at(i); rightmost_point = points.at(i); }
		if (min_distance > distances.at(i)) { min_distance = distances.at(i); leftmost_point = points.at(i); }
	}

	std::cout << "Leftmost: " << leftmost_point.first << ' ' << leftmost_point.second << "\n";
	std::cout << "Rightmost: " << rightmost_point.first << ' ' << rightmost_point.second;

}

int main(void)
{
	auto start_time = std::chrono::steady_clock::now();

	//начало кода для таймера
	PointsSearching search;
	search.searchLeftRight();
	std::cout << "\n\n";
	//конец кода для таймера

	auto end_time = std::chrono::steady_clock::now();
	auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
	std::cout << elapsed_ns.count() << " nanosec\n";

	return 0;
}
