#include "Node.h"

Node::Node( char sym, double weight ) : name(sym), weight(weight), arrived(0), required(0), slack(0) {}

void Node::addFromEdge( Edge * from ) {
    if(from) fromEdge.push_back( from );
}

void Node::addToEdge( Edge * to ) {
    if(to) toEdge.push_back( to );
}

bool Node::isSource() const {
    return fromEdge.empty();
}

bool Node::isSink() const {
    return toEdge.empty();
}

std::ostream & operator<<( std::ostream & os, Node node ) {
    os << node.name << "(" <<node.weight << ") ";
    return os;
}
