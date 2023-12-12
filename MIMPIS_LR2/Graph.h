#pragma once
#include <vector>
#include <map>
#include <ostream>

class Node;
class Edge;
class Graph {
public:
    Graph() : required(0), arrived(0) {}
    ~Graph();
    bool addNode( char sym, double weight );
    bool addEdge( Node * fromNode, Node * toNode );

    Node * getNodeByName( char name ) const;

    void print( std::ostream & os );
    void output( std::ofstream & os );
    double computeCriticalPath();
    void computeRequiredTime();
    void computeSlack();
    void setRequire( double r ) { required = r; }
private:
    double computeWeight( Node * n, double arrived );
    void computeReqWeight( Node * n, double required );
    void printNode( const Node * node, std::ostream & os );
    std::map< char, Node * > nodesMap;
    std::vector<Node *> nodes;
    std::vector<Edge *> edges;
    double required;
    double arrived;
};