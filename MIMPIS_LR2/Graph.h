#pragma once
#include <vector>
#include <map>
#include <ostream>

class Node;
class Edge;
class Graph {
public:
    Graph() {}
    ~Graph();
    bool addNode( char sym, double weight );
    bool addEdge( Node * fromNode, Node * toNode );

    Node * getNodeByName( char name ) const;

    void print( std::ostream & os );

private:
    void printNode( const Node * node, std::ostream & os );
    std::map< char, Node * > nodesMap;
    std::vector<Node *> nodes;
    std::vector<Edge *> edges;
};