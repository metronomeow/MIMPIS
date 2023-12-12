#include "Graph.h"
#include "Node.h"
#include "Edge.h"
#include <iostream>
#include <fstream>
#include <iomanip>
Graph::~Graph() {
    for( auto n : nodes ) delete n;
    for( auto e : edges ) delete e;
    nodes.clear();
    edges.clear();
}
//..........................................................................................
bool Graph::addNode( char sym, double weight ) {
    if( nodesMap.find( sym ) != nodesMap.end() ) return false;
    Node * node = new Node( sym, weight );
    nodes.push_back( node );
    nodesMap[ sym ] = node;
    return true;
}
//..........................................................................................

bool Graph::addEdge( Node * fromNode, Node * toNode ) {
    if( !fromNode ) return false;
    if( !toNode ) return false;
    Edge * edge = new Edge( fromNode, toNode );
    edges.push_back( edge );
    fromNode->addToEdge( edge );
    toNode->addFromEdge( edge );
    return true;
}
//..........................................................................................

Node * Graph::getNodeByName( char name ) const {
    if( nodesMap.find( name ) == nodesMap.end() ) return nullptr;
    return nodesMap.at( name );
}
//..........................................................................................

void Graph::print( std::ostream & os ) {
   /* for( auto n : nodes ) {
        if( n->isSource() ) printNode( n, os );
    }*/

    for( auto n : nodes ) {
        std::cout << n->getName() << ":  A - " <<std::setw(4) << n->getArr() << ";   R - " << std::setw( 4 ) << n->getReq() << ";   S - " << std::setw( 4 ) << n->getSlack() << std::endl;
    }
}
//..........................................................................................

void Graph::output( std::ofstream & os ) {
    for( auto n : nodes ) {
        if( n->getSlack() < 0 ) os << n->getName() << " " << n->getSlack() << std::endl;
    }
}
//..........................................................................................

double Graph::computeCriticalPath() {
    std::vector<double> weights;
    for( auto n : nodes ) {
        if( n->isSource() ) {
            weights.push_back( computeWeight( n, 0 ) );
        }
    }
    arrived = *( std::max_element( weights.begin(), weights.end() ) );
    return arrived;
}
//..........................................................................................

void Graph::computeRequiredTime() {
    double reqCopy = required;
    for( auto n : nodes ) {
        if( n->isSink() ) {
            computeReqWeight( n, reqCopy );
        }
    }

}
//..........................................................................................

void Graph::computeSlack() {
    for( auto n : nodes ) {
        n->setSlack( n->getReq() - n->getArr() );
    }
}
//..........................................................................................

double Graph::computeWeight( Node * node, double arrived ) {
    if( !node ) return 0;
    if( node->isSource() ) arrived = 0;
    arrived += node->getWeight();
    node->setArr( std::max( arrived, node->getArr() ) );
    if( node->isSink() ) {
        return arrived;
    }
    for( auto e : node->getToEdge() ) {
        Node * next = e->getToNode();
        computeWeight( next, arrived );
    }
    return arrived;
}
//..........................................................................................

void Graph::computeReqWeight( Node * node, double required ) {
    if( !node ) return;
    //required -= node->getArr();
    node->setReq( required );
    required -= node->getWeight();
    if( node->isSource() ) return;
    for( auto e : node->getFromEdge() ) {
        Node * next = e->getFromNode();
        computeReqWeight( next, required );
    }
    return;
}
//..........................................................................................

void Graph::printNode( const Node * node, std::ostream & os ) {
    if( !node ) return;
    os << node->getName() << " ---> ";
    if( node->isSink() ) return;
    for( auto e : node->getToEdge() ) {
        const Node * next = e->getToNode();
        printNode( next, os );  
        os << std::endl;
    }
}