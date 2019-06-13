//
// Created by amos on 6/1/19.
// For the sake of computational geometry assignment.
// I have to rewrite everything from scratch.
//

#ifndef COMPUTATIONALGEMOETRY_BINARYTREE_H
#define COMPUTATIONALGEMOETRY_BINARYTREE_H

#include "ContainerBase.h"
#include "Vector.h"

namespace CG
{

#define BTREE_ERR(x) "Binary tree error: " x

    template<typename T>
    inline COMPARE_RES compare_less(T _a, T _b)
    {
        if (_a < _b)
            return SMALLER;
        else if (_a == _b)
            return EQUAL;
        else
            return LARGER;
    }

    template<typename T>
    class BinaryTree : public ContainerBase<T>
    {
    public:
        struct tree_node
        {
            T elem;
            tree_node *llink;
            tree_node *rlink;
            int64 height;
        };

    public:
        BinaryTree(); //Default constructor deleted
        BinaryTree(COMPARE_RES (*_cmp)(T, T)); // Take compare operator
        BinaryTree(const BinaryTree<T> &_rhs); //Copy constructor

        virtual ~BinaryTree();

        virtual void Insert(T _elem); // Insert element to the tree.
        // Delete element from the tree, if the element not exists, we do nothing!.
        virtual void Delete(T _elem);

        // Search the element and return the node information;
        bool Pred_and_Succ(const T _elem, T &_pred, T &_succ); // Find the predecor of this element

        void Clear();

    public:
        T &operator[](int64 _idx); // Search is in order. (not preorder or postorder)

        template<typename Tf>
        friend std::ostream &operator<<(std::ostream &out, BinaryTree<Tf> &_rhs);

    protected:
        virtual void print(std::ostream &out);
        void destroy(tree_node *&_p); // destroy the sub tree from this node
        void delete_node(tree_node *&_p); // delete specified node and re-arrange the tree structure
        void inorder(tree_node *_p, Vector<T> &vec); // Put element in order, and save to the vector
        void findPreSuc(tree_node *_root, tree_node *&pre, tree_node *&suc, T _elem, bool &found);

    protected:
        tree_node *m_root; //Root of the tree
        COMPARE_RES (*cmp)(T, T);
    };


// Implementation
    template<typename T>
    BinaryTree<T>::BinaryTree()
    {
        m_root = nullptr;
        this->m_size = 0;
        cmp = compare_less;
    }

    template<typename T>
    BinaryTree<T>::BinaryTree(COMPARE_RES (*_cmp)(T, T))
    {
        m_root = nullptr;
        this->m_size = 0;
        cmp = _cmp;
    }

    template<typename T>
    BinaryTree<T>::~BinaryTree()
    {
        Clear();
    }

    template<typename T>
    void BinaryTree<T>::Insert(T _elem)
    {
        tree_node *current;
        tree_node *tail;

        tree_node *newNode = new tree_node;
        newNode->elem = _elem;
        newNode->rlink = nullptr;
        newNode->llink = nullptr;
        newNode->height = 0;

        if (m_root == nullptr) // If the tree is empty
        {
            m_root = newNode;
        }
        else
        {
            current = m_root;
            while (current != nullptr)
            {
                tail = current;
                if (cmp(newNode->elem, current->elem) == SMALLER)
                {
                    current = current->llink; // Go to left side
                }
                else
                {
                    current = current->rlink;
                }
            }

            // Now we are ready to insert the node!
            if (cmp(newNode->elem, tail->elem) == SMALLER)
            {
                tail->llink = newNode;
            }
            else
            {
                tail->rlink = newNode;
            }
        }

        this->m_size++;
    }

    template<typename T>
    void BinaryTree<T>::Delete(T _elem)
    {
        // Find the element first
        bool found = false;

        tree_node *current = m_root;
        tree_node *tail = nullptr;

        CG::COMPARE_RES cmp_res;
        while (current != nullptr && found == false)
        {
            if ((cmp_res = cmp(_elem, current->elem)) == CG::EQUAL)
            {
                found = true;
                continue;
            }

            tail = current;
            if (cmp_res == LARGER)
            {
                current = current->rlink;
            }
            else
            {
                current = current->llink;
            }
        }

        if (!found) // Element not in the tree
            return;


        if (tail == nullptr) //Element in the root of the tree
        {
            delete_node(m_root);
        }
        else
        {
            if (cmp(_elem, tail->elem) == CG::SMALLER)
            {
                delete_node(tail->llink);
            }
            else
            {
                delete_node(tail->rlink);
            }
        }

        this->m_size--;
    }

