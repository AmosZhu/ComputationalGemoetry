//
// Created by root on 5/31/19.
//

#include "../common/ConvexHull2D.h"


int main()
{
    CG::int64 n;
    std::cin >> n;

    CG::Point2<CG::int64> *pts = new CG::Point2<CG::int64>[n];

    for (int i = 0; i < n; ++i)
    {
        std::cin >> pts[i].x >> pts[i].y;
    }

    CG::ConvexHull2D<CG::int64> CH;
    CH.BuildFrom(pts, n, CG::GRAHAMSCAN);

    CG::int64 res = CH.ext_index.Size();
    for (CG::int64 i = 0; i < CH.ext_index.Size(); ++i)
    {
        res *= (CH.ext_index[i] + 1);
        res %= n + 1;
    }
    res = res % (n + 1);

    std::cout << res << std::endl;

    delete[] pts;

    return 0;
}
