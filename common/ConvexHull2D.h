//
// Created by amos on 5/26/19.
//

#ifndef COMPUTATIONALGEMOETRY_CONVEXHULL2D_H
#define COMPUTATIONALGEMOETRY_CONVEXHULL2D_H

#include "Point.h"
#include "Template/Stack.h"
#include "Coordinates.h"
#include "Template/Vector.h"
#include "Line.h"
#include "Template/Algorithm.h"
#include "iostream"

namespace CG
{
    enum CONVEXHULL_ALGORITHM
    {
        GRAHAMSCAN,
        JARVIS
    };

    template<typename T>
    class ConvexHull2D
    {
    protected:
        // Used for sorting
        struct sortNode
        {
            Point2<T> pt;
            double angle;
            int64 idx; // The original index of the point

            sortNode &operator=(const sortNode &_rhs)
            {
                pt = _rhs.pt;
                angle = _rhs.angle;
                idx = _rhs.idx;
            }
        };

        static bool cmp(sortNode _a, sortNode _b)
        {
            return _a.angle > _b.angle;
        }

    public:
        ConvexHull2D(); //Default constructor, everything initialise with 0
        ConvexHull2D(const ConvexHull2D<T> &_rhs); //Copy constructor
        ~ConvexHull2D();

        // Build a convexhull by given set of 2D points, return the index of the extreme points w.r.t to the original
        // points.
        void BuildFrom(const Point2<T> *_pts, int64 _sz, CG::CONVEXHULL_ALGORITHM _al = CG::JARVIS);

        // Add a single point, if this point contribute to the convexhull then update
        void AddNew(const Point2<T> _pt);

        // Detect whether intersect with another convex hull
        bool Intersect(ConvexHull2D<T> &_obj);

        template<typename Tf>
        friend std::ostream &operator<<(std::ostream &out, const ConvexHull2D<Tf> &_rhs);


    private:
        // GrahamScan will ignore the points lie on the extreme edges
        void GrahamScan(const Point2<T> *_pts, int64 _sz);

        // Jarvis take account the points lie on the extreme edges
        void Jarvis(const Point2<T> *_pts, int64 _sz);

        // Dobkin and Kirkpatrick's algorithm, only detect whether two convex hull interesect
        bool DK_intersection(ConvexHull2D<T> &_Q);

        // Detect possible intersections between the two chains
        bool dk_intersection_between(Vector<Line2D<T> *> &_P_L, int64 _pi_l, int64 _pi_r,
                                     Vector<Line2D<T> *> &_Q_R, int64 _qi_l, int64 _qi_r);

    public:
        Vector<int64> ext_index; //For computational gemoetry assignment
        Vector<Point2<T>> m_extpts; //Only save extreme points
    };

    // Implementation
    template<typename T>
    ConvexHull2D<T>::ConvexHull2D()
    {}

    template<typename T>
    ConvexHull2D<T>::ConvexHull2D(const CG::ConvexHull2D<T> &_rhs)
    {}

    template<typename T>
    ConvexHull2D<T>::~ConvexHull2D()
    {}

    template<typename T>
    void ConvexHull2D<T>::BuildFrom(const CG::Point2<T> *_pts, int64 _sz, CG::CONVEXHULL_ALGORITHM _al)
    {
        // Build Convex hull
        switch (_al)
        {
            case CG::JARVIS:
                Jarvis(_pts, _sz);
                break;
            case CG::GRAHAMSCAN:
            default:
                GrahamScan(_pts, _sz);
                break;
        }
    }

    template<typename T>
    bool ConvexHull2D<T>::Intersect(ConvexHull2D<T> &_obj)
    {
        return DK_intersection(_obj);
    }

