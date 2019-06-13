//
// Created by amos on 5/26/19.
//

#ifndef COMPUTATIONALGEMOETRY_EDGE_H
#define COMPUTATIONALGEMOETRY_EDGE_H

#include "Template/type.h"
#include "Point.h"
#include "Vec.h"
#include "Template/Algorithm.h"

namespace CG
{

#define LINE_ERR(x) "Line error: " x


    enum LINE_TYPE
    {
        SEGMENT = 0,
        RAY,
        LINE,
    };

    //=======================================> Line in 2D <=========================================
    template<typename T> // abstract type
    class Line2D
    {
    public:
        Line2D(); //Delete default constructor
        Line2D(Point2<T> _p, Point2<T> _q); //Two point define a line
        Line2D(const Line2D<T> &_rhs); //Copy Constructor
        virtual ~Line2D();

        double Slope(); // Return the slope of this segment
        double Angle(Line2D<T> &_l); //Compute the angle between another segment
        Vec3<T> ToHomo(); // Convert it to homogeneous presentation
        Vec2<T> Dir();// Direction of the ray, present by a unit vector


        LEFT_TEST_RES ToLeftTest(Point2<T> _s); // To left test on specified points

        bool Intersect(Line2D<T> &_l); //Only check whether intersect
        // Check if the two line intersect and return intersection point if possible
        bool Intersect(Line2D<T> &_l, Point2<T> &pt); //
        Line2D<T> &operator=(const Line2D<T> &_rhs);

        template<typename Tf>
        friend std::ostream &operator<<(std::ostream &_out, Line2D<Tf> &_obj);

    public:
        virtual bool is_intersect(Line2D<T> &_l); // Do they intersect with each other?
        // Find potential intersection for all types of lines
        bool potential_intersect_pt(Line2D<T> _l, Point2<T> &pt);

        virtual bool onlineTest(Point2<T> _s); //

    protected:

        // Assume the point is colinear already, return true if _s on the line.
        virtual void print(std::ostream &_out); // Print the line information

    public:
        Point2<T> p;
        Point2<T> q;

        LINE_TYPE type;
    };

    //========================================> Segment 2D<======================================================
    template<typename T>
    class Segment2D : public Line2D<T>
    {
    public:
        Segment2D(); //Delete default constructor
        Segment2D(Point2<T> _p, Point2<T> _q); //Two point define a segment
        Segment2D(const Segment2D<T> &_rhs); //Copy Constructor
        ~Segment2D();

        double Length(); // Return the length of this segment

    public:
        bool is_intersect(Line2D<T> &_l); // Do they intersect with each other?
        // Assume the point is colinear, return true if _s on the segment.
        bool onlineTest(Point2<T> _s);

    protected:
        void print(std::ostream &_out);
    };

    //========================================> Ray 2D <======================================================
    template<typename T>
    class Ray2D : public Line2D<T>
    {
    public:
        Ray2D(); //Delete default constructor
        Ray2D(Point2<T> _p, Point2<T> _q); //Two point define a Ray, _p is the anchor, (_q-_p) define the direction
        Ray2D(const Ray2D<T> &_rhs); //Copy Constructor
        ~Ray2D();

    public:
        bool is_intersect(Line2D<T> &_l); // Do they intersect with each other?
        // Assume the point is colinear already, return true if _s on the line.
        bool onlineTest(Point2<T> _s);

    protected:
        void print(std::ostream &_out);
    };

    /******************************************************************************************
     *
     *                                      Line 2D Implementation
     *
     *****************************************************************************************/
    template<typename T>
    Line2D<T>::Line2D()
    {
        type = CG::LINE;
    }

    template<typename T>
    Line2D<T>::Line2D(Point2<T> _p, Point2<T> _q)
    {
        p = _p;
        q = _q;
        type = CG::LINE;
    }

    template<typename T>
    Line2D<T>::Line2D(const Line2D<T> &_rhs)
    {
        p = _rhs.p;
        q = _rhs.q;
        type = _rhs.type;
    }

    template<typename T>
    Line2D<T>::~Line2D()
    {
    }

    template<typename T>
    LEFT_TEST_RES Line2D<T>::ToLeftTest(Point2<T> _s)
    {
        T detval = p.x * q.y - p.y * q.x
                   + q.x * _s.y - q.y * _s.x
                   + _s.x * p.y - _s.y * p.x;

        if (detval > 0)
        {
            return LEFT;
        }
        else if (detval == 0)
        {
            if (this->onlineTest(_s))
                return COLINEAR_ON;
            else
                return COLINEAR_OUT;
        }
        else
        {
            return RIGHT;
        }
    }

    template<typename T>
    double Line2D<T>::Slope()  // Return the radius, in case of q.x-p.x=0
    {
        return atan2((double) (this->q.y - this->p.y), (double) (this->q.x - this->p.x));
    }

