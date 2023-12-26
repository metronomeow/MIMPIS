#pragma once
#include"Layout.h"

class Parser {
public:
    bool readFile( std::ifstream & fs, Layout & layout );
};

