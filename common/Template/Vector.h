//
// Created by amos on 5/26/19.
//

#ifndef COMPUTATIONALGEMOETRY_VECTOR_H
#define COMPUTATIONALGEMOETRY_VECTOR_H

#include <stdlib.h>
#include <iostream>
#include <cstring>
#include "ContainerBase.h"
#include "Algorithm.h"

namespace CG
{

#define VECTOR_ERR(x) "Vector error: " x

    const int _DEFAULT_VECTOR_SIZE = 64;

    template<typename T>
    class Vector : public ContainerBase<T>
    {
    public:
        Vector(); //Default Constructor, everything goes to default
        Vector(int64 _n); //Specify the vector with know element size
        Vector(const Vector &_rhs);

        ~Vector();

        void Push_back(const T _elem); // Push the element to the end of the vector
        void Reserve(int64 _n); // Allocate size for this vector
        void Reverse(); // Reverse the order in this vector;
        void Resize(int64 _n); // Resize the vector to size _n

    protected:
        void resize(int64 _n); //Resize the vector once the number of elements exceed current numbers


        //Override operators
    public:
        T &operator[](int64 _idx); //Operator for index searching
        Vector<T> &operator=(const Vector<T> &_rhs); //Copy new vector

        template<typename Tf>
        friend std::ostream &operator<<(std::ostream &out, const Vector<Tf> &_rhs);

    private:
        T *m_array;
        int m_reserved_size;
    };

    // Implementation
    template<typename T>
    Vector<T>::Vector()
            :ContainerBase<T>()
    {
        m_reserved_size = _DEFAULT_VECTOR_SIZE;
        m_array = new T[_DEFAULT_VECTOR_SIZE];
    }


    template<typename T>
    Vector<T>::Vector(int64 _n)
            :ContainerBase<T>(_n)
    {
        m_reserved_size = _n;
        m_array = new T[_n];
    }

    template<typename T>
    Vector<T>::Vector(const Vector<T> &_rhs)
    {
        m_reserved_size = _rhs.m_reserved_size;
        this->m_size = _rhs.m_size;
        m_array = new T[m_reserved_size];
        for (int64 i = 0; i < this->m_size; ++i)
        {
            m_array[i] = _rhs.m_array[i];
        }
    }


    template<typename T>
    Vector<T>::~Vector()
    {
        if (m_array != nullptr)
        {
            delete[] m_array;
            m_reserved_size = 0;
            m_array = nullptr;
        }
    }

    template<typename T>
    void Vector<T>::Reserve(int64 _n)
    {
        if (m_array != nullptr)
        {
            this->m_size = 0;
            delete[] m_array;
            m_array = nullptr;
        }

        m_reserved_size = _n;
        m_array = new T[_n];
    }

    template<typename T>
    void Vector<T>::Reverse()
    {
        int64 l = 0, r = this->m_size - 1;

        while (l < r)
        {
            CG::swap(m_array[l++], m_array[r--]);
        }

    }

    template<typename T>
    void Vector<T>::Push_back(const T _elem)
    {
        if (this->m_size == m_reserved_size)
            this->resize(m_reserved_size + _DEFAULT_VECTOR_SIZE);

        m_array[this->m_size] = _elem;
        this->m_size++;
    }

    template<typename T>
    void Vector<T>::Resize(int64 _n)
    {
        resize(_n);
        this->m_size = _n;
    }

    template<typename T>
    void Vector<T>::resize(int64 _n)
    {
        if (_n > m_reserved_size)
        {
            T *new_array = new T[_n];
            if (m_array != nullptr)
            {
                // Copy elements, don't use memset or memcpy, for T might be a class.
                // For class object, memset will set its address to 0!
                for (int64 i = 0; i < this->m_size; ++i)
                {
                    new_array[i] = m_array[i];
                }
                //memcpy(new_array, m_array, sizeof(T) * this->m_size);
                delete[] m_array;
                m_array = nullptr;
            }
            m_array = new_array;

            m_reserved_size = _n;
        }
    }

    template<typename T>
    T &Vector<T>::operator[](int64 _idx)
    {
        if (_idx >= this->m_size || _idx < -1)
        {
            throw VECTOR_ERR("index out of range");
        }

        if (_idx == -1) // Return the last element
            return m_array[this->m_size - 1];
        else
            return m_array[_idx];
    }

    template<typename T>
    Vector<T> &Vector<T>::operator=(const Vector<T> &_rhs)
    {
        if (this == &_rhs)
            return *this;

        m_reserved_size = _rhs.m_reserved_size;
        this->m_size = _rhs.m_size;
        m_array = new T[m_reserved_size];
        for (int64 i = 0; i < this->m_size; ++i)
        {
            m_array[i] = _rhs.m_array[i];
        }

        return *this;
    }

    template<typename T>
    std::ostream &operator<<(std::ostream &out, const Vector<T> &_rhs)
    {
        if (_rhs.m_size == 0)
        {
            out << "Empty vector";
            return out;
        }

        out << "[";
        for (int64 i = 0; i < _rhs.m_size - 1; ++i)
        {
            out << _rhs.m_array[i] << ", ";
        }

        out << _rhs.m_array[_rhs.m_size - 1] << "]";
        return out;
    }

}

#endif //COMPUTATIONALGEMOETRY_VECTOR_H
