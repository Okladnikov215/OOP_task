#pragma once

#include <sstream>
#include <cmath>
#include "Base.h"
#include "Container.h"

class Shape : public Printable
{
public:
	Shape()
	{
		++count;
	}

	Shape(Shape const & shape)
	{
		++count;
	}

	virtual ~Shape()
	{
		--count;
	}

	static unsigned int getCount()
	{
		return count;
	}

private:
	static unsigned int count;
};

//TODO .cpp
unsigned int Shape::count = 0;

class Point : public Shape, public Named
{
public:
	Point(double x, double y)
		: Named("Point")
		, x(x)
		, y(y)
	{}

	virtual std::string print() const override
	{
		std::stringstream formatStream;
		formatStream << Named::print() << "(" << x << ", " << y << ")";
		return formatStream.str();
	}

	double getX() const
	{
		return x;
	}

	double getY() const
	{
		return y;
	}

private:
	double x;
	double y;
};

double distance(Point const & point1, Point const & point2)
{
	return sqrt(pow(point1.getX() - point2.getX(), 2) + pow(point1.getY() - point2.getY(), 2));
}

class Circle : public Shape, public Named
{
public:
	Circle(Point const & center, double radius)
		: Named("Circle")
		, center(center)
		, radius(radius)
	{}
	Circle(double x, double y, double center)
		: Circle(Point(x, y), center)
	{}

	Point const & getCenter() const
	{
		return center;
	}

	double getRadius() const
	{
		return radius;
	}

	std::string print() const override
	{
		std::stringstream formatStream;
		formatStream << Named::print() << " with center in " << getCenter().print()
			<< " and radius = " << getRadius();
		return formatStream.str();
	}
private:
	Point center;
	double radius;
};

class Rect : public Shape, virtual public Named
{
public:
	Rect(Point const & vertex1, Point const & vertex2)
		: Named("Rect")
		, vertex1(vertex1)
		, vertex2(vertex2)
	{}

	Rect(double x1, double y1, double x2, double y2)
		: Rect(Point(x1, y1), Point(x2, y2))
	{}

	Rect(Point const & vertex, double width, double height)
		: Rect(vertex, Point(vertex.getX() + width, vertex.getY() + height))
	{}

	Point const & getVertex1() const
	{
		return vertex1;
	}

	Point const & getVertex2() const
	{
		return vertex2;
	}

	double getWidth() const
	{
		return fabs(vertex2.getX() - vertex1.getX());
	}

	double getHeight() const
	{
		return fabs(vertex2.getY() - vertex1.getY());
	}

	double getPerimeter() const
	{
		return (getWidth() + getHeight()) * 2;
	}

	double getArea() const
	{
		return getWidth() * getHeight();
	}

	std::string print() const override
	{
		std::stringstream formatStream;
		formatStream << Named::print()
			<< " with vertices in " << getVertex1().print()
			<< " and " << getVertex2().print()
			<< ", perimeter = " << getPerimeter()
			<< ", area = " << getArea();
		return formatStream.str();
	}

private:
	Point vertex1;
	Point vertex2;
};

class Square : public Rect, virtual public Named
{
public:
	Square(Point const & vertex, double width)
		: Rect(vertex, width, width), Named("Square")
	{}
	Square(double x, double y, double width)
		: Square(Point(x, y), width)
	{}
};

class Polyline : public Shape, virtual public Named
{
public:
	Polyline(Container<Point> const & vertices)
		: Named("Polyline")
		, vertices(vertices)
	{}

	Polyline(Point const & vertex1, Point const & vertex2)
		: Named("Polyline")
	{
		vertices.addLast(vertex1);
		vertices.addLast(vertex2);
	}

	//addPoint
	void addVertex(Point const & vertex)
	{
		vertices.addLast(vertex);
	}

	virtual double getLength() const
	{
		double length = 0;
		Point prevVer = vertices.getFirst();

		vertices.forEach(
			[&length, &prevVer](Point const & nextVer)
		{
			length += distance(prevVer, nextVer);
			prevVer = nextVer;
		}
		);

		return length;
	}

	std::string print() const override
	{
		std::stringstream formatStream;
		formatStream << Named::print() << " with vertices: ";
		vertices.forEach(
			[&formatStream](Point const & v) {formatStream << v.print() << " "; }
		);
		formatStream << " and length: " << getLength();
		return formatStream.str();
	}

protected:
	Container<Point> vertices;
};

class Polygon : public Polyline, virtual public Named
{
public:
	Polygon(Container<Point> const & vertices)
		: Polyline(vertices)
		, Named("Polygon")
	{}

	double getLength() const override
	{
		return Polyline::getLength() + distance(vertices.getFirst(), vertices.getLast());
	}

	std::string print() const override
	{
		std::stringstream formatStream;
		formatStream << Named::print() << " with vertices: ";
		vertices.getFirst().print();
		vertices.forEach(
			[&formatStream](Point const & v) {
			v.getX();
			v.getY();
			v.print();
			formatStream << v.print() << " ";
		}
		);
		formatStream << " and perimeter: " << getLength();
		return formatStream.str();
	}
};