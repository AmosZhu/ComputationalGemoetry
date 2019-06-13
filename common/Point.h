//
// Created by amos on 5/25/19.
//

#ifndef COMPUTATIONALGEMOETRY_POINT_H
#define COMPUTATIONALGEMOETRY_POINT_H

#include <iostream>
#include <math.h>

namespace CG //Computational Geometry
{
    template<typename T>
    class Point2
    {
    public:
        Point2(); //Default Constructor
        Point2(T _x, T _y); // Second Constructor
        Point2(const Point2<T> &_rhs); //Copy Constructor
        virtual ~Point2();

        double Distance(Point2<T> _p); // Distance between these two points

        // Operator to make life easier
        Point2<T> &operator=(const Point2<T> &_rhs);

        Point2<T> operator+(const Point2<T> &_rhs);

        Point2<T> operator+(T _val);

        Point2<T> operator-(const Point2<T> &_rhs);

        Point2<T> operator-(T _val);

        Point2<T> &operator+=(const Point2<T> &_rhs);

        Point2<T> &operator+=(T _val);

        Point2<T> &operator-=(const Point2<T> &_rhs);

        Point2<T> &operator-=(T _val);

        Point2<T> operator/(T _val);

        Point2<T> &operator/=(T _val);

        // Freinds
        template<typename Tf>
        friend std::ostream &operator<<(std::ostream &out, const Point2<Tf> &_rhs);

        template<typename T1, typename T2>
        friend Point2<T1> operator*(const Point2<T1> &_rhs, T2 _val);

        template<typename T1, typename T2>
        friend Point2<T1> operator*(T2 _val, const Point2<T1> &_rhs);


    public:
        T x;
        T y;
    };


// Implementation
    template<typename T>
    Point2<T>::Point2()
    {
        x = 0;
        y = 0;
    }

    template<typename T>
    Point2<T>::Point2(T _x, T _y)
            :x(_x), y(_y)
    {
    }

    template<typename T>
    Point2<T>::Point2(const Point2 &_rhs)
    {
        x = _rhs.x;
        y = _rhs.y;
    }

    template<typename T>
    Point2<T>::~Point2()
    {
    }

    template<typename T>
    double Point2<T>::Distance(CG::Point2<T> _p)
    {
        double dx = x - _p.x;
        double dy = y - _p.y;

        return sqrt(dx * dx + dy * dy);
    }

    template<typename T>
    Point2<T> &Point2<T>::operator=(const Point2<T> &_rhs)
    {
        if (this == &_rhs)
            return *this;

        x = _rhs.x;
        y = _rhs.y;

        return *this;
    }

    template<typename T>
    Point2<T> Point2<T>::operator+(const Point2<T> &_rhs)
    {
        if (&_rhs == nullptr)
            return *this;

        Point2<T> res;

        res.x = x + _rhs.x;
        res.y = y + _rhs.y;

        return res;
    }

    template<typename T>
    Point2<T> Point2<T>::operator+(T _val)
    {
        if (&_val == nullptr)
            return *this;

        Point2<T> res;

        res.x = x + _val;
        res.y = y + _val;

        return res;
    }

    template<typename T>
    Point2<T> Point2<T>::operator-(const Point2<T> &_rhs)
    {
        if (&_rhs == nullptr)
            return *this;

        Point2<T> res;

        res.x = x - _rhs.x;
        res.y = y - _rhs.y;

        return res;
    }

    template<typename T>
    Point2<T> Point2<T>::operator-(T _val)
    {
        if (&_val == nullptr)
            return *this;

        Point2<T> res;

        res.x = x - _val;
        res.y = y - _val;

        return res;
    }

    template<typename T>
    Point2<T> &Point2<T>::operator+=(const Point2<T> &_rhs)
    {
        if (&_rhs == nullptr)
            return *this;


        x += _rhs.x;
        y += _rhs.y;

        return *this;
    }

    template<typename T>
    Point2<T> &Point2<T>::operator+=(T _val)
    {
        if (&_val == nullptr)
            return *this;

        x += _val;
        y += _val;

        return *this;
    }

    template<typename T>
    Point2<T> &Point2<T>::operator-=(const Point2<T> &_rhs)
    {
        if (&_rhs == nullptr)
            return *this;


        x -= _rhs.x;
        y -= _rhs.y;

        return *this;
    }

    template<typename T>
    Point2<T> &Point2<T>::operator-=(T _val)
    {
        if (&_val == nullptr)
            return *this;

        x -= _val;
        y -= _val;

        return *this;
    }

    template<typename T>
    Point2<T> Point2<T>::operator/(T _val)
    {
        if (&_val == nullptr)
            return *this;

        Point2<T> res;

        res.x = x / _val;
        res.y = y / _val;

        return res;
    }

    template<typename T>
    Point2<T> &Point2<T>::operator/=(T _val)
    {
        if (&_val == nullptr)
            return *this;

        x /= _val;
        y /= _val;

        return *this;
    }

    template<typename T>
    std::ostream &operator<<(std::ostream &out, const Point2<T> &_rhs)
    {
        out << "(" << _rhs.x << ", " << _rhs.y << ")";

        return out;
    }

    template<typename T1, typename T2>
    Point2<T1> operator*(const Point2<T1> &_rhs, T2 _val)
    {
        Point2<T1> res;
        res.x = (T1) _val * _rhs.x;
        res.y = (T1) _val * _rhs.y;

        return res;
    }

