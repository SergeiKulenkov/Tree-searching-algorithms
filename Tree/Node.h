#pragma once

class Node
{
public:
    Node();

    Node(int newValue);

    Node* GetLeft();
    Node* GetRight();

    void SetLeft(Node* newLeft);
    void SetRight(Node* newRight);

    int GetValue();
    void SetValue(int newValue);

private:
    int value;
    Node* left;
    Node* right;
};