    template<typename T>
    bool BinaryTree<T>::Pred_and_Succ(const T _elem, T &_pred, T &_succ)
    {
        if (m_root == nullptr) //root is empty
            return false;

        tree_node *pre = nullptr, *succ = nullptr;
        bool found = false;
        findPreSuc(m_root, pre, succ, _elem, found);

        if (!found)
            return false;

        if (pre != nullptr)
            _pred = pre->elem;

        if (succ != nullptr)
            _succ = succ->elem;

        return true;
    }

    template<typename T>
    void BinaryTree<T>::delete_node(tree_node *&p)
    {
        tree_node *tmp;
        tree_node *tail;
        tree_node *current;

        if (p == nullptr)
            return;

        if (p->rlink == nullptr && p->llink == nullptr) // No children for this node
        {
            delete p;
            p = nullptr;
        }
        else if (p->rlink == nullptr) // Has a left child
        {
            tmp = p;
            p = p->llink;
            delete tmp;
        }
        else if (p->llink == nullptr) // Has a right child
        {
            tmp = p;
            p = p->rlink;
            delete tmp;
        }
        else // Has both left and right children
        {
            current = p->llink; // Search the biggest element on its left child, then replace current node
            tail = nullptr;
            while (current->rlink != nullptr)
            {
                tail = current;
                current = current->rlink;
            }

            p->elem = current->elem;
            if (tail == nullptr)
            {
                p->llink = current->llink;
            }
            else
            {
                tail->rlink = current->llink;
            }

            delete current;
        }
    }

    template<typename T>
    void BinaryTree<T>::findPreSuc(tree_node *_root, tree_node *&pre, tree_node *&suc, T _elem, bool &found)
    {
        if (_root == nullptr)
            return;

        if (_root->elem == _elem)
        {
            found = true;
            if (_root->llink != nullptr)
            {
                tree_node *tmp = _root->llink;
                while (tmp->rlink != nullptr)
                    tmp = tmp->rlink;

                pre = tmp;
            }

            if (_root->rlink != nullptr)
            {
                tree_node *tmp = _root->rlink;
                while (tmp->llink != nullptr)
                    tmp = tmp->llink;

                suc = tmp;
            }

            return;
        }

        if (cmp(_elem, _root->elem) == SMALLER)
        {
            suc = _root;
            findPreSuc(_root->llink, pre, suc, _elem, found);
        }
        else
        {
            pre = _root;
            findPreSuc(_root->rlink, pre, suc, _elem, found);
        }
    }

    template<typename T>
    void BinaryTree<T>::inorder(tree_node *_p, Vector<T> &_vec)
    {
        if (_p == nullptr)
            return;

        inorder(_p->llink, _vec);
        // Deal with this element
        _vec.Push_back(_p->elem);
        inorder(_p->rlink, _vec);
    }

    template<typename T>
    void BinaryTree<T>::Clear()
    {
        destroy(m_root);
        m_root = nullptr;
    }

    template<typename T>
    void BinaryTree<T>::destroy(tree_node *&p)
    {
        if (p == nullptr)
            return;

        destroy(p->llink);
        destroy(p->rlink);

        delete p;
        p = nullptr;
        return;
    }

    template<typename T>
    T &BinaryTree<T>::operator[](int64 _idx)
    {
        throw BTREE_ERR("Not support operator []");
    }

    template<typename T>
    std::ostream &operator<<(std::ostream &out, BinaryTree<T> &_rhs)
    {
        if (_rhs.m_root == nullptr)
        {
            out << "Empty tree! ";
            return out;
        }

        _rhs.print(out);
        return out;
    }

    template<typename T>
    void BinaryTree<T>::print(std::ostream &out)
    {
        Vector<T> vec;
        vec.Reserve(this->m_size);
        inorder(m_root, vec);
        out << vec;
    }
}

#endif //COMPUTATIONALGEMOETRY_BINARYTREE_H
