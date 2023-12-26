#pragma once
#include<vector>
#include <string>
#include "Rectangle.h"

enum ObjType {
    none = -1,
    pin,
    nmos,
    pmos,
    contact,
    path
};

inline ObjType typeToString( std::string type ) {
    if( type == "PATH"    ) return path;
    if( type == "CONTACT" ) return contact;
    if( type == "NMOS"    ) return nmos;
    if( type == "PMOS"    ) return pmos;
    if( type == "PIN"     ) return pin;
    return none;

}

class Object {
    ObjType  type;
public:
    std::string name;
    std::vector<Rectangle *> rects;
    Object( ObjType t ) : type( t ), name( "" ) {};
    virtual ObjType getType() = 0;
    virtual void readObj( std::ifstream & fs );
    virtual void addRect( std::string layer, int leftX, int leftY, int rightX, int rightY );
    virtual void andOperation() {};
    ~Object();
};



class Pin : public Object {
public:
    Pin( ObjType t ) : Object( t ) {};
    ObjType getType() override { return pin; }
};

class Nmos : public Object {
public :
    Nmos( ObjType t ) : Object( t ) {};
    ObjType getType() override { return nmos; }
    virtual void andOperation() override;

};

class Pmos : public Object {
public :
    Pmos( ObjType t ) : Object( t ) {};
    ObjType getType() override { return pmos; }
    virtual void andOperation() override;

};

class Contact : public Object {
public :
    Contact( ObjType t ) : Object( t ) {};
    ObjType getType() override { return contact; }

};

class Path : public Object {
public :
    Path( ObjType t ) : Object( t ) {};
    ObjType getType() override { return path; }

};