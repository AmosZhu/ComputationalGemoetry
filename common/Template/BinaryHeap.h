//
// Created by amos on 6/11/19.
//

#ifndef COMPUTATIONALGEMOETRY_BINARYHEAP_H
#define COMPUTATIONALGEMOETRY_BINARYHEAP_H

#include "Vector.h"

namespace CG
{
#define BHEAP_ERR(x) "Binary heap error: " x

    template<typename T>
    inline bool cmp_f(T _a, T _b)
    {
        return _a < _b;
    }

    template<typename T>
    class BinaryHeap : public ContainerBase<T>
    {
    public:
        BinaryHeap(); // Default Constructor
//        BinaryHeap(int _n); // Specify the number of element in the binary
        BinaryHeap(int _n, bool(*_cmp)(T, T) = cmp_f); // Specify the number of element in the binary
        BinaryHeap(bool(*_cmp)(T, T)); // Set compare function
        BinaryHeap(const BinaryHeap<T> &_rhs); // Copy constructor;
        ~BinaryHeap();

        void Insert(T _elem); // Insert the element into the
        T DeleteMin(); // Pop the minimum element in the heap

        T &operator[](int64 _idx); // Search is in order. (not preorder or postorder)

    private:
        Vector<T> m_array; // Store the element in array
        bool (*cmp)(T, T); // compare function
    };

    // Implementation

    template<typename T>
    BinaryHeap<T>::BinaryHeap()
            :ContainerBase<T>()
    {
        cmp = cmp_f;
    }

    template<typename T>
    BinaryHeap<T>::BinaryHeap(bool (*_cmp)(T, T))
            :ContainerBase<T>()
    {
        cmp = _cmp;
    }

    template<typename T>
    BinaryHeap<T>::BinaryHeap(int _n, bool (*_cmp)(T, T))
            :m_array(_n + 1), cmp(_cmp), ContainerBase<T>()
    {}

    template<typename T>
    BinaryHeap<T>::BinaryHeap(const CG::BinaryHeap<T> &_rhs)
            :ContainerBase<T>(_rhs)
    {
        m_array = _rhs.m_array;
        cmp = _rhs.cmp;
        this->m_size = _rhs.m_size;
    }

    template<typename T>
    BinaryHeap<T>::~BinaryHeap()
    {}

    template<typename T>
    void BinaryHeap<T>::Insert(T _elem)
    {
        // The m_array[0] is not used in this situation!
        if (this->m_size >= m_array.Size() - 1)
        {
            m_array.Resize(2 * this->m_size + 1);
        }

        int64 idx;
        for (idx = ++this->m_size; cmp(_elem, m_array[idx / 2]) && idx / 2 > 0; idx /= 2)
        {
            m_array[idx] = m_array[idx / 2];
        }
        m_array[idx] = _elem;
    }

    template<typename T>
    T BinaryHeap<T>::DeleteMin()
    {
        if (this->IsEmpty())
            throw BHEAP_ERR("Empty!");

        int64 idx, childIdx;

        T res = m_array[1]; // Minimum element is always at the top
        T lastElem = m_array[this->m_size];
        this->m_size--;

        for (idx = 1; idx * 2 <= this->m_size; idx = childIdx)
        {
            childIdx = idx * 2;

            if (childIdx <= this->m_size)
            {
                if (childIdx + 1 <= this->m_size)
                {
                    if (cmp(m_array[childIdx + 1], m_array[childIdx]))
                        childIdx++;
                }

                if (cmp(m_array[childIdx], lastElem))
                    m_array[idx] = m_array[childIdx];
                else
                    break;
            }
            else
            {
                break;
            }
        }

        m_array[idx] = lastElem;
        return res;
    }

    template<typename T>
    T &BinaryHeap<T>::operator[](int64 _idx)
    {
        throw BHEAP_ERR("Not support operator []");
    }

}

#endif //COMPUTATIONALGEMOETRY_BINARYHEAP_H
