#pragma once
class Node {
public:
    Node( char _sym, Node * _left = 0, Node * _right = 0 ) : sym( _sym ), left( _left ), right( _right ) {}

    Node *addLeftNode( char sym );
    Node *addRightNode( char sym );

    char getSym() { return sym; }
    Node *getLeft()  { return left; }
    Node *getRight() { return right; }
private:
    Node *left;
    Node *right;
    char sym;
};

