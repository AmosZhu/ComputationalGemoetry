//
// Created by amos on 5/26/19.
// This file aims to build a collection of computation on the coordinate system
//

#ifndef COMPUTATIONALGEMOETRY_COORDINATES_H
#define COMPUTATIONALGEMOETRY_COORDINATES_H

#include "Point.h"
#include "Template/Vector.h"

#define EUC2D_ERR(x) "Euclidiean2D error: " x

namespace CG
{
    template<typename T>
    int64 Lowest_T_Left(const Point2<T> *_elems, int64 _sz); //Lowest then leftmost points, return its index
    template<typename T>
    int64 Lowest_T_Left( Vector<Point2<T>> &_elems); //Lowest then leftmost points, return its index

    template<typename T>
    int64 Highest_T_Left(const Point2<T> *_elems, int64 _sz); //Highest then leftmost points, return its index
    template<typename T>
    int64 Lowest_T_Left( Vector<Point2<T>> &_elems);


    //----------------------------------> Implementation <-----------------------------------------------//
    template<typename T>
    int64 Lowest_T_Left(const Point2<T> *_elems, int64 _sz)
    {
        if (_elems == nullptr || _sz == 0)
        {
            throw EUC2D_ERR("(LTL test) input is empty!");
        }

        int64 idx = 0;
        for (int64 i = 1; i < _sz; ++i)
        {
            if (_elems[idx].y > _elems[i].y)
            {
                idx = i;
            }
            else if (_elems[idx].y == _elems[i].y)
            {
                if (_elems[idx].x > _elems[i].x)
                {
                    idx = i;
                }
            }
        }
        return idx;
    }

    template<typename T>
    int64 Lowest_T_Left( Vector<Point2<T>> &_elems)
    {
        if (_elems.IsEmpty())
        {
            throw EUC2D_ERR("(LTL test) input is empty!");
        }

        int64 idx = 0;
        for (int64 i = 1; i < _elems.Size(); ++i)
        {
            if (_elems[idx].y > _elems[i].y)
            {
                idx = i;
            }
            else if (_elems[idx].y == _elems[i].y)
            {
                if (_elems[idx].x > _elems[i].x)
                {
                    idx = i;
                }
            }
        }
        return idx;
    }

    template<typename T>
    int64 Highest_T_Left(const Point2<T> *_elems, int64 _sz)
    {
        if (_elems == nullptr || _sz == 0)
        {
            throw EUC2D_ERR("(HTL test) input is empty!");
        }

        int64 idx = 0;
        for (int64 i = 1; i < _sz; ++i)
        {
            if (_elems[idx].y < _elems[i].y)
            {
                idx = i;
            }
            else if (_elems[idx].y == _elems[i].y)
            {
                if (_elems[idx].x > _elems[i].x)
                {
                    idx = i;
                }
            }
        }
        return idx;
    }

    template<typename T>
    int64 Highest_T_Left( Vector<Point2<T>> &_elems)
    {
        if (_elems.IsEmpty())
        {
            throw EUC2D_ERR("(HTL test) input is empty!");
        }

        int64 idx = 0;
        for (int64 i = 1; i < _elems.Size(); ++i)
        {
            if (_elems[idx].y < _elems[i].y)
            {
                idx = i;
            }
            else if (_elems[idx].y == _elems[i].y)
            {
                if (_elems[idx].x > _elems[i].x)
                {
                    idx = i;
                }
            }
        }
        return idx;
    }
}

#endif //COMPUTATIONALGEMOETRY_COORDINATES_H
