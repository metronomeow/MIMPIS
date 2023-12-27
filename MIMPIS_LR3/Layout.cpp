#include "Layout.h"
#include "Object.h"
#include "Polygon.h"
#include <iostream>
#include <fstream>

void Layout::addObject( std::string type, std::ifstream & fs ) {
    ObjType tp = typeToString( type );
    Object * newObj = nullptr;
    switch( tp ) {
    case pin:     newObj = new  Pin( tp ); break;
    case contact: newObj = new  Contact( tp ); break;
    case pmos:    newObj = new  Pmos( tp ); break;
    case nmos:    newObj = new  Nmos( tp ); break;
    case path:    newObj = new  Path( tp ); break;
    case none:
    default:
        return;
    }
    newObj->readObj( fs );
    objs.push_back( newObj );
}

void Layout::andOperation() {
//operation  and: between layers DIFFN & POLY, DIFFP & POLY - in PMOS and NMOS
    std::ofstream f( "OUTPUT.TXT" );
    f << "AND operation:" << std::endl;
    for( auto ob : objs ) {
        if( ob->getType() == pmos ) {
            ob->andOperation(f);
        }
        if( ob->getType() == nmos ) {
            ob->andOperation(f);
        }
    }
    f.close();
}


void Layout::orOperation() {
    std::ofstream f( "OUTPUT.TXT", std::ios::app );
    Polygon res2;
    f << "OR Operation: " << std::endl;
    for( auto ob : objs ) {
        if( ob->getType() == pin and ob->name == "vdd" ) {
            Polygon res;
            if( !ob->rects.size() ) continue;
            for( auto r : ob->rects ) {
                if( r->getLayer() == "NWELL" ) {
                    res = *( r->castToPolygon() );
                }
            }
            f << "PIN vdd NWELL RECT ";
            for( auto t : res.points ) f << t.x() << " " << t.y() << " ";
            for( auto r : ob->rects ) {
            f << "PIN vdd " << r->getLayer() << " RECT " << r->getOrigin().x() << " " <<
                r->getOrigin().y() << " " << r->getTopRight().x() << " " << r->getTopRight().y() << " ";
                res = res + *r;
            }
            std::cout << "OR: ";
            f << "POLYGON: ";
            for( auto r : res.points ) {
                std::cout << r.x() << " " << r.y() << " ";
                f << r.x() << " " << r.y() << " ";
            }
            std::cout << std::endl;
            f << std::endl;
        }
    }
    for( auto ob : objs ) {
        if( ob->getType() == path ) {
            for( auto r : ob->rects ) {
                if( r->getLayer() == "M2M" ) {
                    res2 = *( r->castToPolygon() );
                    f << "PATH M2M RECT " ;
                    for( auto t : res2.points ) f << t.x() << " " << t.y() << " ";
                }
            }
        }
    }
    for( auto ob : objs ) {
        if( ob->getType() == contact ) {
            for( auto r : ob->rects ) {
                if( r->getLayer() == "M12M" ) {
                    f << "CONTACT M12M RECT ";
                    for( auto t : res2.points ) f << t.x() << " " << t.y() << " ";
                    res2 = res2 + *r;
                }
            }
        }
    }
    std::cout << "OR: ";
    f << "POLYGON: ";
    for( auto r : res2.points ) {
        std::cout << r.x() << " " << r.y() << " ";
        f << r.x() << " " << r.y() << " ";
    }
    std::cout << std::endl;
    f << std::endl;
    f.close();
}

Layout::~Layout() {
    for( auto o : objs ) delete o;
    objs.clear();
}
