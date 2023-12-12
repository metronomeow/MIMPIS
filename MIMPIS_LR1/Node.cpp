#include "Node.h"

Node *Node::addLeftNode( char sym ) {
    Node *node = new Node( sym );
    left = node;
    return node;
}

Node *Node::addRightNode( char sym ) {
    Node *node = new Node( sym );
    right = node;
    return node;
}
