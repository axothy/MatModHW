#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iterator>

#include <cmath>
#include <stdint.h>

#include <io.h>

typedef std::pair<double, double> Point;
typedef std::vector<Point> ListOfPoints;
typedef std::vector<double> Distances;
typedef std::pair<Point, double> PointAndDistance;
typedef std::vector<PointAndDistance> ListOfPointAndDistances;

struct Line {
	double x0, y0;
	double xn, yn;

	double A = y0 - yn;
	double B = x0 - xn;
	double C = x0 * yn - xn * y0;
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

	line.A = line.y0 - line.yn;
	line.B = line.x0 - line.xn;
	line.C = line.x0 * line.yn - line.xn * line.y0;

	while (!file.eof()) 
	{
		file >> tmpx >> tmpy;
		x.push_back(tmpx);
		y.push_back(tmpy);
		point.first = tmpx;
		point.second = tmpy;
		points.push_back(point);
	}

	
}

inline void PointsSearching::getVectors()
{
	for (uint8_t i = 0; i < x.size(); i++) {
		std::cout << x.at(i) << ' ';
	}

	for (uint8_t i = 0; i < y.size(); i++) {
		std::cout << y.at(i) << ' ';
	}
}

void PointsSearching::searchLeftRight()
{
	distances.reserve(x.size());

	for (uint8_t i = 0; i < x.size(); i++)
	{
		distances.push_back((line.A * x.at(i) + line.B * y.at(i) + line.C) / (sqrt(line.A * line.A + line.B * line.B)));
		point_and_distance.first = points.at(i);
		point_and_distance.second = distances.at(i);
		list_of_points_and_distances.push_back(point_and_distance);
	}

	std::cout << "Distances:\n";
	for (auto i = distances.begin(); i !=distances.end(); ++i)
		std::cout << *i << ' ';
	std::cout << "\n";


	double max_distance=0;
	for (ListOfPointAndDistances::const_iterator it = list_of_points_and_distances.begin(); it != list_of_points_and_distances.end(); ++it)
	{
		if(max_distance < abs(it->second))
		max_distance = abs(it->second);
	}

	Point max_point;

	for (ListOfPointAndDistances::const_iterator it = list_of_points_and_distances.begin(); it != list_of_points_and_distances.end(); ++it)
	{
		if (abs(it->second) == max_distance)
			max_point = it->first;
	}

	std::cout << "Point:\n";
	std::cout << max_point.first << ' ';
	std::cout << max_point.second;

}

int main(void)
{
	PointsSearching search;
	search.searchLeftRight();
	return 0;
}
