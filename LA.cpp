#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>
#include <cmath>
#include <io.h>

typedef std::pair<double, double> Point;
typedef std::vector<Point> ListOfPoints;
typedef std::vector<double> Distances;
typedef std::pair<Point, double> PointAndDistance;
typedef std::vector<PointAndDistance> ListOfPointAndDistances;

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
	ListOfPointAndDistances list_of_points_and_distances;

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
	distances.reserve(x.size());

	for (long int i = 0; i < x.size(); i++)
	{
		distances.push_back(abs(line.A * x.at(i) + line.B * y.at(i) + line.C) / (sqrt(line.A * line.A + line.B * line.B)));
		point_and_distance.first = points.at(i);
		point_and_distance.second = distances.at(i);
		list_of_points_and_distances.push_back(point_and_distance);
	}

	double max_distance = 0, min_distance = 0;

	max_distance = *std::max_element(distances.begin(), distances.end());
	min_distance = *std::min_element(distances.begin(), distances.end());

	Point rightmost_point;
	Point leftmost_point;

	for (ListOfPointAndDistances::const_iterator it = list_of_points_and_distances.begin(); it != list_of_points_and_distances.end(); ++it)
	{
		if ((it->second) == max_distance)
			rightmost_point = it->first;

		if ((it->second) == min_distance)
			leftmost_point = it->first;
	}

	std::cout << "Leftmost: " << leftmost_point.first << ' ' << leftmost_point.second << "\n";
	std::cout << "Rightmost: " << rightmost_point.first << ' ' << rightmost_point.second;

}

int main(void)
{
	PointsSearching search;
	search.searchLeftRight();
	return 0;
}
