#pragma once
#include "Node.h"
#include <vector>
#include <ostream>

#define EXIT( message ) { std::cout << "\033[1;31mERROR: \033[0m" << message << std::endl; exit(EXIT_FAILURE); }
#define WARNING( message ) { std::cout << "\033[1;33mWARNING: \033[0m" << message << std::endl; }
#define INFO( message ) { std::cout << "\033[1;32mINFO: \033[0m" << message << std::endl; }

#define INFO( printFunction ) { std::cout  << "\033[1;32m"; printFunction( std::cout  ); std::cout  << "\033[0m" << std::endl; }
#define ERROR( message ) { std::cout  << "\033[1;31mERROR: \033[0m" << message; } //doesn't need endl, cause used inside INFO

class Graph {
public:
    Graph( std::vector<char> );
    ~Graph();

    void print( std::ostream & os );
    void saveToOutFile( std::string fName );

private:
    std::vector< Node *> nodes;
    Node *root;

    void printNode( Node *node, std::ostream &os );
    int getPriority( char sym );
    void makeGraph( std::vector<char>::iterator _begin, std::vector<char>::iterator _end, Node *_root, bool left );
};

