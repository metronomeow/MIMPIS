#pragma once
#include <vector>
#include <ostream>

class Edge;
class Node;
std::ostream & operator << ( std::ostream & os, Node node );


class Node {
public:
    Node( char sym, double weight );
    void addFromEdge( Edge * from );
    void addToEdge( Edge * to );
    bool isSource() const;
    bool isSink() const;

    char getName() const { return name; }
    const double & getWeight() const { return weight; }
    const double & getArr() const { return arrived; }
    const double & getReq() const { return required; }
    const double & getSlack() const { return slack; }

    const std::vector < Edge *> & getFromEdge() const { return fromEdge; }
    const std::vector < Edge *> & getToEdge() const { return toEdge; }

    void setArr( double d ) { arrived = d; }
    void setReq( double d ) { required = d; }
    void setSlack( double d ) { slack = d; }
private:
    char name;
    double weight;
    double arrived;
    double required;
    double slack;

    std::vector < Edge *> fromEdge;
    std::vector < Edge *> toEdge;

    friend std::ostream & operator << ( std::ostream & os, Node node );
};
