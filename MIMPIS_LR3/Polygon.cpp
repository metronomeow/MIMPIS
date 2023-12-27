#include "Polygon.h"

Polygon operator+( Polygon & r1, Rectangle & r2 ) {
    Polygon result;
    std::vector <Point> newPoints = r1.findCrossPoints( r2 );
    if( !newPoints.size() ) return r1;
    for( auto p : r1.points ) result.points.push_back( p );
    for( auto p : newPoints ) result.points.push_back( p );
    for( size_t i = 0; i < result.points.size(); i++ ) {
        if( result.points[ i ].isInside( r2 ) ) 
            result.points.erase( result.points.begin() + i );
        //if( std::find( result.points.begin(), result.points.end(), result.points.begin() + i )
    }
    return result;
}

Polygon operator+( Rectangle & r1, Rectangle & r2 ) {
    Polygon * polygon = r1.castToPolygon();
    Polygon result = (*polygon) + r2;
    delete polygon;
    return result;
}

std::vector<Point> Polygon::findCrossPoints( Rectangle & rect ) {
     std::vector<Point> res;
     for( size_t i = 0; i < points.size() - 1; i++ ) {
        rect.isCrossLine( points[ i ], points[ i + 1 ], res );
        //if( !res.size() ) continue;
     }

     rect.isCrossLine( points[ 0 ], points[ points.size() - 1 ], res );
     return res;
}
