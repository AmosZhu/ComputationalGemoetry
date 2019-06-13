//
// Created by amos on 5/26/19.
//

#ifndef COMPUTATIONALGEMOETRY_TYPE_H
#define COMPUTATIONALGEMOETRY_TYPE_H

namespace CG
{
    enum LEFT_TEST_RES
    {
        LEFT,
        COLINEAR_ON, // The point on the edge
        COLINEAR_OUT, // The point colinear but not on the edge
        RIGHT
    };

    enum COMPARE_RES
    {
        SMALLER,
        EQUAL,
        LARGER
    };

    typedef long long int64;
}

#endif //COMPUTATIONALGEMOETRY_TYPE_H
