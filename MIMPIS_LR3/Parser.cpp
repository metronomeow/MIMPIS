#include "Parser.h"
#include <fstream>
#include <string>
#include <iostream>
#include "Object.h"

bool Parser::readFile( std::ifstream & fs, Layout & layout ) {
    std::string buf;
    std::getline(fs, buf); // macro name
    std::getline(fs, buf); // class 
    std::getline(fs, buf); // symmetry 
    std::getline(fs, buf); // site
    while( fs >> buf ) {
        if( typeToString( buf ) != none ) layout.addObject( buf, fs );
    }
    std::cout << layout.objs.size();

    return false;
}