    template<typename T1, typename T2>
    Point2<T1> operator*(T2 _val, const Point2<T1> &_rhs)
    {
        return _rhs * _val;
    }

    //-----------------------------------> Point 3D <--------------------------------------//
    template<typename T>
    class Point3
    {
    public:
        Point3(); //Default Constructor
        Point3(T _x, T _y, T _z); // Second Constructor
        Point3(const Point3<T> &_rhs); //Copy Constructor
        virtual ~Point3();

        double Distance(Point3<T> _p); // Distance between these two points

        // Operator to make life easier
        Point3<T> &operator=(const Point3<T> &_rhs);

        Point3<T> operator+(const Point3<T> &_rhs);

        Point3<T> operator+(T _val);

        Point3<T> operator-(const Point3<T> &_rhs);

        Point3<T> operator-(T _val);

        Point3<T> &operator+=(const Point3<T> &_rhs);

        Point3<T> &operator+=(T _val);

        Point3<T> &operator-=(const Point3<T> &_rhs);

        Point3<T> &operator-=(T _val);

        Point3<T> operator/(T _val);

        Point3<T> &operator/=(T _val);

        template<typename Tf>
        friend std::ostream &operator<<(std::ostream &out, const Point3<Tf> &_rhs);

    public:
        T x;
        T y;
        T z;
    };

    template<typename T>
    Point3<T>::Point3()
    {
        x = 0;
        y = 0;
        z = 0;
    }

    template<typename T>
    Point3<T>::Point3(T _x, T _y, T _z)
            :x(_x), y(_y), z(_z)
    {
    }

    template<typename T>
    Point3<T>::Point3(const Point3 &_rhs)
    {
        x = _rhs.x;
        y = _rhs.y;
        z = _rhs.z;
    }

    template<typename T>
    Point3<T>::~Point3()
    {
    }

    template<typename T>
    double Point3<T>::Distance(CG::Point3<T> _p)
    {
        double dx = x - _p.x;
        double dy = y - _p.y;
        double dz = z - _p.z;

        return sqrt(dx * dx + dy * dy + dz * dz);
    }

    template<typename T>
    Point3<T> &Point3<T>::operator=(const Point3<T> &_rhs)
    {
        if (this == &_rhs)
            return *this;

        x = _rhs.x;
        y = _rhs.y;
        z = _rhs.z;

        return *this;
    }

    template<typename T>
    Point3<T> Point3<T>::operator+(const Point3<T> &_rhs)
    {
        if (&_rhs == nullptr)
            return *this;

        Point3<T> res;

        res.x = x + _rhs.x;
        res.y = y + _rhs.y;
        res.z = z + _rhs.z;

        return res;
    }

    template<typename T>
    Point3<T> Point3<T>::operator+(T _val)
    {
        if (&_val == nullptr)
            return *this;

        Point3<T> res;

        res.x = x + _val;
        res.y = y + _val;
        res.z = z + _val;

        return res;
    }

    template<typename T>
    Point3<T> Point3<T>::operator-(const Point3<T> &_rhs)
    {
        if (&_rhs == nullptr)
            return *this;

        Point3<T> res;

        res.x = x - _rhs.x;
        res.y = y - _rhs.y;
        res.z = z - _rhs.z;

        return res;
    }

    template<typename T>
    Point3<T> Point3<T>::operator-(T _val)
    {
        if (&_val == nullptr)
            return *this;

        Point3<T> res;

        res.x = x - _val;
        res.y = y - _val;
        res.z = z - _val;

        return res;
    }

    template<typename T>
    Point3<T> &Point3<T>::operator+=(const Point3<T> &_rhs)
    {
        if (&_rhs == nullptr)
            return *this;


        x += _rhs.x;
        y += _rhs.y;
        z += _rhs.z;

        return *this;
    }

    template<typename T>
    Point3<T> &Point3<T>::operator+=(T _val)
    {
        if (&_val == nullptr)
            return *this;

        x += _val;
        y += _val;
        z += _val;

        return *this;
    }

    template<typename T>
    Point3<T> &Point3<T>::operator-=(const Point3<T> &_rhs)
    {
        if (&_rhs == nullptr)
            return *this;

        x -= _rhs.x;
        y -= _rhs.y;
        z -= _rhs.z;

        return *this;
    }

    template<typename T>
    Point3<T> &Point3<T>::operator-=(T _val)
    {
        if (&_val == nullptr)
            return *this;

        x -= _val;
        y -= _val;
        z -= _val;

        return *this;
    }

    template<typename T>
    Point3<T> Point3<T>::operator/(T _val)
    {
        if (&_val == nullptr)
            return *this;

        Point3<T> res;

        res.x = x / _val;
        res.y = y / _val;
        res.z = z / _val;

        return res;
    }

    template<typename T>
    Point3<T> &Point3<T>::operator/=(T _val)
    {
        if (&_val == nullptr)
            return *this;

        x /= _val;
        y /= _val;
        z /= _val;

        return *this;
    }

    template<typename T>
    std::ostream &operator<<(std::ostream &out, const Point3<T> &_rhs)
    {
        out << "(" << _rhs.x << ", " << _rhs.y << ", " << _rhs.z << ")";

        return out;
    }
}


#endif //COMPUTATIONALGEMOETRY_POINT_H
