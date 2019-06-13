//
// Created by root on 5/30/19.
//

#ifndef COMPUTATIONALGEMOETRY_CONTAINERBASE_H
#define COMPUTATIONALGEMOETRY_CONTAINERBASE_H

#include "type.h"
#include <iostream>

namespace CG
{
    template<typename T>
    class ContainerBase
    {
    public:
        ContainerBase(); // Constructor
        ContainerBase(int64 _n); //Specify the size with new constructor
        virtual ~ContainerBase() = 0;

        virtual int64 Size() const; // Return the size of the elements
        virtual bool IsEmpty() const; // Is empty

        virtual T &operator[](int64 _idx) = 0;

    protected:
        int64 m_size;
    };

    template<typename T>
    ContainerBase<T>::ContainerBase()
    {
        m_size = 0;
    }

    template<typename T>
    ContainerBase<T>::ContainerBase(int64 _n)
    {
        m_size = _n;
    }

    template<typename T>
    ContainerBase<T>::~ContainerBase()
    {
        m_size = 0;
    }

    template<typename T>
    int64 ContainerBase<T>::Size() const
    {
        return m_size;
    }

    template<typename T>
    bool ContainerBase<T>::IsEmpty() const
    {
        return m_size == 0;
    }
}

#endif //COMPUTATIONALGEMOETRY_CONTAINERBASE_H
