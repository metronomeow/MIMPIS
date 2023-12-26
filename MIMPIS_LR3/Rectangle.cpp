#include "Rectangle.h"
#include"Polygon.h"

void Rectangle::computeHeightWidth() {
    int height = topRight.y() - origin.y();
    int width = topRight.x() - origin.x();
}

Rectangle::Rectangle( const std::string & layer, const Point & origin, const Point & topRight ) : layer( layer ), origin( origin ), topRight( topRight ) {
    computeHeightWidth();
}

bool Rectangle::isRect() {
    if( origin > topRight ) return false;
    return true;
}

bool Rectangle::isEmpty() {
    if( layer != "" ) return false;
    if( origin != Point(0,0) ) return false;
    if( topRight != Point(0,0) ) return false;
    if( width != 0 ) return false;
    if( height != 0 ) return false;
    return true;
}

Polygon * Rectangle::castToPolygon() {
    Polygon * pol = new Polygon( { origin, Point( origin.x(), topRight.y() ), topRight, Point( topRight.x(), origin.y() ) } );
    return pol;
}

void Rectangle::isCrossLine( Point start, Point end, Point * result ) {
    result = nullptr;
    if( start > end ) {
        Point swap( start );
        start = end; 
        end = swap;
    }
    if( start.isInside( *this ) and end.isInside( *this ) ) return;
    //if( !start.isInside( *this ) and !end.isInside( *this ) ) return;
    //to do если линия насквозь через прямоугольник то тоже пересекает, посчитать точки (и их 2...)
    if( start.x() == end.x() ) { //vertical
        if( start.y() <= origin.y() and origin.y() <= end.y() ) result = new Point( start.x(), origin.y() );
        if( start.y() <= topRight.y() and topRight.y() <= end.y() )  result = new Point( start.x(), topRight.y() );
    }
    if( start.y() == end.y() ) { //horizontal
        if( start.x() <=   origin.x() and origin.x() <= end.x() )  result = new Point( origin.x(), start.y() );
        if( start.x() <= topRight.x() and topRight.x() <= end.x() )  result = new Point( topRight.x(), start.y() );
    }
}

bool operator>( Point & a, Point & b ) {
    if( a.x() >= b.x() or a.y() >= b.y() ) return true;
    return false;
}

Rectangle operator&( Rectangle & r1, Rectangle & r2 ) {
    Point orig( std::max( r1.getOrigin().x(), r2.getOrigin().x() ), std::max( r1.getOrigin().y(), r2.getOrigin().y() ) );
    Point topR( std::min( r1.getTopRight().x(), r2.getTopRight().x() ), std::min( r1.getTopRight().y(), r2.getTopRight().y() ) );
    Rectangle rect( "", orig, topR );
    if( rect.isRect() )
        return rect;
    else return Rectangle();
}


bool Point::isInside( Rectangle & rect ) {
    return ( rect.getOrigin().x() <= x() and x() <= rect.getTopRight().x() ) and ( rect.getOrigin().y() <= y() and y() <= rect.getTopRight().y() );
}
