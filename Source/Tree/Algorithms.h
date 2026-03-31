#pragma once
#include <queue>
#include <stack>
#include <vector>
#include <iostream>

#include "Node.h"

////////////////////////////////////////

constexpr uint16_t maxTreeLayerSize = 16;

namespace Algorithms
{
    template<Numeric T>
    bool InsertNode(Node<T>** root, const T value)
    {
        bool notFound = true;
        if (root != nullptr)
        {
            if (*root != nullptr)
            {
                Node<T>* current = *root;
                while (current != nullptr)
                {
                    if (value < current->GetValue())
                    {
                        if (current->GetLeft() == nullptr)
                        {
                            current->SetLeft(new Node<T>(value));
                            break;
                        }
                        current = current->GetLeft();
                    }
                    else if (value > current->GetValue())
                    {
                        if (current->GetRight() == nullptr)
                        {
                            current->SetRight(new Node<T>(value));
                            break;
                        }
                        current = current->GetRight();
                    }
                    else
                    {
                        notFound = false;
                        break;
                    }
                }
            }
            else
            {
                *root = new Node<T>(value);
            }
        }

        return notFound;
    }

    template<Numeric T>
    bool DeleteNode(Node<T>** root, const T value)
    {
        bool found = false;
        if (root != nullptr && *root != nullptr)
        {
            Node<T>* current = *root;
            Node<T>* previous = nullptr;
            while (current != nullptr)
            {
                if (value < current->GetValue())
                {
                    if (current->GetLeft() != nullptr)
                    {
                        previous = current;
                        current = current->GetLeft();
                    }
                }
                else if (value > current->GetValue())
                {
                    if (current->GetRight() != nullptr)
                    {
                        previous = current;
                        current = current->GetRight();
                    }
                }
                else
                {
                    const bool setLeft = (previous != nullptr && (value < previous->GetValue()));
                    if (current->GetLeft() != nullptr)
                    {
                        if (setLeft) previous->SetLeft(current->GetLeft());
                        else previous->SetRight(current->GetLeft());
                    }
                    else if (current->GetRight() != nullptr)
                    {
                        if (setLeft) previous->SetLeft(current->GetRight());
                        else previous->SetRight(current->GetRight());
                    }

                    found = true;
                    break;
                }
            }
        }

        return found;
    }

    template<Numeric T>
    std::vector<T> DepthFirstSearchRecursive(const Node<T>* node)
    {
        std::vector<T> result;
        if (node != nullptr)
        {
            result.emplace_back(node->GetValue());
            const std::vector<T> left = DepthFirstSearchRecursive(node->GetLeft());
            const std::vector<T> right = DepthFirstSearchRecursive(node->GetRight());
            result.insert(result.end(), left.begin(), left.end());
            result.insert(result.end(), right.begin(), right.end());
        }

        return result;
    }

