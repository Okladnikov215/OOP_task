#pragma once

#include "Shapes.h"

class ShapeFactory
{
public:
	static Shape * makeRandomShape()
	{
		switch (rand() % SHAPETYPESCOUNT)
		{
		case 0:
			return makePoint();
		case 1:
			return makeCircle();
		case 2:
			return makeRect();
		case 3:
			return makeSquare();
		case 4:
			return makePolyline();
		case 5:
			return makePolygon();
		default:
			assert(false);
			return nullptr;
		}
	}

	static Point * makePoint()
	{
		double x = randomDouble(-MAXRAND, MAXRAND);
		double y = randomDouble(-MAXRAND, MAXRAND);

		return new Point(x, y);
	}

	static Circle * makeCircle()
	{
		Point * center = makePoint();
		double radius = randomDouble(-MAXRAND, MAXRAND);

		Circle * circle = new Circle(*center, radius);
		delete center;
		return circle;
	}

	static Rect * makeRect()
	{
		Point * vertex1 = makePoint();
		Point * vertex2 = makePoint();

		Rect * rect = new Rect(*vertex1, *vertex2);
		delete vertex1;
		delete vertex2;
		return rect;
	}

	static Square * makeSquare()
	{
		Point * vertex = makePoint();
		double width = randomDouble(-MAXRAND, MAXRAND);

		Square * sqr = new Square(*vertex, width);
		delete vertex;
		return sqr;
	}

	static Polyline * makePolyline()
	{
		Point * vertex1 = makePoint();
		Point * vertex2 = makePoint();
		Polyline * polyline = new Polyline(*vertex1, *vertex2);
		delete vertex1;
		delete vertex2;
		for (int i = 0, vertCount = rand() % MAXVERT; i < vertCount; ++i)
		{
			Point * newVertex = makePoint();
			polyline->addVertex(*newVertex);
			delete newVertex;
		}
		return polyline;
	}

	static Polygon * makePolygon()
	{
		Container<Point> vertices;

		for (int i = 0, vertCount = rand() % MAXVERT; i < vertCount + 3; ++i)
		{
			Point * newVertex = makePoint();
			vertices.addFirst(*newVertex);
			delete newVertex;
		}
		return new Polygon(vertices);
	}

private:
	static double randomDouble(double min, double max)
	{
		double random = (double)rand() / RAND_MAX;
		return min + random * (max - min);
	}

	static unsigned int const MAXVERT = 16;
	static double constexpr MAXRAND = 64;
	static unsigned int const SHAPETYPESCOUNT = 6;

};