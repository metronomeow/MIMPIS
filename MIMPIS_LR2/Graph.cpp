#include "Graph.h"
#include "Node.h"
#include "Edge.h"
#include <iostream>

Graph::~Graph() {
    for( auto n : nodes ) delete n;
    for( auto e : edges ) delete e;
    nodes.clear();
    edges.clear();
}

bool Graph::addNode( char sym, double weight ) {
    if( nodesMap.find( sym ) != nodesMap.end() ) return false;
    Node * node = new Node( sym, weight );
    nodes.push_back( node );
    nodesMap[ sym ] = node;
    return true;
}

bool Graph::addEdge( Node * fromNode, Node * toNode ) {
    if( !fromNode ) return false;
    if( !toNode ) return false;
    Edge * edge = new Edge( fromNode, toNode );
    edges.push_back( edge );
    fromNode->addToEdge( edge );
    toNode->addFromEdge( edge );
    return true;
}

Node * Graph::getNodeByName( char name ) const {
    if( nodesMap.find( name ) == nodesMap.end() ) return nullptr;
    return nodesMap.at( name );
}

void Graph::print( std::ostream & os ) {
    for( auto n : nodes ) {
        if( n->isSource() ) printNode( n, os );
    }
}

void Graph::printNode( const Node * node, std::ostream & os ) {
    if( !node ) return;
    if( node->getToEdge().empty() ) return;
    os << node->getName() << " ---> ";
    for( auto e : node->getToEdge() ) {
        const Node * next = e->getToNode();
        printNode( next, os );  
        os << std::endl;
    }
}