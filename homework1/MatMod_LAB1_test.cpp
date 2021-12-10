// MatMod_LAB1_test.cpp: определяет точку входа для приложения.
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>

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

	/*distances.reserve(x.size());
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
	*/

	double X_L = 0;
	double Y_L = 0;
	double X_R = 0;
	double Y_R = 0;
	double X_Lm = 0;
	double Y_Lm = 0;
	double X_Rmax = 0;
	double Y_Lmax = 0;
	double H_L1;
	double H_R1;
	double Y_Rms;
	double X_Rms;
	double H_Rstart = fabs((line.yn * X_R - line.xn * Y_R) / sqrt(line.xn * line.xn + line.yn * line.yn));
	double H_Lstart = fabs((line.yn * X_L - line.xn * Y_L) / sqrt(line.xn * line.xn + line.yn * line.yn));

	for (int i = 0; i < x.size(); ++i) {
		if (line.yn * x.at(i) - line.xn * y.at(i) < 0) {
			X_L = x.at(i);
			Y_L = y.at(i);
			H_L1 = fabs((line.yn * X_L - line.xn * Y_L) / sqrt(line.xn * line.xn + line.yn * line.yn));
			if (H_L1 >= H_Lstart) {
				H_Lstart = H_L1;
				X_Lm = x.at(i);
				Y_Lm = y.at(i);
			}
		}
		else {
			X_R = x.at(i);
			Y_R = y.at(i);
			H_R1 = fabs((line.yn * X_R - line.xn * Y_R) / sqrt(line.xn * line.xn + line.yn * line.yn));
			if (H_R1 >= H_Rstart) {
				H_Rstart = H_R1;
				X_Rmax = x.at(i);
				Y_Lmax = y.at(i);
			}
			if (H_R1 == 0) {
				X_Rms = x.at(i);
				Y_Rms = y.at(i);
			}
		}
	}

	if (H_R1 == 0) {
		std::cout << "Leftmost: " << X_Lm << " " << Y_Lm << "\n";
		std::cout << "Rightmost: " << X_Rms << " " << Y_Rms << "\n";
	}
	else {
		std::cout << "Leftmost: " << X_Lm << " " << Y_Lm << "\n";
		std::cout << "Rightmost: " << X_Rmax << " " << Y_Lmax << "\n";
	}
}

int main(void)
{
	PointsSearching search;
	search.searchLeftRight();

	return 0;
}