    template<typename T>
    // Label the extreme points by GrahamScan algorithm
    void ConvexHull2D<T>::GrahamScan(const Point2<T> *_pts, int64 _sz)
    {
        if (_sz == 1)
            return;
        /*
         * Graham scan algorithm to build a convex hull
         * Find two extreme points as a basis, then sort
         * the rest points w.r.t the angle of the edge
         */

        //  First find lowest then leftmost point
        int64 idx = Lowest_T_Left(_pts, _sz);
        Point2<T> p1 = _pts[idx];

        int64 idx_2 = 0;
        if (idx_2 == idx)
            idx_2++;

        //  The second extreme point
        Point2<T> p2 = _pts[idx_2];
        Line2D<T> seg(p1, p2);
        for (int64 i = 0; i < _sz; ++i)
        {
            if (i == idx)
                continue;

            Point2<T> p3 = _pts[i];
            if (seg.ToLeftTest(p3) == LEFT)
            {
                p2 = p3;
                seg = Segment2D<T>(p1, p2);
                idx_2 = i;
            }
        }

        // Sort the rest of points base on the angle w.r.t to the basis edge
        Segment2D<T> basis(p1, p2);
        Vector<sortNode> pts;
        pts.Reserve(_sz);
        for (int64 i = 0; i < _sz; ++i)
        {
            if (i == idx || i == idx_2)
                continue; // Skip the initial two extreme points

            Segment2D<T> seg(p1, _pts[i]);
            double ang = basis.Angle(seg);
            sortNode node;
            node.angle = ang;
            node.pt = _pts[i];
            node.idx = i;
            pts.Push_back(node);
        }

        CG::MergeSort(pts, this->cmp);

        /*
         * Do Graham Scan to construct a convex hull
         */

        Stack<sortNode> s; // all points in this stack are extreme points
        Stack<sortNode> t;

        sortNode n1;
        n1.idx = idx;
        n1.pt = p1;

        sortNode n2;
        n2.idx = idx_2;
        n2.pt = p2;

        s.Push(n1);
        s.Push(n2);

        for (int64 i = 0; i < pts.Size(); ++i)
        {
            t.Push(pts[i]);
        }

        while (!t.IsEmpty())
        {
            Segment2D<T> seg(s[0].pt, s[1].pt);
            CG::LEFT_TEST_RES res = seg.ToLeftTest(t[0].pt);
            if (res == CG::LEFT)
            {
                s.Push(t.Pop());
            }
//            else if (res == CG::COLINEAR)
//            {
//                // Choose a point further away
//                double dist_01 = s[1].pt.Distance(s[0].pt);
//                double dist_02 = s[1].pt.Distance(t[0].pt);
//                if (dist_02 > dist_01)
//                {
//                    // Swap by a further point, but we still mark the previous one as an extreme point
//
//                    s.Pop();
//                }
//                else
//                {
//                    t.Pop();
//                }
//            }
            else if (res == CG::COLINEAR_ON)
            {
                t.Pop();
            }
            else
            {
                s.Pop();
            }
        }

        m_extpts.Reserve(s.Size());
        ext_index.Reserve(s.Size());

        while (!s.IsEmpty())
        {
            sortNode pop_elem = s.Pop();

            m_extpts.Push_back(pop_elem.pt);
            ext_index.Push_back(pop_elem.idx);
        }
    }

