#pragma once
#include <string>
#include <vector>

class Parser {
public:
    bool getSymbolArray( std::string &, std::vector<char> & );
private:
    bool isAllowedSymbol( char sym );

};

