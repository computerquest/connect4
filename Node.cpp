#include "Node.h";
using namepsace std;

Node::Node() {
    state = 0;
}

void Node::set(int pos, Node* n) {
    adjacencies[pos] = n;
    n->mutualSet(pos, this);
}

void Node::mutualSet(int pos, Node* n){
    int newPos = (pos+4)%8; //this used a mod ring to transform the adjacencies

    adjacencies[newPos] = n;
}