    template<typename T>
    void ConvexHull2D<T>::Jarvis(const Point2<T> *_pts, CG::int64 _sz)
    {
        /*
         *  Jarvis algorithm
         *  1. Find first extreme point and extreme edge
         */
        int64 initExPt = Lowest_T_Left(_pts, _sz);
        m_extpts.Reserve(_sz / 4);
        ext_index.Reserve(_sz / 4);

        if (_sz == 1)
        {
            return;
        }
        /*
         *  2. Loop to reconstruct a convex hull until meet the start point again.
         */
        Vector<int64> colinearPoints(_sz);
//        int64 *colinearPoints = new long long[m_size];
        int64 currentColinearPoint = -1;
        int64 colinearCount = 0;

        int64 previousExPt = initExPt;
        int64 currentExPt = -1;

        while (currentExPt != initExPt)
        {
            int64 idx = 0;

            /*
             *  Reset conlinear list information
             */
            currentColinearPoint = -1;

            /*
             *  Choose an arbitray point but not an extreme point to start
             */
            for (; idx < _sz; idx++)
            {
                if (idx != previousExPt)
                {
                    currentExPt = idx;
                    break;
                }
            }
            /*
             *  Update extreme point whennerver the point is on the right side of the edge.
             *  It means smaller angular
             */
            for (; idx < _sz; idx++)
            {
                if (idx == previousExPt || idx == currentExPt)
                {
                    continue;
                }
                Line2D<T> seg(_pts[previousExPt], _pts[currentExPt]);
                LEFT_TEST_RES ltres = seg.ToLeftTest(_pts[idx]);

                if (ltres == CG::RIGHT)
                {
                    currentExPt = idx;
                    colinearCount = 0;
                }
                else if (ltres == CG::COLINEAR_ON)
                {
                    // Only consider the points that are extreme point
                    if (currentColinearPoint != currentExPt)
                    {
                        currentColinearPoint = currentExPt;
                        colinearCount = 0;
                    }
                    colinearPoints[colinearCount++] = idx;
                }
            }

            /*
             *  If we have colinear extreme points, choose the largest distance point
             *  as next previous point
             */
            if (colinearCount > 0)
            {
                int64 largestPos = currentExPt;
                int64 replacePos = 0;
                for (int64 i = 0; i < colinearCount; i++)
                {
                    // Choose a point further away
                    Point2<T> previousPT = _pts[previousExPt];
                    double dist_01 = previousPT.Distance(_pts[largestPos]);
                    double dist_02 = previousPT.Distance(_pts[colinearPoints[i]]);

                    if (dist_02 > dist_01)
                    {
                        largestPos = colinearPoints[i];
                        replacePos = i;
                    }
                    m_extpts.Push_back(_pts[colinearPoints[i]]);
                }

                if (largestPos != currentExPt)
                {
                    colinearPoints[replacePos] = currentExPt;
                    currentExPt = largestPos;
                }

                for (int i = 0; i < colinearCount; i++)
                {
                    ext_index.Push_back(colinearPoints[i]);
                    //m_epIndices[epSize++] = colinearPoints[i];
                }
            }

            m_extpts.Push_back(_pts[currentExPt]);
            ext_index.Push_back(currentExPt);

            previousExPt = currentExPt;
        }

    }

