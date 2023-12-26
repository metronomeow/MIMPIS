#pragma once
#include <string>

class Polygon;
class Rectangle;
class Point : public std::pair<int, int> {

public:
    int x() const { return first; }
    int y() const { return second; }
    Point() = default;
    Point( int a, int b ) : std::pair<int, int>( a, b ) {};
    bool  isInside( Rectangle & rect );
};

// a>b:   if ( a not lefter than b ) and ( a not lower than  b )
bool operator> ( Point & a, Point & b );

class Rectangle {
    std::string layer;
    Point origin;
    Point topRight;
    int height;
    int width;
    void computeHeightWidth();
public:
    std::string getLayer() const { return layer; }
    
    Point getOrigin() const { return origin; }
    Point getTopRight() const { return topRight; }

    void setOrigin( int x, int y ) { origin = Point( x, y ); computeHeightWidth(); }
    void setTopRight( int x, int y ) { topRight = Point( x, y ); computeHeightWidth(); }

    Rectangle() : layer(""), origin(0,0), topRight(0,0), height(0), width(0) {};
    Rectangle( const std::string & layer, const Point & origin, const Point & topRight );

    bool isRect();
    bool isEmpty();
    Polygon * castToPolygon();
    void isCrossLine( Point start, Point end, Point * result );
};


Rectangle operator& ( Rectangle & r1, Rectangle & r2 );