//
// Created by amos on 5/26/19.
//

#ifndef COMPUTATIONALGEMOETRY_LIST_H
#define COMPUTATIONALGEMOETRY_LIST_H

namespace CG
{
    template <typename T>
    class List
    {
    public:
        List();
        List(const List<T>& _rhs);
        ~List();

        void Insert(T _elem);
        void Delete(T _elem);


    };
}

#endif //COMPUTATIONALGEMOETRY_LIST_H
