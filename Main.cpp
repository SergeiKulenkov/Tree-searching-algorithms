#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include "Tree/Node.h"

////////////////////////////////////////

std::vector<Node*> DepthFirstSearchRecursive(Node* node)
{
    std::vector<Node*> result;
    if (node != nullptr)
    {
        result.push_back(node);
        std::vector<Node*> left = DepthFirstSearchRecursive(node->GetLeft());
        std::vector<Node*> right = DepthFirstSearchRecursive(node->GetRight());
        result.insert(result.end(), left.begin(), left.end());
        result.insert(result.end(), right.begin(), right.end());
    }

    return result;
}

std::vector<Node*> DepthFirstSearchIterative(Node* root)
{
    std::vector<Node*> result;
    if (root != nullptr)
    {
        std::cout << "Iterative DFS: \n";

        Node* current;
        std::stack<Node*> stack;
        stack.push(root);

        while (stack.size() > 0)
        {
            current = stack.top();
            stack.pop();
            result.push_back(current);

            if (current->GetRight() != nullptr)
            {
                stack.push(current->GetRight());
            }
            if (current->GetLeft() != nullptr)
            {
                stack.push(current->GetLeft());
            }
        }
    }

    return result;
}

std::vector<Node*> BreadthFirstSearch(Node* root)
{
    std::vector<Node*> result;
    if (root != nullptr)
    {
        std::cout << "BFS: \n";

        Node* current;
        std::queue<Node*> q;
        q.push(root);

        while (q.size() > 0)
        {
            current = q.front();
            q.pop();
            result.push_back(current);

            if (current->GetLeft() != nullptr)
            {
                q.push(current->GetLeft());
            }
            if (current->GetRight() != nullptr)
            {
                q.push(current->GetRight());
            }
        }
    }

    return result;
}

// just uses BFS and exits when the target is found
bool TreeIncludes(Node* root, int target)
{
    bool includes = false;

    if (root != nullptr)
    {
        Node* current;
        std::queue<Node*> q;
        q.push(root);

        while (q.size() > 0)
        {
            current = q.front();
            q.pop();
            if (current->GetValue() == target)
            {
                includes = true;
                break;
            }

            if (current->GetLeft() != nullptr)
            {
                q.push(current->GetLeft());
            }
            if (current->GetRight() != nullptr)
            {
                q.push(current->GetRight());
            }
        }
    }

    return includes;
}

// also can be done using BFS and just adding to sum
int TreeSum(Node* root)
{
    int sum = 0;
    if (root != nullptr)
    {
        sum += root->GetValue();
        sum += TreeSum(root->GetLeft());
        sum += TreeSum(root->GetRight());
    }

    return sum;
}

// DFS version, can also be done using BFS
int TreeMinValue(Node* root)
{
    int minValue = INT_MAX;
    if (root != nullptr)
    {
        Node* current;
        std::stack<Node*> stack;
        stack.push(root);

        while (stack.size() > 0)
        {
            current = stack.top();
            stack.pop();
            if (current->GetValue() < minValue)
            {
                minValue = current->GetValue();
            }

            if (current->GetRight() != nullptr)
            {
                stack.push(current->GetRight());
            }
            if (current->GetLeft() != nullptr)
            {
                stack.push(current->GetLeft());
            }
        }
    }

    return minValue;
}

int TreeMinValueRecursive(Node* node)
{
    int minValue = INT_MAX;
    if (node != nullptr)
    {
        const int leftMin = TreeMinValueRecursive(node->GetLeft());
        const int rightMin = TreeMinValueRecursive(node->GetRight());
        minValue = std::min({ node->GetValue(), leftMin, rightMin });
    }

    return minValue;
}

int TreeMaxPathSum(Node* node)
{
    int sum = 0;
    if (node != nullptr)
    {
        if ((node->GetLeft() == nullptr) &&
            (node->GetRight() == nullptr))
        {
            sum += node->GetValue();
        }
        else
        {
            sum += node->GetValue() + std::max(TreeMaxPathSum(node->GetLeft()), TreeMaxPathSum(node->GetRight()));
        }
    }
    else
    {
        sum = INT_MAX * (-1);
    }

    return sum;
}

//////////////////////////////////////////

void Print(const std::vector<Node*>& nodes)
{
    std::cout << "Printing: ";
    for (int i = 0; i < nodes.size(); i++)
    {
        std::cout << nodes[i]->GetValue() << " ";
    }
    std::cout << '\n';
}

int main()
{
    //      1
    //    2   3
    //   4 5   6
    Node* root = new Node(1);
    // setting first layer
    root->SetLeft(new Node(2));
    root->SetRight(new Node(3));
    // setting second layer
    root->GetLeft()->SetLeft(new Node(4));
    root->GetLeft()->SetRight(new Node(5));
    root->GetRight()->SetRight(new Node(6));

    std::cout << "Recursive DFS: \n";
    Print(DepthFirstSearchRecursive(root));
    Print(DepthFirstSearchIterative(root));

    Print(BreadthFirstSearch(root));

    // values for testing are set here
    const int target = 5;
    const int target2 = 55;
    std::cout << "Tree includes (true or false) " << target << " - " << TreeIncludes(root, target) << '\n';
    std::cout << "Tree includes (true or false) " << target2 << " - " << TreeIncludes(root, target2) << '\n';

    std::cout << "Tree sum = " << TreeSum(root) << '\n';

    std::cout << "Tree min value = " << TreeMinValue(root) << '\n';
    std::cout << "Tree min value (recursive) = " << TreeMinValueRecursive(root) << '\n';

    std::cout << "Tree max path sum = " << TreeMaxPathSum(root) << '\n';

    return 0;
}