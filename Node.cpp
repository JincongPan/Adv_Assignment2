
#include "Node.h"

Node::Node(Tile* t, Node* n)
{
   tile = t;
   next = n;
}

Node::Node(Node& other)
{
   next = other.next;
   tile->colour = other.tile->colour;
   tile->shape = other.tile->shape;
}