    template<typename T>
    double Line2D<T>::Angle(Line2D<T> &_l)
    {
        double ang1 = this->Slope();
        double ang2 = _l.Slope();

        return ang1 - ang2;
    }

    template<typename T>
    Vec3<T> Line2D<T>::ToHomo()
    {
        Vec3<T> p1(this->p);
        Vec3<T> p2(this->q);

        return p1.cross(p2);
    }


    template<typename T>
    Vec2<T> Line2D<T>::Dir()
    {
        Vec2<T> d;
        Point2<T> dp = this->q - this->p;
        d.x = dp.x;
        d.y = dp.y;
        d.normalisation();

        return d;
    }

    template<typename T>
    bool Line2D<T>::Intersect(Line2D<T> &_l)
    {
        return this->is_intersect(_l);
    }

    template<typename T>
    bool Line2D<T>::Intersect(Line2D<T> &_l, Point2<T> &pt)
    {
        if (!this->is_intersect(_l))
            return false;

        return this->potential_intersect_pt(_l, pt);
    }

    template<typename T>
    bool Line2D<T>::is_intersect(CG::Line2D<T> &_l)
    {
        if (_l.type == CG::LINE)
        {
            // we use homogeneous coordinate to find the intersection of the line in 2D
            Vec3<T> l1 = this->ToHomo();
            Vec3<T> l2 = _l.ToHomo();

            Vec3<T> int_pt = l1.cross(l2); // The intersection point
            if (int_pt.z == 0) // Point at infinity, no intersection! Parralle line
                return false;
            else
                return true;
        }
        else if (_l.type == CG::SEGMENT)
        {
            Segment2D<T> *l = dynamic_cast<Segment2D<T> * >(&_l);
            return l->is_intersect(*this);
        }
        else if (_l.type == CG::RAY)
        {
            Ray2D<T> *l = dynamic_cast<Ray2D<T> * >(&_l);
            return l->is_intersect(*this);
        }
    }

    template<typename T>
    bool Line2D<T>::potential_intersect_pt(Line2D<T> _l, Point2<T> &pt)
    {
        // we use homogeneous coordinate to find the intersection of the line in 2D
        Vec3<T> l1 = this->ToHomo();
        Vec3<T> l2 = _l.ToHomo();

        Vec3<T> int_pt = l1.cross(l2); // The intersection point
        if (int_pt.z == 0) // Point at infinity, no intersection! Parralle line
            return false;

        int_pt /= int_pt.z;
        pt.x = int_pt.x;
        pt.y = int_pt.y;

        return true;
    }

    template<typename T>
    bool Line2D<T>::onlineTest(Point2<T> _s)
    {
        return true;
    }

    template<typename T>
    Line2D<T> &Line2D<T>::operator=(const Line2D<T> &_rhs)
    {
        if (this == &_rhs)
            return *this;

        this->p = _rhs.p;
        this->q = _rhs.q;
        this->type = _rhs.type;

        return *this;
    }

    template<typename T>
    void Line2D<T>::print(std::ostream &_out)
    {
        _out << "Line: ";
    }

    template<typename T>
    std::ostream &operator<<(std::ostream &_out, Line2D<T> &_obj)
    {
        _obj.print(_out);
        _out << "{" << _obj.p << ", " << _obj.q << "}";
    }


    /******************************************************************************************
     *
     *                                Segment 2D Implementation
     *
     *****************************************************************************************/
    // Implementation
    template<typename T>
    Segment2D<T>::Segment2D()
            :Line2D<T>()
    {
        this->type = CG::SEGMENT;
    }

    template<typename T>
    Segment2D<T>::Segment2D(Point2<T> _p, Point2<T> _q)
            :Line2D<T>(_p, _q)
    {
        this->type = CG::SEGMENT;
    }

    template<typename T>
    Segment2D<T>::Segment2D(const Segment2D<T> &_rhs)
            :Line2D<T>(_rhs)
    {}

    template<typename T>
    Segment2D<T>::~Segment2D()
    {}


    template<typename T>
    double Segment2D<T>::Length()
    {
        double dx = this->q.x - this->p.x;
        double dy = this->q.y - this->p.y;

        return sqrt(dx * dx + dy * dy);
    }

