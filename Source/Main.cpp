#include <iostream>
#include "Tree/Node.h"
#include "Tree/Algorithms.h"

//////////////////////////////////////////

using TreeType = uint8_t;

template<Numeric T>
void Print(const std::vector<T>& values)
{
    for (const T& value : values)
    {
        if constexpr (!std::is_same_v<T, uint8_t>) std::cout << value << " ";
        else std::cout << static_cast<unsigned>(value) << " ";
    }
    std::cout << '\n';
}

template<Numeric T>
void CreateTestTree(Node<T>** root)
{
    //      1
    //    2   3
    //   4 5   6
    // setting first layer
    root->SetLeft(new Node<T>(2));
    root->SetRight(new Node<T>(3));
    // setting second layer
    root->GetLeft()->SetLeft(new Node<T>(4));
    root->GetLeft()->SetRight(new Node<T>(5));
    root->GetRight()->SetRight(new Node<T>(6));
}

template<Numeric T>
void CreateTestBST(Node<T>** root)
{
    constexpr T node2 = 2;
    constexpr T node3 = 7;
    constexpr T node4 = 4;
    constexpr T node5 = 6;
    constexpr T node6 = 9;
    constexpr T node7 = 8;
    //    5
    //  2   7
    //   4 6  9
    //       8
    if (Algorithms::InsertNode<T>(root, node2))
    {
        if constexpr (!std::is_same_v<T, uint8_t>) std::cout << "inserted node with value " << node2 << '\n';
        else std::cout << "inserted node with value " << static_cast<unsigned>(node2) << '\n';
    }
    else
    {
        if constexpr (!std::is_same_v<T, uint8_t>) std::cout << "value " << node2 << " is already in the tree\n";
        else std::cout << "value " << static_cast<unsigned>(node2) << " is already in the tree\n";
    }

    if (Algorithms::InsertNode<T>(root, node3))
    {
        if constexpr (!std::is_same_v<T, uint8_t>) std::cout << "inserted node with value " << node3 << '\n';
        else std::cout << "inserted node with value " << static_cast<unsigned>(node3) << '\n';
    }
    else
    {
        if constexpr (!std::is_same_v<T, uint8_t>) std::cout << "value " << node3 << " is already in the tree\n";
        else std::cout << "value " << static_cast<unsigned>(node3) << " is already in the tree\n";
    }

    if (Algorithms::InsertNode<T>(root, node4))
    {
        if constexpr (!std::is_same_v<T, uint8_t>) std::cout << "inserted node with value " << node4 << '\n';
        else std::cout << "inserted node with value " << static_cast<unsigned>(node4) << '\n';
    }
    else
    {
        if constexpr (!std::is_same_v<T, uint8_t>) std::cout << "value " << node4 << " is already in the tree\n";
        else std::cout << "value " << static_cast<unsigned>(node4) << " is already in the tree\n";
    }

    if (Algorithms::InsertNode<T>(root, node5))
    {
        if constexpr (!std::is_same_v<T, uint8_t>) std::cout << "inserted node with value " << node5 << '\n';
        else std::cout << "inserted node with value " << static_cast<unsigned>(node5) << '\n';
    }
    else
    {
        if constexpr (!std::is_same_v<T, uint8_t>) std::cout << "value " << node5 << " is already in the tree\n";
        else std::cout << "value " << static_cast<unsigned>(node5) << " is already in the tree\n";
    }

    if (Algorithms::InsertNode<T>(root, node6))
    {
        if constexpr (!std::is_same_v<T, uint8_t>) std::cout << "inserted node with value " << node6 << '\n';
        else std::cout << "inserted node with value " << static_cast<unsigned>(node6) << '\n';
    }
    else
    {
        if constexpr (!std::is_same_v<T, uint8_t>) std::cout << "value " << node6 << " is already in the tree\n";
        else std::cout << "value " << static_cast<unsigned>(node6) << " is already in the tree\n";
    }

    if (Algorithms::InsertNode<T>(root, node7))
    {
        if (!std::is_same_v<T, uint8_t>) std::cout << "inserted node with value " << node7 << '\n';
        else std::cout << "inserted node with value " << static_cast<unsigned>(node7) << '\n';
    }
    else
    {
        if constexpr (!std::is_same_v<T, uint8_t>) std::cout << "value " << node7 << " is already in the tree\n";
        else std::cout << "value " << static_cast<unsigned>(node7) << " is already in the tree\n";
    }
}

template<typename T>
void DestroyTree(Node<T>** root)
{
    if (root != nullptr && *root != nullptr)
    {
        Node<T>* current = nullptr;
        std::queue<Node<T>*> order;
        order.push(*root);

        while (!order.empty())
        {
            current = order.front();
            order.pop();

            if (current->GetLeft() != nullptr)
            {
                order.push(current->GetLeft());
            }
            if (current->GetRight() != nullptr)
            {
                order.push(current->GetRight());
            }

            delete current;
        }
    }
    else
    {
        std::cout << "trying to destroy an empty tree.\n";
    }
}

