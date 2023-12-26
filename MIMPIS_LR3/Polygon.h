#pragma once
#include <vector>
#include "Rectangle.h"


class Polygon {
public:
    std::vector<Point> points;
    Polygon() {};
    Polygon( std::vector<Point> points ) : points(points) {};
    std::vector<Point> findCrossPoints( Rectangle & rect );
};


Polygon operator+ ( Polygon & r1, Rectangle & r2 );
Polygon operator+ ( Rectangle & r1, Rectangle & r2 );