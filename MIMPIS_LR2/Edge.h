#pragma once

class Node;

class Edge {
public:
    Edge( Node * fromNode, Node * toNode ) : fromNode( fromNode ), toNode( toNode ) {}
    const Node * getFromNode() const { return fromNode; }
    const Node * getToNode() const { return toNode; }
private:
    Node *fromNode;
    Node *toNode;
};

