#include "Layout.h"
#include "Object.h"
#include "Polygon.h"
#include <iostream>

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
    for( auto ob : objs ) {
        if( ob->getType() == pmos or ob->getType() == nmos ) {
            ob->andOperation();
        }
    }
}

void Layout::orOperation() {
    Polygon res2;
    for( auto ob : objs ) {
        if( ob->getType() == pin and ob->name == "vdd" ) {
            Polygon res;
            if( !ob->rects.size() ) continue;
            for( auto r : ob->rects ) {
                if( r->getLayer() == "NWELL" ) res = *( r->castToPolygon() );
            }
            for( auto r : ob->rects ) {
                res = res + *r;
            }
            std::cout << "OR: ";
            for( auto r : res.points ) {
                std::cout << r.x() << " " << r.y() << " ";
            }
            std::cout << std::endl;
        }
    }
    for( auto ob : objs ) {
        if( ob->getType() == path ) {
            for( auto r : ob->rects ) {
                if( r->getLayer() == "M2M" ) {
                    res2 = *( r->castToPolygon() );
                }
            }
        }
    }
    for( auto ob : objs ) {
        if( ob->getType() == contact ) {
            for( auto r : ob->rects ) {
                if( r->getLayer() == "M12M" ) {
                    res2 = res2 + *r;
                }
            }
        }
    }
    std::cout << "OR: ";
    for( auto r : res2.points ) {
        std::cout << r.x() << " " << r.y() << " ";
    }
    std::cout << std::endl;
}

Layout::~Layout() {
    for( auto o : objs ) delete o;
    objs.clear();
}
