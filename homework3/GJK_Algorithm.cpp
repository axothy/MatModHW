#include <thread>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

struct _vec2 { double x; double y; };
using vec2 = _vec2;

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

	std::vector<std::pair<double, double>> getPoints() { return {}; }
	double getRadius() override { return radius_; }
	double getXCenter() override { return x_; }
	double getYCenter() override { return y_; }

	double getX1() { return -1; }
	double getX2() { return -1; }
	double getX3() { return -1; }
	double getX4() { return -1; }
	double getY1() { return -1; }
	double getY2() { return -1; }
	double getY3() { return -1; }
	double getY4() { return -1; }
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

	std::vector<std::pair<double, double>> getPoints() { return {}; }
	double getRadius() override { return -1; }
	double getXCenter() override { return -1; }
	double getYCenter() override { return -1; }


	double getX1() override { return x1_; }
	double getX2() override { return x2_; }
	double getX3() override { return x3_; }
	double getX4() override { return x4_; }
	double getY1() override { return y1_; }
	double getY2() override { return y2_; }
	double getY3() override { return y3_; }
	double getY4() override { return y4_; }
};

class Polygon : public Figure {
	std::vector<std::pair<double, double>> points;
public:
	Polygon(std::vector<std::pair<double, double>>& pts) {
		points = pts;
	}
	void getData() { std::cout << "POLY" << std::endl; }

	bool isDotInFigure(int x, int y) { return 0; }

	std::vector<std::pair<double, double>> getPoints() override { return points; }

	double getX1() { return -1; }
	double getX2() { return -1; }
	double getX3() { return -1; }
	double getX4() { return -1; }
	double getY1() { return -1; }
	double getY2() { return -1; }
	double getY3() { return -1; }
	double getY4() { return -1; }

	double getRadius() override { return -1; }
	double getXCenter() override { return -1; }
	double getYCenter() override { return -1; }
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

class CollisionDetector {
public:
	CollisionDetector();
	CollisionDetector(std::vector<Figure*>& figures);

	std::vector<std::pair<int, int>> collided_figures;

	void showCollisions();

	vec2 Jostle(vec2 a);

	int gjk(const vec2* vertices1, size_t count1,
		const vec2* vertices2, size_t count2);

private:

	//Basic vector arithmetic operations
	vec2 subtract(vec2 a, vec2 b) { a.x -= b.x; a.y -= b.y; return a; }
	vec2 negate(vec2 v) { v.x = -v.x; v.y = -v.y; return v; }
	vec2 perpendicular(vec2 v) { vec2 p = { v.y, -v.x }; return p; }
	double dotProduct(vec2 a, vec2 b) { return a.x * b.x + a.y * b.y; }
    double lengthSquared(vec2 v) { return v.x * v.x + v.y * v.y; }
	vec2 tripleProduct(vec2 a, vec2 b, vec2 c);
	vec2 averagePoint(const vec2* vertices, size_t count);
	size_t indexOfFurthestPoint(const vec2* vertices, size_t count, vec2 d);
	vec2 support(const vec2* vertices1, size_t count1,
		const vec2* vertices2, size_t count2, vec2 d);
	double Perturbation();

};


// Triple product expansion is used to calculate perpendicular normal vectors
// which kinda 'prefer' pointing towards the Origin in Minkowski space

vec2 CollisionDetector::tripleProduct(vec2 a, vec2 b, vec2 c) {

	vec2 r;

	float ac = a.x * c.x + a.y * c.y; // perform a.dot(c)
	float bc = b.x * c.x + b.y * c.y; // perform b.dot(c)

	// perform b * a.dot(c) - a * b.dot(c)
	r.x = b.x * ac - a.x * bc;
	r.y = b.y * ac - a.y * bc;
	return r;
}

// This is to compute average center (roughly). It might be different from
// Center of Gravity, especially for bodies with nonuniform density,
// but this is ok as initial direction of simplex search in GJK.
vec2 CollisionDetector::averagePoint(const vec2* vertices, size_t count) {
	vec2 avg = { 0.f, 0.f };
	for (size_t i = 0; i < count; i++) {
		avg.x += vertices[i].x;
		avg.y += vertices[i].y;
	}
	avg.x /= count;
	avg.y /= count;
	return avg;
}


// Get furthest vertex along a certain direction
size_t CollisionDetector::indexOfFurthestPoint(const vec2* vertices, size_t count, vec2 d) {

	float maxProduct = dotProduct(d, vertices[0]);
	size_t index = 0;
	for (size_t i = 1; i < count; i++) {
		float product = dotProduct(d, vertices[i]);
		if (product > maxProduct) {
			maxProduct = product;
			index = i;
		}
	}
	return index;
}

// Minkowski sum support function for GJK
vec2 CollisionDetector::support(const vec2* vertices1, size_t count1,
	const vec2* vertices2, size_t count2, vec2 d) {

	// get furthest point of first body along an arbitrary direction
	size_t i = indexOfFurthestPoint(vertices1, count1, d);

	// get furthest point of second body along the opposite direction
	size_t j = indexOfFurthestPoint(vertices2, count2, negate(d));

	// subtract (Minkowski sum) the two points to see if bodies 'overlap'
	return subtract(vertices1[i], vertices2[j]);
}

double CollisionDetector::Perturbation()
{
	return ((double)rand() / (double)RAND_MAX) * FLT_EPSILON * 100.0f * ((rand() % 2) ? 1.0f : -1.0f);
}

vec2 CollisionDetector::Jostle(vec2 a)
{
	vec2 b;
	b.x = a.x + Perturbation();
	b.y = a.y + Perturbation();
	return b;
}

int CollisionDetector::gjk(const vec2* vertices1, size_t count1,
	const vec2* vertices2, size_t count2) {

	int itercount = 0;
	size_t index = 0; // index of current vertex of simplex
	vec2 a, b, c, d, ao, ab, ac, abperp, acperp, simplex[3];

	vec2 position1 = averagePoint(vertices1, count1); // not a CoG but
	vec2 position2 = averagePoint(vertices2, count2); // it's ok for GJK )

	// initial direction from the center of 1st body to the center of 2nd body
	d = subtract(position1, position2);

	// if initial direction is zero – set it to any arbitrary axis (we choose X)
	if ((d.x == 0) && (d.y == 0))
		d.x = 1.f;

	// set the first support as initial point of the new simplex
	a = simplex[0] = support(vertices1, count1, vertices2, count2, d);

	if (dotProduct(a, d) <= 0)
		return 0; // no collision

	d = negate(a); // The next search direction is always towards the origin, so the next search direction is negate(a)

	while (1) {
		itercount++;

		a = simplex[++index] = support(vertices1, count1, vertices2, count2, d);

		if (dotProduct(a, d) <= 0)
			return 0; // no collision

		ao = negate(a); // from point A to Origin is just negative A

		// simplex has 2 points (a line segment, not a triangle yet)
		if (index < 2) {
			b = simplex[0];
			ab = subtract(b, a); // from point A to B
			d = tripleProduct(ab, ao, ab); // normal to AB towards Origin
			if (lengthSquared(d) == 0)
				d = perpendicular(ab);
			continue; // skip to next iteration
		}

		b = simplex[1];
		c = simplex[0];
		ab = subtract(b, a); // from point A to B
		ac = subtract(c, a); // from point A to C

		acperp = tripleProduct(ab, ac, ac);

		if (dotProduct(acperp, ao) >= 0) {

			d = acperp; // new direction is normal to AC towards Origin

		}
		else {

			abperp = tripleProduct(ac, ab, ab);

			if (dotProduct(abperp, ao) < 0)
				return 1; // collision

			simplex[0] = simplex[1]; // swap first element (point C)

			d = abperp; // new direction is normal to AB towards Origin
		}

		simplex[1] = simplex[2]; // swap element in the middle (point B)
		--index;
	}

	return 0;
}

CollisionDetector::CollisionDetector(std::vector<Figure*>& figures) {



}

void CollisionDetector::showCollisions() {

}

int main()
{
	std::vector<Figure*> figures;


	Reader readfile(figures);
	for (int i = 0; i < figures.size(); i++) {
		figures[i]->getData();
	}

	CollisionDetector collisions(figures);

   vec2 vertices1[] = {
{ 2.0f, 2.0f },
{ 2.0f, -2.0f },
{ -2.0f, -2.0f },
{-2.0f, 2.0f},
	};

	vec2 vertices2[] = {
	{ 0.0f, 0.0f },
	{ 5.0f, -5.0f },
	{ -5.0f, -5.0f },
	};

	size_t count1 = sizeof(vertices1) / sizeof(vec2); // == 3
	size_t count2 = sizeof(vertices2) / sizeof(vec2); // == 4


	vec2 a[sizeof(vertices1) / sizeof(vec2)];
	vec2 b[sizeof(vertices2) / sizeof(vec2)];

	for (size_t i = 0; i < count1; ++i) a[i] = collisions.Jostle(vertices1[i]);
	for (size_t i = 0; i < count2; ++i) b[i] = collisions.Jostle(vertices2[i]);

	int collisionDetected = collisions.gjk(a, count1, b, count2);
	if (collisionDetected)
	{
		printf("Collision detected!\n");
	}

	return 0;
}
