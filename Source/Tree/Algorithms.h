#pragma once
#include <queue>
#include <stack>
#include <vector>
#include "Node.h"

////////////////////////////////////////

namespace Algorithms
{
    template<Numeric T>
    std::vector<T> DepthFirstSearchRecursive(Node<T>* node)
    {
        std::vector<T> result;
        if (node != nullptr)
        {
            result.push_back(node->GetValue());
            std::vector<T> left = DepthFirstSearchRecursive(node->GetLeft());
            std::vector<T> right = DepthFirstSearchRecursive(node->GetRight());
            result.insert(result.end(), left.begin(), left.end());
            result.insert(result.end(), right.begin(), right.end());
        }

        return result;
    }

    template<Numeric T>
    std::vector<T> DepthFirstSearchIterative(Node<T>* root)
    {
        std::vector<T> result;
        if (root != nullptr)
        {
            Node<T>* current;
            std::stack<Node<T>*> stack;
            stack.push(root);

            while (stack.size() > 0)
            {
                current = stack.top();
                stack.pop();
                result.push_back(current->GetValue());

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

    template<Numeric T>
    std::vector<T> BreadthFirstSearch(Node<T>* root)
    {
        std::vector<T> result;
        if (root != nullptr)
        {
            Node<T>* current;
            std::queue<Node<T>*> q;
            q.push(root);

            while (q.size() > 0)
            {
                current = q.front();
                q.pop();
                result.push_back(current->GetValue());

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
    template<Numeric T>
    bool TreeIncludes(Node<T>* root, T target)
    {
        bool includes = false;

        if (root != nullptr)
        {
            Node<T>* current;
            std::queue<Node<T>*> q;
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
    template<Numeric T>
    T TreeSum(Node<T>* root)
    {
        T sum = 0;
        if (root != nullptr)
        {
            sum += root->GetValue();
            sum += TreeSum(root->GetLeft());
            sum += TreeSum(root->GetRight());
        }

        return sum;
    }

    // DFS version, can also be done using BFS
    template<Numeric T>
    T TreeMinValue(Node<T>* root)
    {
        T minValue = static_cast<T>(INT_MAX);
        if (root != nullptr)
        {
            Node<T>* current;
            std::stack<Node<T>*> stack;
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

    template<Numeric T>
    T TreeMinValueRecursive(Node<T>* node)
    {
        T minValue = static_cast<T>(INT_MAX);
        if (node != nullptr)
        {
            const T leftMin = TreeMinValueRecursive(node->GetLeft());
            const T rightMin = TreeMinValueRecursive(node->GetRight());
            minValue = std::min({ node->GetValue(), leftMin, rightMin });
        }

        return minValue;
    }

    template<Numeric T>
    T TreeMaxPathSum(Node<T>* node)
    {
        T sum = 0;
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

        return sum;
    }

    // fast recursive version
    template<Numeric T>
    uint16_t MaxDepth(Node<T>* node)
    {
        if (node != nullptr)
        {
            return 1 + std::max(MaxDepth(node->GetLeft()), MaxDepth(node->GetRight()));
        }
        else
        {
            return 0;
        }
    }
}