    template<typename T>
    bool Segment2D<T>::is_intersect(Line2D<T> &_l)
    {
        LEFT_TEST_RES r1, r2, r3, r4;

        // They might have intersection
        if (_l.type == CG::SEGMENT)
        {
            Segment2D<T> *l = dynamic_cast<Segment2D<T> *>(&_l);
            r1 = this->ToLeftTest(_l.p);
            r2 = this->ToLeftTest(_l.q);
            r3 = l->ToLeftTest(this->p);
            r4 = l->ToLeftTest(this->q);

            if (r1 == CG::COLINEAR_ON || r2 == CG::COLINEAR_ON || r3 == CG::COLINEAR_ON || r4 == CG::COLINEAR_ON)
                return true;

            if (r1 == r2 || r3 == r4)
                return false;
            else
                return true;
        }
        else if (_l.type == CG::RAY)
        {
            Ray2D<T> *l = dynamic_cast<Ray2D<T> *>(&_l);
            r1 = this->ToLeftTest(_l.p); // Test the anchor point of the ray.

            r3 = l->ToLeftTest(this->p);
            r4 = l->ToLeftTest(this->q);
            if (r1 == CG::COLINEAR_ON || r3 == CG::COLINEAR_ON || r4 == CG::COLINEAR_ON)
                return true;

            if (r3 == r4 || r3 == CG::COLINEAR_OUT || r4 == CG::COLINEAR_OUT)
                return false;

            // It might intersect, but we need to judge according to the anchor point and direction of the ray
            //  Check the possible intersection point, then test it on the ray or not.
            Point2<T> int_pt;
            if (!this->potential_intersect_pt(_l,
                                              int_pt)) //Still do parallel check, but it should always return true in here
                return false;

            return l->onlineTest(int_pt);
        }
        else if (_l.type == CG::LINE)
        {
            r3 = _l.ToLeftTest(this->p);
            r4 = _l.ToLeftTest(this->q);

            if (r3 == CG::COLINEAR_ON || r4 == CG::COLINEAR_ON)
                return true;

            if (r3 == r4)
                return false;

            return true;
        }
    }

    template<typename T>
    bool Segment2D<T>::onlineTest(CG::Point2<T> _s)
    {
        if (this->p.x != this->q.x)
        {
            return CG::between(this->p.x, this->q.x, _s.x);
        }
        else // If this is vertical segment
        {
            return CG::between(this->p.y, this->q.y, _s.y);
        }
    }

    template<typename T>
    void Segment2D<T>::print(std::ostream &_out)
    {
        _out << "Segment: ";
    }


    /******************************************************************************************
    *
    *                                      Ray 2D Implementation
    *
    *****************************************************************************************/
    template<typename T>
    Ray2D<T>::Ray2D()
            :Line2D<T>()
    {
        this->type = CG::RAY;
    }

    template<typename T>
    Ray2D<T>::Ray2D(Point2<T> _p, Point2<T> _q)
            :Line2D<T>(_p, _q)
    {
        this->type = CG::RAY;
    }

    template<typename T>
    Ray2D<T>::Ray2D(const Ray2D<T> &_rhs)
            :Line2D<T>(_rhs)
    {}

    template<typename T>
    Ray2D<T>::~Ray2D()
    {}

    template<typename T>
    bool Ray2D<T>::onlineTest(CG::Point2<T> _s)
    {
        if (this->p.x != this->q.x)
        {
            // Ray point to right
            if (this->q.x > this->p.x)
            {
                return _s.x > this->p.x;
            }
            else
            {
                return _s.x < this->p.x;
            }
        }
        else
        {
            // Ray point to up
            if (this->q.y > this->p.y)
            {
                return _s.y > this->p.y;
            }
            else
            {
                return _s.y < this->p.y;
            }
        }
    }

    template<typename T>
    bool Ray2D<T>::is_intersect(Line2D<T> &_l)
    {
        LEFT_TEST_RES r1, r2;
        if (_l.type == CG::SEGMENT)
        {
            Segment2D<T> *l = dynamic_cast<Segment2D<T> * >(&_l);
            return l->is_intersect(*this);
        }
        else if (_l.type == CG::RAY)
        {
            Ray2D<T> *l = dynamic_cast<Ray2D<T> * >(&_l);

            // Test whether the anchor point is
            r1 = this->ToLeftTest(l->p);
            r2 = l->ToLeftTest(this->p);

            if (r1 == CG::COLINEAR_ON || r2 == CG::COLINEAR_ON)
                return true;

            Point2<T> int_pt;
            if (!this->potential_intersect_pt(_l, int_pt)) // If the two ray are parallel
                return false;

            // if the intersection point is on both ray, then they surely have intersection
            return this->onlineTest(int_pt) & l->onlineTest(int_pt);
        }
        else if (_l.type == CG::LINE)
        {
            r1 = _l.ToLeftTest(this->p);
            if (r1 == CG::COLINEAR_ON) // if the anchor point of the ray lay on the line, then we done!
                return true;

            Point2<T> int_pt;
            if (!this->potential_intersect_pt(_l, int_pt))// Ray and line are parallel
                return false;

            return this->onlineTest(int_pt);
        }

    }


    template<typename T>
    void Ray2D<T>::print(std::ostream &_out)
    {
        _out << "Ray: ";
    }
}

#endif //COMPUTATIONALGEMOETRY_EDGE_H
