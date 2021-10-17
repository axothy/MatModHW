#include "LA.h"

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
	for (int i = 0; i < x.size(); i++) {
		std::cout << x.at(i) << ' ';
	}

	std::cout << '\n';

	for (int i = 0; i < y.size(); i++) {
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
	PointsSearching search;
	search.searchLeftRight();

	return 0;
}