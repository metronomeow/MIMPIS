#include "Object.h"
#include<fstream>
#include <iostream>


void Object::readObj( std::ifstream & fs ) {
    std::string buf;
    std::string layer;
    bool end = false; 
    if( type == pin ) {
        fs >> buf;
        name = buf;
    }
    while( fs >> buf ) {
        if( end ) break;
        if( buf == "END" ) end = true;

        if( buf == "LAYER" ) {
            fs >> buf;
            layer = buf;
            while( fs >> buf ) {
                if( buf == "END" ) break;
                if( buf == "RECT" ) {
                    int a, b, c, d;
                    fs >> a >> b >> c >> d >> buf;
                    addRect( layer, a, b, c, d );
                }
            }
        }
    }

}

void Object::addRect( std::string layer, int leftX, int leftY, int rightX, int rightY ) {
    Rectangle * rect = new Rectangle( layer, Point( leftX, leftY ), Point( rightX, rightY ) );
    rects.push_back( rect );
}

Object::~Object() {
    for( auto r : rects ) {
        delete r;
    }
    rects.clear();
}

void Nmos::andOperation( std::ofstream & f ) {
    std::vector<Rectangle *> rectsDIFFN;
    std::vector<Rectangle *> rectsPOLY;
    for( auto r : rects ) {
        if( r->getLayer() == "DIFFN" ) rectsDIFFN.push_back( r );
        if( r->getLayer() == "Poly" ) rectsPOLY.push_back( r );
    }
    if( !rectsDIFFN.size() or !rectsPOLY.size() ) return;
    for( size_t i = 0; i < rectsPOLY.size(); i++ ) {
        for( size_t j = 0; j < rectsDIFFN.size(); j++ ) {
            Rectangle result = *( rectsPOLY[ i ] );
            result = result & *rectsDIFFN[ j ];
            if( result.isEmpty() ) continue;
            f << "NMOS Poly RECT " << rectsPOLY[ i ]->getOrigin().x() << " " 
                << rectsPOLY[ i ]->getOrigin().y() << " " << rectsPOLY[i]->getTopRight().x() << " " << rectsPOLY[i]->getTopRight().y()<<" ";
            f << "NMOS DIFFN RECT " << rectsDIFFN[ j ]->getOrigin().x() << " "
                << rectsDIFFN[ j ]->getOrigin().y() << " " << rectsDIFFN[j]->getTopRight().x() << " " << rectsDIFFN[j]->getTopRight().y() << " ";
            std::cout << "AND: " << result.getOrigin().x() << " " << result.getOrigin().y() << " " << result.getTopRight().x() << " " << result.getTopRight().y() << std::endl;
            f << "POLYGON: " << result.getOrigin().x() << " " << result.getOrigin().y() << " " << result.getTopRight().x() << " " << result.getTopRight().y() << std::endl;
        }
    }
}

void Pmos::andOperation( std::ofstream & f ) {
    std::vector<Rectangle *> rectsDIFFN;
    std::vector<Rectangle *> rectsPOLY;
    for( auto r : rects ) {
        if( r->getLayer() == "DIFFP" ) rectsDIFFN.push_back( r );
        if( r->getLayer() == "Poly" ) rectsPOLY.push_back( r );
    }
    if( !rectsDIFFN.size() or !rectsPOLY.size() ) return;
    for( size_t i = 0; i < rectsPOLY.size(); i++ ) {
        for( size_t j = 0; j < rectsDIFFN.size(); j++ ) {
            Rectangle result = *( rectsPOLY[ i ] );
            result = result & *rectsDIFFN[ j ];
            
            if( result.isEmpty() ) continue;
            f << "PMOS Poly RECT " << rectsPOLY[ i ]->getOrigin().x() << " " 
                << rectsPOLY[ i ]->getOrigin().y() << " " << rectsPOLY[i]->getTopRight().x() << " " << rectsPOLY[i]->getTopRight().y() << " ";
            f << "PMOS DIFFP RECT " << rectsDIFFN[ j ]->getOrigin().x() << " "
                << rectsDIFFN[ j ]->getOrigin().y() << " " << rectsDIFFN[j]->getTopRight().x() << " " << rectsDIFFN[j]->getTopRight().y() << " ";
            std::cout << "AND: " << result.getOrigin().x() << " " << result.getOrigin().y() << " " << result.getTopRight().x() << " " << result.getTopRight().y() << std::endl;
            f << "POLYGON: " << result.getOrigin().x() << " " << result.getOrigin().y() << " " << result.getTopRight().x() << " " << result.getTopRight().y() << std::endl;

        }
    }
}
