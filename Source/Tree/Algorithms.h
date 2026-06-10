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
            // try to find the node with the target value
            while (current != nullptr)
            {
                if (value < current->GetValue())
                {
                    previous = current;
                    current = current->GetLeft();
                }
                else if (value > current->GetValue())
                {
                    previous = current;
                    current = current->GetRight();
                }
                else
                {
                    found = true;
                    break;
                }
            }

            // case 1 - deleting a leaf node
            // case 2 - deleting a node with only one child node
            // case 3 - deleting a node with two child nodes
            if (found)
            {
                Node<T>* newCurrent = nullptr;
                // current (node with the target value) has zero or only one child node
                if (current->GetLeft() == nullptr || current->GetRight() == nullptr)
                {
                    if (current->GetLeft() == nullptr)
                    {
                        newCurrent = current->GetRight();
                    }
                    else newCurrent = current->GetLeft();

                    if (previous == nullptr)
                    {
                        // trying to delete the root
                        *root = newCurrent;
                    }
                    else
                    {
                        if (value < previous->GetValue())
                        {
                            previous->SetLeft(newCurrent);
                        }
                        else previous->SetRight(newCurrent);

                        delete current;
                    }
                }
                // two child nodes
                else
                {
                    // find the inorder successor - smallest value in the right subtree
                    previous = nullptr;
                    newCurrent = current->GetRight();
                    while (newCurrent->GetLeft() != nullptr)
                    {
                        previous = newCurrent;
                        newCurrent = newCurrent->GetLeft();
                    }

                    if (previous != nullptr)
                    {
                        previous->SetLeft(newCurrent->GetRight());
                    }
                    else current->SetRight(newCurrent->GetRight());

                    current->SetValue(newCurrent->GetValue());
                    delete newCurrent;
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
            std::queue<const Node<T>*> order;
            order.push(root);

            while (!order.empty())
            {
                current = order.front();
                order.pop();
                result.emplace_back(current->GetValue());

                if (current->GetLeft() != nullptr)
                {
                    order.push(current->GetLeft());
                }
                if (current->GetRight() != nullptr)
                {
                    order.push(current->GetRight());
                }
            }
        }

        return result;
    }

    // returns the values in the BFS order but also prints them in layers
    template<Numeric T>
    std::vector<T> BreadthFirstSearchLayers(const Node<T>* root)
    {
        std::vector<T> result;
        if (root != nullptr)
        {
            bool allNull = true;
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
                        allNull = false;
                        break;
                    }
                }

                if (allNull) break;

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
                allNull = true;
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

    // using BST concept where left < root, right > root
    // so the search should be faster than the above BFS version
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
        bool isSame = false;
        if (tree1 != nullptr && tree2 != nullptr)
        {
            if (tree1->GetValue() == tree2->GetValue())
            {
                isSame = true && IsSameTree(tree1->GetRight(), tree2->GetRight()) && IsSameTree(tree1->GetLeft(), tree2->GetLeft());
            }
        }
        else if (tree1 == nullptr && tree2 == nullptr)
        {
            isSame = true;
        }

        return isSame;
    }

    template<Numeric T>
    Node<T>* GetInveredtTree(const Node<T>* root)
    {
        Node<T>* result = nullptr;
        if (root != nullptr)
        {
            // clone the original tree
            result = new Node<T>(root);
            Node<T>* current = nullptr;
            Node<T>* previous = nullptr;
            std::queue<Node<T>*> order;
            order.push(result);

            while (!order.empty())
            {
                for (size_t i = order.size(); i > 0; i--)
                {
                    current = order.front();
                    if (current != nullptr)
                    {
                        previous = current->GetLeft();
                        current->SetLeft(current->GetRight());
                        current->SetRight(previous);

                        order.push(current->GetLeft());
                        order.push(current->GetRight());
                    }

                    order.pop();
                }
            }
        }

        return result;
    }

    template<Numeric T>
    std::vector<T> GetRightSideView(const Node<T>* root)
    {
        std::vector<T> result;
        if (root != nullptr)
        {
            const Node<T>* current = nullptr;
            const Node<T>* right = nullptr;
            std::queue<const Node<T>*> order;
            order.push(root);

            while (!order.empty())
            {
                for (size_t i = order.size(); i > 0; i--)
                {
                    current = order.front();
                    order.pop();

                    if (current != nullptr)
                    {
                        // get the right most node of each layer
                        right = current;
                        order.push(current->GetLeft());
                        order.push(current->GetRight());
                    }
                }

                if (right != nullptr)
                {
                    result.emplace_back(right->GetValue());
                }
                right = nullptr;
            }
        }

        return result;
    }

    template<Numeric T>
    bool ValidateBSTHelper(const Node<T>* node, const T low, const T high)
    {
        bool valid = true;
        if (node != nullptr)
        {
            // each node in each subtree must be in a specific range
            // for the left subtree it's (type_min, root), for the right it's (root, type_max)
            if ((node->GetValue() > low) &&
                (node->GetValue() < high))
            {
                valid = ValidateBSTHelper(node->GetLeft(), low, node->GetValue()) &&
                        ValidateBSTHelper(node->GetRight(), node->GetValue(), high);
            }
            else valid = false;
        }

        return valid;
    }

    template<Numeric T>
    bool ValidateBST(const Node<T>* root)
    {
        return ValidateBSTHelper(root, std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
    }

    template<Numeric T>
    Node<T>* ConstructHelper(const std::vector<T>& inorder, const std::vector<T>& preorder, const uint32_t leftLimit, uint32_t& inorderIndex, uint32_t& preorderIndex)
    {
        Node<T>* result = nullptr;
        if ((preorderIndex < preorder.size()) &&
            (inorderIndex < inorder.size()))
        {
            if (inorder[inorderIndex] != leftLimit)
            {
                result = new Node<T>(preorder[preorderIndex++]);
                // use current node value because left subtree contains values less than this one
                result->SetLeft(ConstructHelper(inorder, preorder, result->GetValue(), inorderIndex, preorderIndex));
                result->SetRight(ConstructHelper(inorder, preorder, leftLimit, inorderIndex, preorderIndex));
            }
            else if (inorder[inorderIndex] == leftLimit)
            {
                // left subtree is done
                inorderIndex++;
            }
        }

        return result;
    }

    template<Numeric T>
    Node<T>* Construct(const std::vector<T>& inorder, const std::vector<T>& preorder)
    {
        Node<T>* result = nullptr;
        if (!preorder.empty() && !inorder.empty())
        {
            uint32_t preorderIndex = 0;
            uint32_t inorderIndex = 0;

            result = ConstructHelper(inorder, preorder, UINT32_MAX, inorderIndex, preorderIndex);
        }

        return result;
    }

    // Leetcode house robber 3

}