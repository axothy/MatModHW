#include <thread>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

class Figure {
public:
	virtual void getData() = 0;
	virtual bool isDotInFigure(int x, int y) = 0;

	virtual std::vector<std::pair<double, double>> getPoints() = 0;

	virtual double getRadius() = 0;
	virtual double getXCenter() = 0;
	virtual double getYCenter() = 0;
	virtual double getX1() = 0;
	virtual double getX2() = 0;
	virtual double getX3() = 0;
	virtual double getX4() = 0;
	virtual double getY1() = 0;
	virtual double getY2() = 0;
	virtual double getY3() = 0;
	virtual double getY4() = 0;
};

class Circle : public Figure {
	double radius_, x_, y_;
public:
	Circle(double r, double x, double y) {
		radius_ = r;
		x_ = x;
		y_ = y;
	}
	bool isDotInFigure(int x, int y) {
		if ((x_ - x) * (x_ - x) + (y_ - y) * (y_ - y) < radius_ * radius_) {
			return true;
		}
		return false;
	}
	void getData() { std::cout << "CIRCLE" << std::endl; }

	double getRadius() override { return radius_; }
};

class Rectangle : public Figure {
	double x1_, y1_, x2_, y2_, x3_, y3_, x4_, y4_;
public:
	Rectangle(double x1, double y1, double x3, double y3) {
		x1_ = x1;
		y1_ = y1;
		x2_ = x3;
		y2_ = y1;
		x3_ = x3;
		y3_ = y3;
		x4_ = x1;
		y4_ = y3;
	}
	bool isDotInFigure(int x, int y) {
		if (x > x1_ && y > y1_ && x < x3_ && y < y3_) {
			return true;
		}
		return false;
	}

	void getData() { std::cout << "RECT" << std::endl; }

};

class Polygon : public Figure {
	std::vector<std::pair<double, double>> points;
public:
	Polygon(std::vector<std::pair<double, double>>& pts) {
		points = pts;
	}
	void getData() { std::cout << "POLY" << std::endl; }

	bool isDotInFigure(int x, int y) { return 0; }

};

class Reader {
public:
	Reader(std::vector<Figure*>& figures) {
		std::ifstream input("input.txt");

		if (input.is_open() == false || input.eof()) {
			exit(0);
		}

		std::string inputstr;

		input >> inputstr;

		while (!input.eof()) {
			if (inputstr == "RECTANGLE") {
				double x1, y1, x3, y3;
				input >> x1 >> y1 >> x3 >> y3;
				figures.push_back(new Rectangle(x1, y1, x3, y3));
				input >> inputstr;
			}
			else if (inputstr == "CIRCLE") {
				double r, x, y;
				input >> r >> x >> y;
				figures.push_back(new Circle(r, x, y));
				input >> inputstr;
			}
			else if (inputstr == "POLYGON") {
				std::vector<std::pair<double, double>> points;
				std::pair<double, double> point;
				std::string checkStr;

				while (!input.eof()) {
					input >> checkStr;
					if (checkStr == "CIRCLE" || checkStr == "RECTANGLE") {
						break;
					}

					std::stringstream ss(checkStr);
					ss >> point.first;
					input >> point.second;
					points.push_back(point);
				}
				figures.push_back(new Polygon(points));
				inputstr = checkStr;

			}


		}
	}

	Reader(std::string& initstr) {
		std::ifstream input("input.txt");

		if (input.is_open() == false) {
			exit(0);
		}

		std::string inputstr;

		while (!input.eof()) {
			input >> inputstr;
			initstr = inputstr + ' ';
			if (inputstr == "RECTANGLE") {
				for (int i = 0; i < 4; i++) {
					input >> inputstr;
					initstr += inputstr + ' ';
				}
			}
			else if (inputstr == "CIRCLE") {
				for (int i = 0; i < 3; i++) {
					input >> inputstr;
					initstr += inputstr + ' ';
				}
			}
			else if (inputstr == "POLYGON") {

			}
		}

	}
};

class Initializer {
public:
	void InitFigures(const std::string& initstring, std::vector<Figure*>& figures) {
		std::stringstream datastream(initstring);
		std::string datastring;
		datastream >> datastring;
		if (datastring == "RECTANGLE") {
			double x1, y1, x3, y3;
			datastream >> x1 >> y1 >> x3 >> y3;
			figures.push_back(new Rectangle(x1, y1, x3, y3));
		}
		else if (datastring == "CIRCLE") {
			double r, x, y;
			datastream >> r >> x >> y;
			figures.push_back(new Circle(r, x, y));

		}
		else if (datastring == "POLYGON") {

		}
	}
};

int main()
{
	std::vector<Figure*> figures;


	Reader readfile(figures);
	for (int i = 0; i < figures.size(); i++) {
		figures[i]->getData();
	}


	return 0;
}
