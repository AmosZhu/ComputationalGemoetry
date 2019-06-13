#include <iostream>
#include "common/Point.h"
#include "common/Template/Stack.h"
#include "common/Coordinates.h"
#include "common/Template/Vector.h"
#include "common/ConvexHull2D.h"
#include <ctime>
#include <cstdlib>

#include <algorithm>

void test2() {
    CG::Point2D<double> a[10];
    for (int i = 0; i < 10; ++i) {
        int x = i + 1;
        a[i].x = x;
        a[i].y = x * x - 3;
    }

    int res;
    res = CG::Euclidean2D<double>::Lowest_T_Left(a, 10);
    std::cout << "The LTL point is " << a[res] << std::endl;
}

void test3() {
    try {
        CG::Vector<CG::Point2D<double >> a;
        a.push_back(CG::Point2D<double>(1, 2));
        a.push_back(CG::Point2D<double>(1, 3));
        a.push_back(CG::Point2D<double>(4, 2));

//        a[2] = CG::Point2D<double>(5, 5);

        std::cout << a[1] << std::endl;

        std::cout << a << std::endl;
    }
    catch (const char *msg) {
        std::cout << msg << std::endl;
    }

}

void test4() {
    try {
        CG::Stack<double> a;
        a.Push(1.1);
        a.Push(2.2);
        a.Push(3);
        a.Push(4);
        a.Push(-1.1);

//        a[2] = 3.5;

        std::cout << a[10] << std::endl;

        std::cout << a << std::endl;
    }
    catch (const char *msg) {
        std::cout << msg << std::endl;
    }
}

bool cmp(double a, double b) {
    return a > b;
}

void test5() {
    CG::Vector<double> a;
    a.push_back(0);
    a.push_back(-1.2);
    a.push_back(3);
    a.push_back(4.5);
    a.push_back(-100);
    a.push_back(3.98);
    std::cout << a << std::endl;

    CG::MergeSort(a);

    std::cout << a << std::endl;
}

void ConvexHullTest() {
    int n = 1000;
    CG::Point2D<int> pts[n];
    srand(time(0));
    for (int i = 0; i < n; ++i) {
        pts[i].x = (rand() % 100000) + 1;
        pts[i].y = (rand() % 100000) + 1;
    }

//    pts[0] = CG::Point2D<int>(7, 9);
//    pts[1] = CG::Point2D<int>(-8, -1);
//    pts[2] = CG::Point2D<int>(-3, -1);
//    pts[3] = CG::Point2D<int>(1, 4);
//    pts[4] = CG::Point2D<int>(-3, 9);
//    pts[5] = CG::Point2D<int>(6, -4);
//    pts[6] = CG::Point2D<int>(7, 5);
//    pts[7] = CG::Point2D<int>(6, 6);
//    pts[8] = CG::Point2D<int>(-6, 10);
//    pts[9] = CG::Point2D<int>(0, 8);
//    for (int i = 0; i < 10; ++i)
//    {
//        std::cin >> pts[i].x >> pts[i].y;
//    }

    CG::ConvexHull2D<int> CH;
    CH.BuildFrom(pts, n);
    std::cout << CH << std::endl;
}

int main() {
    test5();
    return 0;
}

void test1() {
    CG::Point2D<double> x(1.2, 3.453);
    CG::Point2D<double> y = x + 1;
    CG::Point2D<double> z = x + y;
//    z = x = y;
    z += 1;
//    z = x = y;
    std::cout << z << std::endl;
    std::cout << z - x + y << std::endl;
    std::cout << x - 2.3 << std::endl;
    std::cout << "Hello, World!" << std::endl;

    CG::Stack<int> stack;

    for (int i = 0; i < 10; ++i) {
        stack.Push(i * i);
    }

    std::cout << stack << std::endl;

    try {
        int a = stack.Pop();
        int b = stack.Pop();
        std::cout << a << "," << b << std::endl;
        std::cout << stack << std::endl;

    }
    catch (const char *msg) {
        std::cout << msg << std::endl;
    }
}

