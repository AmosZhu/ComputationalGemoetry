//
// Created by amos on 6/2/19.
//

#ifndef COMPUTATIONALGEMOETRY_BALANCEDBSTREE_H
#define COMPUTATIONALGEMOETRY_BALANCEDBSTREE_H

#include "BinaryTree.h"
#include "Algorithm.h"
#include "Stack.h"

namespace CG
{
    template<typename T>
    class BalancedBSTree : public BinaryTree<T>
    {
    public:
        BalancedBSTree(); //Default Constructor
        BalancedBSTree(COMPARE_RES (*_cmp)(T, T)); // Take compare operator
        BalancedBSTree(const BalancedBSTree<T> &_rhs); //Copy constructor
        virtual ~BalancedBSTree();

        virtual void Insert(T _elem); // Insert element to the tree.
        // Delete element from the tree, if the element not exists, we do nothing!.
        virtual void Delete(T _elem);

        //Return the depth of the tree, value stores in the root;
        int64 Depth();

    protected:
        virtual void print(std::ostream &out);

    private:
        // Recursive insertion
        struct BinaryTree<T>::tree_node *insert(T _elem, struct BinaryTree<T>::tree_node *&_node);

        void deleteFromTree(struct BinaryTree<T>::tree_node *&p, T &pop_elem, bool &pop_elem_f,
                            CG::Stack<struct BinaryTree<T>::tree_node *> &nodeStack);

        // Return the height of current node;
        int64 height(struct BinaryTree<T>::tree_node *_p);

        struct BinaryTree<T>::tree_node *singleRotationWithLeft(struct BinaryTree<T>::tree_node *k2);

        struct BinaryTree<T>::tree_node *singleRotationWithRight(struct BinaryTree<T>::tree_node *k2);

        struct BinaryTree<T>::tree_node *doubleRotationWithLeft(struct BinaryTree<T>::tree_node *k3);

        struct BinaryTree<T>::tree_node *doubleRotationWithRight(struct BinaryTree<T>::tree_node *k3);
    };


    // Implementation
    template<typename T>
    BalancedBSTree<T>::BalancedBSTree()
            :BinaryTree<T>()
    {}

    template<typename T>
    BalancedBSTree<T>::BalancedBSTree(COMPARE_RES(*_cmp)(T, T))
            :BinaryTree<T>(_cmp)
    {}

    template<typename T>
    BalancedBSTree<T>::BalancedBSTree(const BalancedBSTree<T> &_rhs)
            :BinaryTree<T>(_rhs)
    {}

    template<typename T>
    BalancedBSTree<T>::~BalancedBSTree()
    {}

    template<typename T>
    int64 BalancedBSTree<T>::Depth()
    {
        return height(this->m_root);
    }

    template<typename T>
    void BalancedBSTree<T>::Insert(T _elem)
    {
        insert(_elem, this->m_root);
        this->m_size++;
    }

