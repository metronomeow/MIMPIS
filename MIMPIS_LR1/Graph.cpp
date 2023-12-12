#include "Graph.h"
#include <iostream>
#include <fstream>

Graph::Graph( std::vector<char> array ) {
    root = new Node( ' ');
    makeGraph( array.begin(), array.end(), root, true );
}

Graph::~Graph() {
    for( auto n : nodes ) delete n;
    nodes.clear();
}

void Graph::print( std::ostream &os ) {
    if( nodes.empty() ) ERROR( "This line was incorrect" );
    printNode( root, os );
}

void Graph::saveToOutFile( std::string fName ) {
    std::ofstream fs( fName, std::ios::app );
    if( !fs.is_open() ) {
        EXIT( "Couldn't open file '"  + fName + "' to write" );
    }
    if( nodes.empty() ) fs << "ERROR: This line was incorrect";
    printNode( root, fs );
    fs << std::endl;
    fs.close();
}

void Graph::printNode( Node *node, std::ostream &os ) {
    if( !node ) return;
    os << node->getSym();
    printNode( node->getLeft(), os );
    printNode( node->getRight(), os );
}

/*
-1 - list node,lowest priority
 0 - !
 1 - *
 2 - +, highest priority
*/
int Graph::getPriority( char sym ) {
    if( sym > 64 and sym < 91 ) return -1;
    if( sym > 96 and sym < 123 ) return -1;
    switch( sym ) {
        case '0': return -1;
        case '1': return -1;
        case '!': return 0;
        case '*': return 1;
        case '+': return 2;
        default: break;
    }
    return -1;
}

void Graph::makeGraph( std::vector<char>::iterator _begin, std::vector<char>::iterator _end, Node *_root, bool left ) {
    int priority = -2;
    std::vector<char>::iterator isNeededSym = _end;
    for( std::vector<char>::iterator sym = _begin; sym != _end; sym++ ) {
        if( getPriority( *sym ) > priority ) {
            priority = getPriority( *sym );
            isNeededSym = sym;
        }
    }

    if( priority == -2 ) return;

    Node *newNode = 0;

    if( left ) {
        newNode = _root->addLeftNode( *isNeededSym );
        nodes.push_back( newNode );
    }
    else {
        newNode = _root->addRightNode( *isNeededSym );
        nodes.push_back( newNode );
    }

    //left group
    makeGraph( _begin, isNeededSym, newNode, true );
    //right group
    makeGraph( isNeededSym+1, _end, newNode, false );
}
