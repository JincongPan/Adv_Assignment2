
#include "Node.h"

Node::Node(Tile* t, Node* n)
{
   // struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
   // tile->colour = tile->colour;
   // tile->shape = tile->shape;
   tile = t;
   next = n;
   // TODO
}

Node::Node(Node& other)
{
   // struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
   next = other.next;
   tile->colour = other.tile->colour;
   tile->shape = other.tile->shape;
   // TODO
}