    template<typename T>
    void BalancedBSTree<T>::Delete(T _elem)
    {
        struct BinaryTree<T>::tree_node *current = nullptr, *tail = nullptr, *p1, *p2;
        CG::Stack<struct BinaryTree<T>::tree_node *> nodeStack;
        bool found = false;
        T pop_elem;
        bool pop_elem_f; // If this set true, we know we want some element to replace current delete node

        if (this->m_root == nullptr)
            return; // Finish if this is an empty tree

        // 1. First find the element in the tree, n(log(n))

        current = this->m_root;
        while (current != nullptr && !found)
        {
            CG::COMPARE_RES cmp_res;
            if ((cmp_res = this->cmp(_elem, current->elem)) == CG::EQUAL)
            {
                found = true;
                continue;
            }

            tail = current;
            nodeStack.Push(current);

            if (cmp_res == SMALLER)
            {
                current = current->llink;
            }
            else
            {
                current = current->rlink;
            }
        }

        if (!found) // This element not in the tree!
            return;

        // 2. Delete the element from the tree
        if (tail != nullptr)
        {
            if (this->cmp(_elem, tail->elem) == SMALLER)
                deleteFromTree(tail->llink, pop_elem, pop_elem_f, nodeStack);
            else
                deleteFromTree(tail->rlink, pop_elem, pop_elem_f, nodeStack);
        }
        else
        {
            // Delete the root!
            deleteFromTree(this->m_root, pop_elem, pop_elem_f, nodeStack);
        }

        // 3. We need update its predecor's height and balanced the tree
        if (!nodeStack.IsEmpty())
            p2 = nodeStack.Pop();

        while (!nodeStack.IsEmpty())
        {
            p1 = p2;
            p2 = nodeStack.Pop();
            p1->height = CG::max(height(p1->llink), height(p1->rlink)) + 1;

            if (this->cmp(pop_elem, p1->elem) == CG::SMALLER)
            {
                // The pop element from the left subtree, check whether the right subtree is deeper than the left one
                if (height(p1->rlink) - height(p1->llink) == 2)
                {
                    if (height(p1->rlink->llink) > height(p1->rlink->rlink))
                    {
                        if (this->cmp(p1->elem, p2->elem) == CG::SMALLER)
                            p2->llink = doubleRotationWithLeft(p1);
                        else
                            p2->rlink = doubleRotationWithLeft(p1);
                    }
                    else
                    {
                        if (this->cmp(p1->elem, p2->elem) == CG::SMALLER)
                            p2->llink = singleRotationWithRight(p1);
                        else
                            p2->rlink = singleRotationWithRight(p1);
                    }
                }
            }
            else
            {
                // The pop element from the right subtree, check whether the left subtree is deeper than the right one
                if (height(p1->llink) - height(p1->rlink) == 2)
                {
                    if (height(p1->llink->llink) > height(p1->llink->rlink))
                    {
                        if (this->cmp(p1->elem, p2->elem) == CG::SMALLER)
                            p2->llink = singleRotationWithLeft(p1);
                        else
                            p2->rlink = singleRotationWithLeft(p1);
                    }
                    else
                    {
                        if (this->cmp(p1->elem, p2->elem) == CG::SMALLER)
                            p2->llink = doubleRotationWithRight(p1);
                        else
                            p2->rlink = doubleRotationWithRight(p1);
                    }
                }
            }
        }

        // Process the last node p2, this should be the root of the tree!
        p2->height = CG::max(height(p2->llink), height(p2->rlink)) + 1;
        if (this->cmp(pop_elem, p2->elem) == CG::SMALLER)
        {
            if (height(p2->rlink) - height(p2->llink) == 2)
            {

                if (height(p2->rlink->llink) > height(p2->rlink->rlink))
                    this->m_root = doubleRotationWithLeft(p2);
                else
                    this->m_root = singleRotationWithRight(p2);

            }
        }
        else
        {
            if (height(p2->llink) - height(p2->rlink) == 2)
            {
                if (height(p2->llink->llink) > height(p2->llink->rlink))
                    this->m_root = singleRotationWithLeft(p2);
                else
                    this->m_root = doubleRotationWithRight(p2);

            }
        }

        if (pop_elem_f)
            current->elem = pop_elem;

        this->m_size--;
    }

    template<typename T>
    struct BinaryTree<T>::tree_node *BalancedBSTree<T>::insert(T _elem, struct BinaryTree<T>::tree_node *&node)
    {
        if (node == nullptr)
        {
            node = new struct BinaryTree<T>::tree_node;
            node->elem = _elem;
            node->llink = nullptr;
            node->rlink = nullptr;
            node->height = 0;
        }
        else if (this->cmp(_elem, node->elem) == CG::SMALLER)
        {
            // Insert it to the left subtree
            node->llink = insert(_elem, node->llink);
            if (height(node->llink) - height(node->rlink) == 2) // Rotation when unbalanced
            {
                if (this->cmp(_elem, node->llink->elem) == CG::SMALLER)
                {
                    node = singleRotationWithLeft(node);
                }
                else
                {
                    node = doubleRotationWithRight(node);
                }
            }
        }
        else
        {
            // Insert it to the right subtree
            node->rlink = insert(_elem, node->rlink);
            if (height(node->rlink) - height(node->llink) == 2) // Rotation when unbalanced
            {
                if (this->cmp(_elem, node->rlink->elem) != CG::SMALLER)
                {
                    node = singleRotationWithRight(node);
                }
                else
                {
                    node = doubleRotationWithLeft(node);
                }
            }
        }

