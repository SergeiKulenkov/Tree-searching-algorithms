#include <iostream>
#include "Tree/Node.h"
#include "Tree/Algorithms.h"

//////////////////////////////////////////

template<Numeric T>
void Print(const std::vector<Node<T>*>& nodes)
{
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
    Node<int>* root = new Node<int>(1);
    // setting first layer
    root->SetLeft(new Node<int>(2));
    root->SetRight(new Node<int>(3));
    // setting second layer
    root->GetLeft()->SetLeft(new Node<int>(4));
    root->GetLeft()->SetRight(new Node<int>(5));
    root->GetRight()->SetRight(new Node<int>(6));

    std::cout << "Recursive DFS: \n";
    Print(Algorithms::DepthFirstSearchRecursive(root));

    std::cout << "Iterative DFS: \n";
    Print(Algorithms::DepthFirstSearchIterative(root));

    std::cout << "BFS: \n";
    Print(Algorithms::BreadthFirstSearch(root));

    // test values
    const int target1 = 5;
    const int target2 = 55;
    std::cout << "Tree includes " << target1 << " - " << (Algorithms::TreeIncludes(root, target1) ? "true" : "false") << '\n';
    std::cout << "Tree includes " << target2 << " - " << (Algorithms::TreeIncludes(root, target2) ? "true" : "false") << '\n';

    std::cout << "Tree sum = " << Algorithms::TreeSum(root) << '\n';

    std::cout << "Tree min value = " << Algorithms::TreeMinValue(root) << '\n';
    std::cout << "Tree min value (recursive) = " << Algorithms::TreeMinValueRecursive(root) << '\n';

    std::cout << "Tree max path sum = " << Algorithms::TreeMaxPathSum(root) << '\n';

    return 0;
}