template<Numeric T>
void TestDelete(Node<T>* root)
{
    constexpr TreeType deleteTarget = 5;
    if (Algorithms::DeleteNode<TreeType>(&root, deleteTarget))
    {
        if constexpr (!std::is_same_v<TreeType, uint8_t>) std::cout << "deleted node with value " << deleteTarget << '\n';
        else std::cout << "deleted node with value " << static_cast<unsigned>(deleteTarget) << '\n';
    }
    else
    {
        if constexpr (!std::is_same_v<TreeType, uint8_t>) std::cout << "trying to delete, couldn't find a node with value " << deleteTarget << '\n';
        else std::cout << "trying to delete, couldn't find a node with value " << static_cast<unsigned>(deleteTarget) << '\n';
    }
}

template<Numeric T>
void TestTraversals(Node<T>* root)
{
    std::cout << '\n';
    //std::cout << "Recursive DFS: \n";
    //Print(Algorithms::DepthFirstSearchRecursive(root));

    std::cout << "Iterative DFS: \n";
    Print(Algorithms::DepthFirstSearchIterative(root));

    //std::cout << "BFS: \n";
    //Print(Algorithms::BreadthFirstSearch(root));

    std::cout << "BFS with layers: \n";
    Algorithms::BreadthFirstSearchLayers(root);

    std::cout << "Inorder: \n";
    Print(Algorithms::InorderTraversal(root));

    std::cout << "Preorder: \n";
    Print(Algorithms::PreorderTraversal(root));

    std::cout << "Postorder: \n";
    Print(Algorithms::PostorderTraversal(root));
}

template<Numeric T>
void TestQueries(Node<T>* root)
{
    std::cout << "\n";
    constexpr TreeType target1 = 5;
    constexpr TreeType target2 = 55;

    if constexpr (std::is_same_v<TreeType, uint8_t>)
    {
        std::cout << "BST includes " << static_cast<unsigned>(target1) << " - " << (Algorithms::BSTIncludes(root, target1) ? "true" : "false") << '\n';
        std::cout << "BST includes " << static_cast<unsigned>(target2) << " - " << (Algorithms::BSTIncludes(root, target2) ? "true" : "false") << '\n';

        std::cout << "Tree sum = " << static_cast<unsigned>(Algorithms::TreeSum(root)) << '\n';

        std::cout << "Tree min value = " << static_cast<unsigned>(Algorithms::TreeMinValue(root)) << '\n';
        //std::cout << "Tree min value (recursive) = " << static_cast<unsigned>(Algorithms::TreeMinValueRecursive(root)) << '\n';

        std::cout << "Tree max path sum = " << static_cast<unsigned>(Algorithms::TreeMaxPathSum(root)) << '\n';
    }
    else
    {
        std::cout << "BST includes " << target1 << " - " << (Algorithms::BSTIncludes(root, target1) ? "true" : "false") << '\n';
        std::cout << "BST includes " << target2 << " - " << (Algorithms::BSTIncludes(root, target2) ? "true" : "false") << '\n';

        std::cout << "Tree sum = " << Algorithms::TreeSum(root) << '\n';

        std::cout << "Tree min value = " << Algorithms::TreeMinValue(root) << '\n';
        //std::cout << "Tree min value (recursive) = " << Algorithms::TreeMinValueRecursive(root) << '\n';

        std::cout << "Tree max path sum = " << Algorithms::TreeMaxPathSum(root) << '\n';
    }

    std::cout << "Tree max depth = " << Algorithms::MaxDepth(root) << '\n';

    Node<T>* inverted = Algorithms::GetInveredtTree(root);
    std::cout << "layers of inverted:\n";
    Algorithms::BreadthFirstSearchLayers(inverted);

    std::cout << "is original the same as inverted - " << (Algorithms::IsSameTree(root, inverted) ? "true" : "false") << '\n';

    std::cout << "right side view:\n";
    Print(Algorithms::GetRightSideView(root));

    DestroyTree(&inverted);
}

//////////////////////////////////////////

int main()
{
    constexpr TreeType node1 = 5;
    Node<TreeType>* root = new Node<TreeType>(node1);

    if constexpr (!std::is_same_v<TreeType, uint8_t>) std::cout << "created root with value " << node1 << '\n';
    else std::cout << "created root with value " << static_cast<unsigned>(node1) << '\n';

    //CreateTestTree(&root);
    CreateTestBST(&root);

    //TestDelete(root);
    TestTraversals(root);
    TestQueries(root);

    DestroyTree(&root);
    return 0;
}