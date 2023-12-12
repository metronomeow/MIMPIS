#include "Parser.h"
#include <iostream>

bool Parser::getSymbolArray( std::string & str, std::vector<char> & arr ) {
    for( auto sym : str ) {
        if( sym == ' ' ) continue;
        if( !isAllowedSymbol( sym ) ) return false;
        arr.push_back( sym );
    }
    return true;
}

bool Parser::isAllowedSymbol( char sym ) {
    switch( sym ) {
        case '0':
        case '1':
        case '!':
        case '*':
        case '+':
            return true;
        default: break;
    }
    if( sym > 64 and sym < 91  ) return true;
    if( sym > 96 and sym < 123 ) return true;
    return false;
}
