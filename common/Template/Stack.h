//
// Created by amos on 5/25/19.
// A stack from scratch, for the test platform is not allowed to use stl.
//

#ifndef COMPUTATIONALGEMOETRY_STACK_H
#define COMPUTATIONALGEMOETRY_STACK_H

#include <iostream>
#include "type.h"
#include "ContainerBase.h"


namespace CG
{

#define STACK_ERR(x) "Stack error: " x

    template<typename T>
    class Stack : public ContainerBase<T>
    {
    public:
        struct node_t
        {
            T elem;
            node_t *next;
        };

    public:
        Stack(); //Default Constructor
        Stack(const Stack &_rhs); //Copy Constructor
        Stack(const Stack &&_rhs) = delete; // For the test platform only support C++ 11
        ~Stack();

        T Top(); //Return the top element of the stack but not pop
        T Pop(); //Pop the top element of the stack
        void Push(T _elem); //Push a new element to the top


        Stack<T> &operator=(const Stack &_rhs); // Assign operator
        T &operator[](int64 _idx); // Convenient way to access the element

        template<typename Tf>
        friend std::ostream &operator<<(std::ostream &out, const Stack<Tf> &_rhs);

    private:
        node_t *m_head;
    };


    // Implementation
    template<typename T>
    Stack<T>::Stack()
    {
        this->m_size = 0;
        m_head = nullptr;
    }

    template<typename T>
    Stack<T>::Stack(const Stack &_rhs)
    {
        if (_rhs.size() == 0)
        {
            this->m_size = 0;
            m_head = nullptr;
            return;
        }

        // Loop through the stack and copy all the values
        this->m_size = _rhs.m_size;
        m_head = new node_t();

        node_t *rhs_ptr = _rhs.m_head;
        node_t *ptr = m_head;

        m_head->elem = rhs_ptr->elem;

        while (rhs_ptr->next != nullptr)
        {
            rhs_ptr = rhs_ptr->next;

            node_t *newNode = new node_t();
            newNode->elem = rhs_ptr->elem;

            ptr->next = newNode;
            ptr = ptr->next;
        }

    }

    template<typename T>
    Stack<T>::~Stack()
    {
        if (m_head == nullptr)
            return;

        while (m_head->next != nullptr)
        {
            node_t *ptr = m_head;
            m_head = m_head->next;
            delete ptr;
        }

        m_head = nullptr;
    }

    template<typename T>
    T Stack<T>::Top()
    {
        if (m_head == nullptr)
            throw STACK_ERR("Stack is empty");

        T val = m_head->elem;

        return val;
    }

    template<typename T>
    T Stack<T>::Pop()
    {
        if (m_head == nullptr)
            throw STACK_ERR("Stack is empty");

        T val = m_head->elem;

        node_t *ptr = m_head;
        m_head = m_head->next;

        this->m_size--;
        delete ptr;

        return val;
    }

    template<typename T>
    void Stack<T>::Push(T elem)
    {
        node_t *newNode = new node_t();
        newNode->elem = elem;
        newNode->next = m_head;

        m_head = newNode;
        this->m_size++;
    }

    template<typename T>
    T &Stack<T>::operator[](int64 _idx)
    {
        if (_idx >= this->m_size || _idx < 0)
        {
            throw STACK_ERR("index out of range");
        }

        node_t *ptr = m_head;
        int64 i = 0;
        while (i < _idx)
        {
            ptr = ptr->next;
            i++;
        }
        return ptr->elem;
    }

    template<typename T>
    std::ostream &operator<<(std::ostream &out, const Stack<T> &_rhs)
    {
        if (_rhs.m_head == nullptr)
        {
            out << "Empty stack!";
            return out;
        }

        // Loop through the stack
        struct Stack<T>::node_t *ptr = _rhs.m_head;

        out << "Top to Bottom: (";
        while (ptr->next != nullptr)
        {
            out << ptr->elem << ", ";
            ptr = ptr->next;
        }

        out << ptr->elem << ")";

        return out;
    }
}

#endif //COMPUTATIONALGEMOETRY_STACK_H