    template<Numeric T>
    std::vector<T> DepthFirstSearchIterative(const Node<T>* root)
    {
        std::vector<T> result;
        if (root != nullptr)
        {
            const Node<T>* current;
            std::stack<const Node<T>*> stack;
            stack.push(root);

            while (stack.size() > 0)
            {
                current = stack.top();
                stack.pop();
                result.emplace_back(current->GetValue());

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
    std::vector<T> BreadthFirstSearch(const Node<T>* root)
    {
        std::vector<T> result;
        if (root != nullptr)
        {
            const Node<T>* current;
            std::queue<const Node<T>*> q;
            q.push(root);

            while (q.size() > 0)
            {
                current = q.front();
                q.pop();
                result.emplace_back(current->GetValue());

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

    template<Numeric T>
    std::vector<T> BreadthFirstSearchLayers(const Node<T>* root)
    {
        std::vector<T> result;
        if (root != nullptr)
        {
            bool allEmpty = true;
            std::vector<const Node<T>*> currentLayer;
            currentLayer.reserve(maxTreeLayerSize);
            currentLayer.emplace_back(root);

            std::vector<const Node<T>*> nextLayer;
            nextLayer.reserve(maxTreeLayerSize);

            while (!currentLayer.empty())
            {
                for (const Node<T>* node : currentLayer)
                {
                    if (node != nullptr)
                    {
                        allEmpty = false;
                        break;
                    }
                }

                if (allEmpty) break;

                for (const Node<T>* node : currentLayer)
                {
                    if (node == nullptr)
                    {
                        std::cout << ". ";
                        nextLayer.emplace_back(node);
                        nextLayer.emplace_back(node);
                    }
                    else
                    {
                        nextLayer.emplace_back(node->GetLeft());
                        nextLayer.emplace_back(node->GetRight());

                        if constexpr (!std::is_same_v<T, uint8_t>) std::cout << node->GetValue() << " ";
                        else std::cout << static_cast<unsigned>(node->GetValue()) << " ";
                        result.emplace_back(node->GetValue());
                    }
                }

                std::cout << '\n';
                currentLayer.swap(nextLayer);
                nextLayer.clear();
                allEmpty = true;
            }
        }

        return result;
    }

    // useful to get values in the original order
    template<Numeric T>
    std::vector<T> InorderTraversal(const Node<T>* node)
    {
        std::vector<T> result;
        if (node != nullptr)
        {
            const std::vector<T> left = InorderTraversal(node->GetLeft());
            if (!left.empty())
            {
                result.insert(result.end(), left.begin(), left.end());
            }

            result.emplace_back(node->GetValue());
            const std::vector<T> right = InorderTraversal(node->GetRight());
            if (!right.empty())
            {
                result.insert(result.end(), right.begin(), right.end());
            }
        }

        return result;
    }

    // useful to get root values first, then the leaves
    template<Numeric T>
    std::vector<T> PreorderTraversal(const Node<T>* node)
    {
        std::vector<T> result;
        if (node != nullptr)
        {
            result.emplace_back(node->GetValue());
            const std::vector<T> left = PreorderTraversal(node->GetLeft());
            if (!left.empty())
            {
                result.insert(result.end(), left.begin(), left.end());
            }

            const std::vector<T> right = PreorderTraversal(node->GetRight());
            if (!right.empty())
            {
                result.insert(result.end(), right.begin(), right.end());
            }
        }

        return result;
    }

    // useful to get leaves first, then the roots
    template<Numeric T>
    std::vector<T> PostorderTraversal(const Node<T>* node)
    {
        std::vector<T> result;
        if (node != nullptr)
        {
            const std::vector<T> left = PostorderTraversal(node->GetLeft());
            if (!left.empty())
            {
                result.insert(result.end(), left.begin(), left.end());
            }

            const std::vector<T> right = PostorderTraversal(node->GetRight());
            if (!right.empty())
            {
                result.insert(result.end(), right.begin(), right.end());
            }
            result.emplace_back(node->GetValue());
        }

        return result;
    }

    // just uses BFS and exits when the target is found
    template<Numeric T>
    bool TreeIncludes(const Node<T>* root, const T target)
    {
        bool includes = false;

        if (root != nullptr)
        {
            const Node<T>* current;
            std::queue<const Node<T>*> q;
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

    template<Numeric T>
    bool BSTIncludes(const Node<T>* root, const T target)
    {
        bool found = false;
        if (root != nullptr)
        {
            const Node<T>* current = root;
            while (current != nullptr)
            {
                if (target < current->GetValue())
                {
                    current =  current->GetLeft();
                }
                else if (target > current->GetValue())
                {
                    current = current->GetRight();
                }
                else
                {
                    found = true;
                    break;
                }
            }
        }

        return found;
    }

    // also can be done using BFS and just adding to sum
    template<Numeric T>
    T TreeSum(const Node<T>* root)
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
    T TreeMinValue(const Node<T>* root)
    {
        T minValue = 0;
        if (root != nullptr)
        {
            minValue = root->GetValue();
            const Node<T>* current;
            std::stack<const Node<T>*> stack;
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
    T TreeMinValueRecursive(const Node<T>* node)
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
    T TreeMaxPathSum(const Node<T>* node)
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
    uint32_t MaxDepth(const Node<T>* node)
    {
        if (node != nullptr)
        {
            return 1 + std::max(MaxDepth(node->GetLeft()), MaxDepth(node->GetRight()));
        }
        else return 0;
    }

    template<Numeric T>
    bool IsSameTree(const Node<T>* tree1, const Node<T>* tree2)
    {
        
    }

    template<Numeric T>
    Node<T>* InvertTree(const Node<T>* root)
    {
        
    }
}