    template<typename T>
    bool ConvexHull2D<T>::DK_intersection(ConvexHull2D<T> &_Q)
    {
        //1. Divide each convex hull into two monotone chains. (Top to bottom)

        int64 P_t_idx, P_b_idx, Q_t_idx, Q_b_idx;
        // Find the highest then leftmost point as the top.
        P_t_idx = CG::Highest_T_Left(m_extpts);
        //P_b_idx = CG::Lowest_T_Left(m_extpts);
        Q_t_idx = CG::Highest_T_Left(_Q.m_extpts);
        //Q_b_idx = CG::Lowest_T_Left(_Q.m_extpts);

        P_b_idx = -1; // The LTL point is at the last of the vector.
        Q_b_idx = -1;


        // Construct the left and right monotone chains.
        Vector<Line2D<T> *> P_L(m_extpts.Size() - P_t_idx + 1);
        Vector<Line2D<T> *> P_R(P_t_idx + 3);
        Vector<Line2D<T> *> Q_L(_Q.m_extpts.Size() - Q_t_idx + 1);
        Vector<Line2D<T> *> Q_R(Q_t_idx + 3);
        int64 k = 1;
        // The extreme points are saved in CCW, we need to construct a correct chain here

        // =====================The bottom ray for left chain of polygon P ===========
        // Construct the right chain first, and the ray should point to left infinity,

        // The order of right chain should be from Top to bottom
        P_R[0] = new Ray2D<T>(m_extpts[P_b_idx], m_extpts[P_b_idx] - Point2<T>(1, 0));
        k = 1;
        for (int i = 0; i <= P_t_idx; ++i, ++k)
        {
            P_R[k] = new Segment2D<T>(m_extpts[i], m_extpts[i - 1]);
        }
        P_R[k] = new Ray2D<T>(m_extpts[P_t_idx], m_extpts[P_t_idx] - Point2<T>(1, 0));
        P_R.Reverse(); // Reverse the order

        P_L[0] = new Ray2D<T>(m_extpts[P_b_idx], m_extpts[P_b_idx] + Point2<T>(1, 0));
        k = 1;
        for (int i = m_extpts.Size() - 1; i > P_t_idx; --i, ++k)
        {
            P_L[k] = new Segment2D<T>(m_extpts[i], m_extpts[i - 1]);
        }
        // The top ray for left chain of polygon P.
        P_L[k] = new Ray2D<T>(m_extpts[P_t_idx], m_extpts[P_t_idx] + Point2<T>(1, 0));

        // ============================ Same for Q =================================
        // ---------------------- The top ray for right chain of polygon Q ---------------
        Q_R[0] = new Ray2D<T>(_Q.m_extpts[Q_b_idx], _Q.m_extpts[Q_b_idx] - Point2<T>(1, 0));
        k = 1;
        for (int i = 0; i <= Q_t_idx; ++i, ++k)
        {
            Q_R[k] = new Segment2D<T>(_Q.m_extpts[i], _Q.m_extpts[i - 1]);
        }
        Q_R[k] = new Ray2D<T>(_Q.m_extpts[Q_t_idx], _Q.m_extpts[Q_t_idx] - Point2<T>(1, 0));
        Q_R.Reverse();

        Q_L[0] = new Ray2D<T>(_Q.m_extpts[Q_b_idx], _Q.m_extpts[Q_b_idx] + Point2<T>(1, 0));
        k = 1;
        for (int i = _Q.m_extpts.Size() - 1; i > Q_t_idx; --i, ++k)
        {
            Q_L[k] = new Segment2D<T>(_Q.m_extpts[i], _Q.m_extpts[i - 1]);
        }
        Q_L[k] = new Ray2D<T>(_Q.m_extpts[Q_t_idx], _Q.m_extpts[Q_t_idx] + Point2<T>(1, 0));


        // Only if P_L and Q_R has intersection, in the mean while P_R and Q_L has intersection.
        bool b_intersect = dk_intersection_between(P_L, 0, P_L.Size() - 1, Q_R, 0, Q_R.Size() - 1);
        std::cout << b_intersect << std::endl;

        bool b_intersect1 = dk_intersection_between(Q_L, 0, Q_L.Size() - 1, P_R, 0, P_R.Size() - 1);
        std::cout << b_intersect1 << std::endl;

        // Release the memory
        for (int i = 0; i < P_L.Size(); ++i)
        {
            delete P_L[i];
        }

        for (int i = 0; i < P_R.Size(); ++i)
        {
            delete P_R[i];
        }

        for (int i = 0; i < Q_L.Size(); ++i)
        {
            delete Q_L[i];
        }

        for (int i = 0; i < Q_R.Size(); ++i)
        {
            delete Q_R[i];
        }

        return b_intersect & b_intersect1;
    }