        node->height = max(height(node->llink), height(node->rlink)) + 1;

        return node;
    }

    template<typename T>
    void BalancedBSTree<T>::deleteFromTree(struct BinaryTree<T>::tree_node *&p, T &pop_elem, bool &pop_elem_f,
                                           CG::Stack<struct BinaryTree<T>::tree_node *> &nodeStack)
    {
        struct BinaryTree<T>::tree_node *tmp, *tail, *current;

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
            nodeStack.Push(p);
            tail = nullptr;
            while (current->rlink != nullptr)
            {
                nodeStack.Push(current);
                tail = current;
                current = current->rlink;
            }

            if (tail == nullptr)
            {
                p->llink = current->llink;
            }
            else
            {
                tail->rlink = current->llink;
            }

            pop_elem = current->elem;  // Save for replace later, different from binary tree!.
            pop_elem_f = true;
            delete current;
        }
    }

    template<typename T>
    struct CG::BinaryTree<T>::tree_node *
    BalancedBSTree<T>::singleRotationWithLeft(struct CG::BinaryTree<T>::tree_node *k2)
    {
        struct CG::BinaryTree<T>::tree_node *k1;
        if (k2 == nullptr)
            return nullptr;

        k1 = k2->llink;
        k2->llink = k1->rlink;
        k1->rlink = k2;

        k2->height = max(height(k2->llink), height(k2->rlink)) + 1;
        k1->height = max(height(k1->llink), height(k1->rlink)) + 1;

        return k1;
    }

    template<typename T>
    struct CG::BinaryTree<T>::tree_node *
    BalancedBSTree<T>::singleRotationWithRight(struct CG::BinaryTree<T>::tree_node *k2)
    {
        struct CG::BinaryTree<T>::tree_node *k1;
        if (k2 == nullptr)
            return nullptr;

        k1 = k2->rlink;
        k2->rlink = k1->llink;
        k1->llink = k2;

        k2->height = max(height(k2->llink), height(k2->rlink)) + 1;
        k1->height = max(height(k1->llink), height(k1->rlink)) + 1;

        return k1;
    }

    template<typename T>
    struct CG::BinaryTree<T>::tree_node *
    BalancedBSTree<T>::doubleRotationWithLeft(struct CG::BinaryTree<T>::tree_node *k3)
    {
        struct CG::BinaryTree<T>::tree_node *k2, *k1;
        if (k3 == nullptr)
            return nullptr;

        k2 = k3->rlink;
        k1 = k2->llink;

        k2->llink = k1->rlink;
        k1->rlink = k2;

        k3->rlink = k1->llink;
        k1->llink = k3;

        k3->height = max(height(k3->llink), height(k3->rlink)) + 1;
        k2->height = max(height(k2->llink), height(k2->rlink)) + 1;
        k1->height = max(height(k1->llink), height(k1->rlink)) + 1;

        return k1;
    }

    template<typename T>
    struct CG::BinaryTree<T>::tree_node *
    BalancedBSTree<T>::doubleRotationWithRight(struct CG::BinaryTree<T>::tree_node *k3)
    {
        struct CG::BinaryTree<T>::tree_node *k2, *k1;
        if (k3 == nullptr)
            return nullptr;

        k2 = k3->llink;
        k1 = k2->rlink;

        k2->rlink = k1->llink;
        k1->llink = k2;

        k3->llink = k1->rlink;
        k1->rlink = k3;

        k3->height = max(height(k3->llink), height(k3->rlink)) + 1;
        k2->height = max(height(k2->llink), height(k2->rlink)) + 1;
        k1->height = max(height(k1->llink), height(k1->rlink)) + 1;

        return k1;
    }

    template<typename T>
    int64 BalancedBSTree<T>::height(struct BinaryTree<T>::tree_node *_p)
    {
        if (_p == nullptr)
            return -1;

        return _p->height;
    }

    template<typename T>
    void BalancedBSTree<T>::print(std::ostream &out)
    {
        out << "(Tree depth: " << Depth() << ")";
        Vector<T> vec;
        vec.Reserve(this->m_size);
        this->inorder(this->m_root, vec);
        out << vec;
    }
}

#endif //COMPUTATIONALGEMOETRY_BALANCEDBSTREE_H
