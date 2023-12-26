#pragma once
#include<vector>
#include<fstream>
class Object;

class Layout {
public:
    std::vector<Object *> objs;
    void addObject( std::string type, std::ifstream & fs );
    void andOperation( );
    void orOperation( );
    ~Layout();
};

