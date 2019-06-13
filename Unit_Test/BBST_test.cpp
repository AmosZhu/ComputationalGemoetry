//
// Created by amos on 6/1/19.
//

#include "../common/Template/BalancedBSTree.h"

int data[] = {11, 22, 54, 32, 89, 57, 40, 12, 101, 220, 445, 532, 980, 1, 4, 0}; //left & right single rotation
//int data[] = {11, 1, 4, 0}; //left & right single rotation

inline CG::COMPARE_RES compare_large(int _a, int _b)
{
    if (_a < _b)
        return CG::LARGER;
    else if (_a == _b)
        return CG::EQUAL;
    else
        return CG::SMALLER;
}

void test1()
{
    CG::BalancedBSTree<int> tree1;

    std::cout << "Depth " << tree1.Depth() << std::endl;

    int length = sizeof(data) / sizeof(int);
    for (int idx = 0; idx < length; idx++)
    {
        tree1.Insert(data[idx]);
    }

    std::cout << tree1 << std::endl;
    tree1.Delete(0);
    tree1.Delete(532);
    tree1.Insert(-3);
    std::cout << tree1 << std::endl;
    tree1.Insert(45);
    tree1.Insert(45);
    tree1.Insert(-3);
    std::cout << tree1 << std::endl;

    tree1.Insert(22);
    tree1.Insert(22);
    tree1.Insert(22);
    tree1.Insert(22);
    tree1.Insert(22);

    tree1.Delete(22);

    std::cout << tree1 << std::endl;

    for (int i = 0; i < length; ++i)
    {
        tree1.Delete(data[i]);
    }

    std::cout << tree1 << std::endl;
    int elem = 22;
    int pre, succ;
    tree1.Pred_and_Succ(elem, pre, succ);
    std::cout << pre << ", " << elem << ", " << succ << std::endl;
}

void test_duplicate_elem()
{
    CG::BalancedBSTree<int> tree;
    int n = 16;
    for (int i = 0; i < n; ++i)
    {
        tree.Insert(22);
    }

    tree.Insert(-3);
    tree.Insert(45);
    tree.Insert(22);

    std::cout << tree << std::endl;
    tree.Delete(22);
    std::cout << tree << std::endl;
}

int main()
{
    test1();

    return 0;
}

