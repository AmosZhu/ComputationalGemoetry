//
// Created by root on 5/30/19.
//

#ifndef COMPUTATIONALGEMOETRY_ALGORITHM_H
#define COMPUTATIONALGEMOETRY_ALGORITHM_H

#include "ContainerBase.h"

namespace CG
{

#define ALGORITHM_ERR(x) "Algorithm error: " x

    template<typename T>
    bool al_compare_less(T _a, T _b)
    {
        return _a < _b;
    }

    /*******************************************************************************************
     *                                   Utility functions
     *******************************************************************************************/
    template<typename T, typename cmp_f= bool (*)(T, T)>
    T max(T _a, T _b, cmp_f cmp = al_compare_less)
    {
        if (cmp(_a, _b))
            return _b;
        else
            return _a;
    }

    template<typename T>
    void swap(T &_a, T &_b)
    {
        T tmp;
        tmp = _a;
        _a = _b;
        _b = tmp;
    }

    template<typename T, typename cmp_f= bool (*)(T, T)>
    bool between(T _a, T _b, T _c, cmp_f cmp = al_compare_less) // Check wheterh _c is between [_a,_b]
    {
        if (_a > _b)
        {
            swap(_a, _b);
        }

        return _a <= _c && _c <= _b;
    }


    /*******************************************************************************************
     * Merge sort
     * @tparam T
     * @tparam cmp_f
     * @param _array
     * @param cmp
     ******************************************************************************************/
    template<typename T, typename cmp_f= bool (*)(T, T)>
    void MergeSort(ContainerBase <T> &_array, cmp_f cmp = al_compare_less); //Merge sort main entry
    template<typename T>
    void msort(ContainerBase <T> &_array, bool (*cmp)(T _a, T _b), int _lpos, int _rpos); // msort sub function
    template<typename T>
    void merge(ContainerBase <T> &_array, bool (*cmp)(T _a, T _b), int _lpos, int _cpos, int _rpos); //Merge array

    template<typename T, typename cmp_f>
    inline void MergeSort(ContainerBase <T> &_array, cmp_f cmp)
    {
        if (cmp == nullptr)
        {
            throw ALGORITHM_ERR("Merge sort must provide a customise comparison function");
        }

        int sz = _array.Size();

        if (sz <= 1)
            return;

        msort(_array, cmp, 0, sz - 1);

    }

    template<typename T>
    void msort(ContainerBase <T> &_array, bool (*cmp)(T _a, T _b), int _lpos, int _rpos)
    {
        if (_lpos < _rpos)
        {
            int cpos = (_lpos + _rpos) / 2;
            msort(_array, cmp, _lpos, cpos);
            msort(_array, cmp, cpos + 1, _rpos);
            merge(_array, cmp, _lpos, cpos, _rpos);
        }
    }

    template<typename T>
    void merge(ContainerBase <T> &_array, bool (*cmp)(T _a, T _b), int _lpos, int _cpos, int _rpos)
    {
        int len = _rpos - _lpos + 1;
        T *tmpArray = new T[len]; //temporary array to store the merge array;

        int lp, rp, tp; // left, right pointer, and temp array pointer;
        int leftEnd = _cpos;
        int rightEnd = _rpos;

        lp = _lpos;
        rp = _cpos + 1;
        tp = 0;


        while (lp <= leftEnd && rp <= rightEnd)
        {
            if (cmp(_array[lp], _array[rp]))
            {
                tmpArray[tp++] = _array[lp++];
            }
            else
            {
                tmpArray[tp++] = _array[rp++];
            }
        }

        // Dealing with the rest elements
        for (; lp <= leftEnd; lp++, tp++)
        {
            tmpArray[tp] = _array[lp];
        }

        for (; rp <= rightEnd; rp++, tp++)
        {
            tmpArray[tp] = _array[rp];
        }

        for (int i = 0; i < len; ++i)
        {
            _array[_lpos + i] = tmpArray[i];
        }

        delete[] tmpArray;
    }


}

#endif //COMPUTATIONALGEMOETRY_ALGORITHM_H
