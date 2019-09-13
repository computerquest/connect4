#include "Node.h"
#include <iostream>
using namespace std;

Node::Node()
{
    state = 0;

    for (int i = 0; i < 8; i++)
    {
        adjacent[i] = nullptr;
    }
}

void Node::set(int pos, Node &n)
{
    adjacent[pos] = &n;
    n.mutualSet(pos, *this);
}

void Node::mutualSet(int pos, Node &n)
{
    int newPos = (pos + 4) % 8; //this used a mod ring to transform the adjacencies

    adjacent[newPos] = &n;
}

void Node::setState(int i)
{
    state = i;
}

int Node::getState()
{
    return state;
}

void Node::print()
{
    if (state == 0)
    {
        cout << " * |";
    }
    else if (state == 1)
    {
        cout << " 1 |";
    }
    else if (state == 2)
    {
        cout << " 2 |";
    }

    if (adjacent[2])
    {
        adjacent[2]->print();
    }
}

Node *Node::goDown()
{
    return adjacent[4];
}

Node *Node::goUp()
{
    return adjacent[0];
}

int Node::checkWin(int count, int pos, int player)
{
    if (state != player)
    {
        return count;
    }

    count++;

    if (adjacent[pos] && (count = adjacent[pos]->checkWin(count, pos, player)) >= 4)
    {
        return count;
    }

    return count;
}

Node::~Node()
{
    if (adjacent[2])
    {
        delete adjacent[2];
    }
}