    template<typename T>
    bool ConvexHull2D<T>::dk_intersection_between(CG::Vector<CG::Line2D<T> *> &_P_L, CG::int64 _pi_l, CG::int64 _pi_r,
                                                  CG::Vector<CG::Line2D<T> *> &_Q_R, CG::int64 _qi_l, CG::int64 _qi_r)
    {
        // Return at trivial case when there is only one edge in P_L and Q_R
        if (_pi_r == _pi_l && _qi_l == _qi_r)
        {
            return _P_L[_pi_l]->Intersect(*_Q_R[_qi_l]);
        }

        // Take the median edges from both chains then decide next movement
        int64 pi_m = (_pi_r + _pi_l + 1) / 2;
        int64 qi_m = (_qi_r + _qi_l + 1) / 2;

        std::cout << "ep: " << *_P_L[pi_m] << ", eq: " << *_Q_R[qi_m] << std::endl;

        // 1. If they intersect with each other then return
        if (_P_L[pi_m]->Intersect(*_Q_R[qi_m]))
            return true;

        // 2. If not, find their possible intersection from line configuration
        Line2D<T> *ep = _P_L[pi_m]; // Slice them to base class -> line2D
        Line2D<T> *eq = _Q_R[qi_m];

        Point2<T> v;

        T ep_y = CG::max(ep->p.y, ep->q.y);
        T eq_y = CG::max(eq->p.y, eq->q.y);
        CG::LEFT_TEST_RES r3, r4;
        r3 = eq->ToLeftTest(ep->p);
        r4 = eq->ToLeftTest(ep->q);

        bool is_intersection = false;

        if (ep->potential_intersect_pt(*eq, v))
        {
            if (r3 == CG::LEFT && r4 == CG::LEFT)
            {
                // THe intersection point must higher or lower then ep
                if (v.y > eq_y)
                {
                    if (v.y > ep_y)
                    {
                        is_intersection = dk_intersection_between(_P_L, _pi_l, pi_m, _Q_R, _qi_l, qi_m);
                    }
                    else
                    {
                        is_intersection = dk_intersection_between(_P_L, pi_m, _pi_r, _Q_R, _qi_l, qi_m);
                    }
                }
                else
                {
                    if (v.y > ep_y)
                    {
                        is_intersection = dk_intersection_between(_P_L, pi_m, _pi_r, _Q_R, qi_m, _qi_r);
                    }
                    else
                    {
                        is_intersection = dk_intersection_between(_P_L, _pi_l, pi_m, _Q_R, qi_m, _qi_r);
                    }
                }
            }
            else
            {
                if (ep_y > eq_y)
                {
                    if (v.y > ep_y || v.y > eq_y)  // v, ep, eq construct an upper triangle
                    {
                        is_intersection = dk_intersection_between(_P_L, _pi_l, _pi_r, _Q_R, _qi_l, qi_m);
                    }
                    else
                    {
                        is_intersection = dk_intersection_between(_P_L, _pi_l, pi_m, _Q_R, _qi_l, _qi_r);
                    }
                }
                else
                {
                    // Check is v.y higher any of them
                    if (v.y > ep_y || v.y > eq_y)  // v, ep, eq construct an upper triangle
                    {
                        is_intersection = dk_intersection_between(_P_L, pi_m, _pi_r, _Q_R, _qi_l, _qi_r);
                    }
                    else
                    {
                        is_intersection = dk_intersection_between(_P_L, _pi_l, _pi_r, _Q_R, qi_m, _qi_r);
                    }
                }
            }
        }

        else
        {
            // ep and eq are parallel lines
            if (r3 == CG::RIGHT && r4 == CG::RIGHT)
            {
                if (ep_y > eq_y)
                {
                    is_intersection = dk_intersection_between(_P_L, _pi_l, pi_m - 1, _Q_R, _qi_l, _qi_r);
                }
                else
                {
                    is_intersection = dk_intersection_between(_P_L, pi_m + 1, _pi_r, _Q_R, _qi_l, _qi_r);
                }
            }
            else
                is_intersection = false; // For convex polygon is impossible to intersect in this case
        }

        return is_intersection;
    }

    template<typename T>
    void ConvexHull2D<T>::AddNew(const CG::Point2<T> _pt)
    {}


    template<typename T>
    std::ostream &operator<<(std::ostream &out, const ConvexHull2D<T> &_rhs)
    {
        out << "Extreme points are: ";
        out << _rhs.m_extpts;
    }

}

#endif //COMPUTATIONALGEMOETRY_CONVEXHULL2D_H
