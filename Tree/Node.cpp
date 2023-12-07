#include "Node.h"

Node::Node() : value(0), left(nullptr), right(nullptr)
{
}

Node::Node(int newValue) : value(newValue)
{
    left = nullptr;
    right = nullptr;
}

Node* Node::GetLeft()
{
    return left;
}

Node* Node::GetRight()
{
    return right;
}

void Node::SetLeft(Node* newLeft)
{
    left = newLeft;
}

void Node::SetRight(Node* newRight)
{
    right = newRight;
}

int Node::GetValue()
{
    return value;
}

void Node::SetValue(int newValue)
{
    value = newValue;
}
