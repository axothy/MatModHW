#include <thread>
#include <iostream>
#include <fstream>
#include <vector>

class Figure {

};

class Circle : public Figure {
	double _radius, _x, _y;
public:
	Circle(double r, double x, double y) {
		_radius = r;
		_x = x;
		_y = y;
	}
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
};

class Polygon : public Figure {

};

class Reader {
public:
	Reader(std::string& initstr) {
		std::ifstream input("input.txt");

		if (input.is_open() == false) {
			exit(0);
		}

		std::string inputstr;
		std::string initstr;

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
	std::string initstring;
	std::vector<Figure*> figures;

	auto reading = [&initstring]() {
		Reader readfile(initstring);
	};

	std::thread read(reading);

	Initializer initializer;

	auto initialization = [&initstring, &figures](Initializer initializer)->Initializer {
		initializer.InitFigures(initstring, figures);
	};

	std::thread init(initialization(initializer));


	read.join();
	init.join();

	return 0;
}
