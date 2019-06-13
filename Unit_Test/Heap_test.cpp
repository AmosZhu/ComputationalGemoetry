//
// Created by amos on 6/12/19.
//

#include "common/Template/BinaryHeap.h"

int data[] = {13, 55, 43, 4, 123, 98, 67, 444, 777, 223, -1, 0, -3, -4};

int main()
{
    CG::BinaryHeap<int> heap(1);

    int n = sizeof(data) / sizeof(int);
    CG::Vector<int> vec(n);

    for (int i = 0; i < n; ++i)
    {
        heap.Insert(data[i]);
    }

    for (int i = 0; i < n; ++i)
    {
        vec[i] = heap.DeleteMin();
    }

    std::cout << vec << std::endl;

}
