#include <iostream>
#include "Tree/Node.h"
#include "Tree/Algorithms.h"

//////////////////////////////////////////

template<Numeric T>
void Print(const std::vector<T>& values)
{
    for (const T value : values)
    {
        std::cout << static_cast<unsigned>(value) << " ";
    }
    std::cout << '\n';
}

int main()
{
    //      1
    //    2   3
    //   4 5   6
    Node<uint8_t>* root = new Node<uint8_t>(1);
    // setting first layer
    root->SetLeft(new Node<uint8_t>(2));
    root->SetRight(new Node<uint8_t>(3));
    // setting second layer
    root->GetLeft()->SetLeft(new Node<uint8_t>(4));
    root->GetLeft()->SetRight(new Node<uint8_t>(5));
    root->GetRight()->SetRight(new Node<uint8_t>(6));

    std::cout << "Recursive DFS: \n";
    Print(Algorithms::DepthFirstSearchRecursive(root));

    std::cout << "Iterative DFS: \n";
    Print(Algorithms::DepthFirstSearchIterative(root));

    std::cout << "BFS: \n";
    Print(Algorithms::BreadthFirstSearch(root));

    // test values
    const uint8_t target1 = 5;
    const uint8_t target2 = 55;
    std::cout << "Tree includes " << target1 << " - " << (Algorithms::TreeIncludes(root, target1) ? "true" : "false") << '\n';
    std::cout << "Tree includes " << target2 << " - " << (Algorithms::TreeIncludes(root, target2) ? "true" : "false") << '\n';

    std::cout << "Tree sum = " << static_cast<unsigned>(Algorithms::TreeSum(root)) << '\n';

    std::cout << "Tree min value = " << static_cast<unsigned>(Algorithms::TreeMinValue(root)) << '\n';
    std::cout << "Tree min value (recursive) = " << static_cast<unsigned>(Algorithms::TreeMinValueRecursive(root)) << '\n';

    std::cout << "Tree max path sum = " << static_cast<unsigned>(Algorithms::TreeMaxPathSum(root)) << '\n';
    std::cout << "Tree max depth = " << static_cast<unsigned>(Algorithms::MaxDepth(root)) << '\n';

    return 0;
}