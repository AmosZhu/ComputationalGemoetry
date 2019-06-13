//
// Created by root on 5/31/19.
//

#ifndef COMPUTATIONALGEMOETRY_VEC_H
#define COMPUTATIONALGEMOETRY_VEC_H

#include "Point.h"
#include <math.h>

namespace CG
{
    // -------------------------> Vector in 2D <--------------------------------------
    template<typename T>
    class Vec2 : public Point2<T>
    {
    public:
        Vec2(); // Default constructor
        Vec2(T _x, T _y); // Second Constructor
        Vec2(const Vec2<T> &_rhs); //Copy Constructor
        ~Vec2();

        double norm(); // Return the norm of the vector
        void normalisation();

        double Angle(Vec2<T> _v); // Compute the angle with another vector, return the radius
    };

    template<typename T>
    Vec2<T>::Vec2()
            :Point2<T>()
    {}

    template<typename T>
    Vec2<T>::Vec2(T _x, T _y)
            :Point2<T>(_x, _y)
    {}

    template<typename T>
    Vec2<T>::Vec2(const Vec2<T> &_rhs)
            :Point2<T>(_rhs)
    {}

    template<typename T>
    Vec2<T>::~Vec2()
    {}

    template<typename T>
    double Vec2<T>::norm()
    {
        return sqrt(double(this->x * this->x) + double(this->y * this->y));
    }

    template<typename T>
    void Vec2<T>::normalisation()
    {
        double denorm = this->norm();
        *this /= denorm;
    }

    template<typename T>
    double Vec2<T>::Angle(Vec2<T> _v)
    {
        Vec2<T> v1(*this);
        Vec2<T> v2(_v);

        v1.normalisation();
        v2.normalisation();

        return acos((double) (v1.x * v2.x + v1.y + v2.y));
    }


    // ===========================> Vector in 3D <=================================
    template<typename T>
    class Vec3 : public Point3<T>
    {
    public:
        Vec3(); // Default constructor
        Vec3(T _x, T _y, T _z); // Second Constructor
        Vec3(Point2 <T> _p); // Set the z=1 in this case
        Vec3(const Vec3<T> &_rhs); //Copy Constructor
        ~Vec3();

        double norm(); // Return the norm of the vector
        void normalisation();

        double dot(Vec3<T> _v); // dot product
        Vec3<T> cross(Vec3<T> _v); // cross product
        double Angle(Vec3<T> _v); // Compute the angle with another vector, return the radius
    };

    template<typename T>
    Vec3<T>::Vec3()
            :Point3<T>()
    {}

    template<typename T>
    Vec3<T>::Vec3(T _x, T _y, T _z)
            :Point3<T>(_x, _y, _z)
    {}

    template<typename T>
    Vec3<T>::Vec3(Point2 <T> _p)
    {
        this->x = _p.x;
        this->y = _p.y;
        this->z = 1;
    }

    template<typename T>
    Vec3<T>::Vec3(const CG::Vec3<T> &_rhs)
            :Point3<T>(_rhs)
    {}

    template<typename T>
    Vec3<T>::~Vec3()
    {}

    template<typename T>
    double Vec3<T>::norm()
    {
        return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
    }

    template<typename T>
    void Vec3<T>::normalisation()
    {
        double denorm = this->norm();
        *this /= denorm;
    }

    template<typename T>
    double Vec3<T>::dot(Vec3<T> _v)
    {
        return this->x * _v.x + this->y * _v.y + this->z * _v.z;
    }

    template<typename T>
    Vec3<T> Vec3<T>::cross(Vec3<T> _v)
    {
        Vec3<T> res;
        res.x = this->y * _v.z - this->z * _v.y;
        res.y = this->z * _v.x - this->x * _v.z;
        res.z = this->x * _v.y - this->y * _v.x;

        return res;
    }


    template<typename T>
    double Vec3<T>::Angle(CG::Vec3<T> _v)
    {
        Vec3<T> v1(*this);
        Vec3<T> v2(_v);

        v1.normalisation();
        v2.normalisation();

        return acos(v1.dot(v2));
    }

}

#endif //COMPUTATIONALGEMOETRY_VEC_H
