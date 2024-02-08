#pragma once
#include "../lib/types.h"
#include "../math/math.cpp"
#include "Vector.cpp"

template <typename T>
class Point3
{
    public:
    T x, y, z;

    Point3() 
    { 
        x = 0;
        y = 0;
        z = 0; 
    }

    Point3(T x, T y, T z) : x(x), y(y), z(z) {
        assert(!hasNaNs());
    }

    Point3(const Point3<T> &p) 
    {
        assert(!p.hasNaNs());

        x = p.x; 
        y = p.y; 
        z = p.z;
    }

    explicit Point3(const Vector3<T> &v)
    {
        assert(!v.hasNaNs());

        x = v.x; 
        y = v.y; 
        z = v.z;
    }

    // Construct a vector with a point
    Vector3<T> toVector() const {
        return Vector3<T>(x, y, z);
    }
    
    Point3<T> &operator=(const Point3<T> &p) 
    {
        assert(!p.hasNaNs());
        x = p.x; 
        y = p.y; 
        z = p.z;

        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Point3<T> &p) 
    {
        Point3<T> p2 = p;

        if (abs(p2.x) < FLOAT_ERROR_MARGIN)
            p2.x = 0;

        if (abs(p2.y) < FLOAT_ERROR_MARGIN)
            p2.y = 0;
        
        if (abs(p2.z) < FLOAT_ERROR_MARGIN)
            p2.z = 0;


        os << "point[" << p2.x << ", " << p2.y << ", " << p2.z << "]";
        return os;
    }

    Point3<T> operator+(const Vector3<T> &v) const {
        return Point3<T>(x + v.x, y + v.y, z + v.z);
    }

    Point3<T> &operator+=(const Vector3<T> &v) 
    {
        x += v.x; 
        y += v.y; 
        z += v.z;

        return *this;
    }

    Vector3<T> operator-(const Point3<T> &p) const {
        return Vector3<T>(x - p.x, y - p.y, z - p.z);
    }

    Point3<T> operator-(const Vector3<T> &v) const {
        return Point3<T>(x - v.x, y - v.y, z - v.z);
    }

    Point3<T> &operator-=(const Vector3<T> &v) 
    {
        x -= v.x; 
        y -= v.y; 
        z -= v.z;

        return *this;
    }

    Point3<T> &operator+=(const Point3<T> &p) 
    {
        x += p.x; 
        y += p.y; 
        z += p.z;

        return *this;
    }

    Point3<T> operator+(const Point3<T> &p) const {
        return Point3<T>(x + p.x, y + p.y, z + p.z);
    }

    Point3<T> operator*(T f) const {
        return Point3<T>(f*x, f*y, f*z);
    }

    Point3<T> &operator*=(T f) 
    {
        x *= f; 
        y *= f; 
        z *= f;

        return *this;
    }

    Point3<T> operator/(T f) const 
    {
        Float inv = (Float)1 / f;
        return Point3<T>(inv*x, inv*y, inv*z);
    }

    Point3<T> &operator/=(T f) 
    {
        Float inv = (Float)1 / f;
        x *= inv; 
        y *= inv; 
        z *= inv;

        return *this;
    }

    T operator[](int i) const 
    { 
        assert(i >= 0 && i <= 2);

        if (i == 0) 
            return x;
        else if (i == 1) 
            return y;
        else 
            return z;
    }
    
    T &operator[](int i) 
    { 
        assert(i >= 0 && i <= 2);

        if (i == 0) 
            return x;
        else if (i == 1) 
            return y;
        else 
            return z;

        return z;
    }

    inline bool isZero() const {
        return x == 0 && y == 0 && z == 0;
    }

    inline bool operator==(const Point3<T> &p) const {
        return x == p.x && y == p.y && z == p.z;
    }

    inline bool operator!=(const Point3<T> &p) const {
        return x != p.x || y != p.y || z != p.z;
    }

    inline bool hasNaNs() const {
        return isNaN(x) || isNaN(y) || isNaN(z);
    }

    bool hasInf() const {
        return isInf(x) || isInf(y);
    }

    inline Point3<T> operator-() const { 
        return Point3<T>(-x, -y, -z); 
    }

    void print() const {
        printf("point[%f, %f, %f]\n", x, y, z);
    }
};

typedef Point3<Float> Point3f;
typedef Point3<int>   Point3i;

template <typename T>
inline Float distance(const Point3<T> &p1, const Point3<T> &p2) {
    return (p1 - p2).length();
}

template <typename T>
inline Float distanceSquared(const Point3<T> &p1, const Point3<T> &p2) {
    return (p1 - p2).lengthSquared();
}


template <typename T>
class Point2
{
    public:

    T x, y;

    explicit Point2(const Point3<T> &p) 
    : x(p.x), y(p.y) 
    {
        assert(!hasNaNs());
    }

    Point2() 
    { 
        x = 0;
        y = 0; 
    }
    
    Point2(T xx, T yy)
        : x(xx), y(yy) {
        assert(!hasNaNs());
    }
    
    Point2(const Point2<T> &p) 
    {
        assert(!p.hasNaNs());
        x = p.x; 
        y = p.y;
    }

    Point2 (const Vector2<T> &v)
    {
        assert(!v.hasNaNs());
        x = v.x; 
        y = v.y;
    }

    template <typename U>
    Point2 (const Point2<U> &p)
    {
        assert(!p.hasNaNs());
        x = (T)p.x; 
        y = (T)p.y;
    }

    // Construct a vector with a point
    Vector2<T> toVector() const
    {
        return Vector2<T>(x, y);
    }

    bool isZero() const {
        return x == 0 && y == 0;
    }

    
    Point2<T> &operator=(const Point2<T> &p) 
    {
        assert(!p.hasNaNs());
        x = p.x; 
        y = p.y;

        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Point2<T> &p) 
    {
        Point2<T> p2 = p;

        if (abs(p2.x) < FLOAT_ERROR_MARGIN)
            p2.x = 0;
        
        if (abs(p2.y) < FLOAT_ERROR_MARGIN)
            p2.y = 0;

        os << "point[" << p2.x << ", " << p2.y << "]";
        return os;
    }

    
    Point2<T> operator+(const Vector2<T> &v) const 
    {
        assert(!v.hasNaNs());
        return Point2<T>(x + v.x, y + v.y);
    }

    
    Point2<T> &operator+=(const Vector2<T> &v) 
    {
        assert(!v.hasNaNs());
        x += v.x; 
        y += v.y;

        return *this;
    }

    Vector2<T> operator-(const Point2<T> &p) const 
    {
        assert(!p.hasNaNs());
        return Vector2<T>(x - p.x, y - p.y);
    }
    
    Point2<T> operator-(const Vector2<T> &v) const 
    {
        assert(!v.hasNaNs());
        return Point2<T>(x - v.x, y - v.y);
    }

    Point2<T> operator-() const { 
        return Point2<T>(-x, -y);
    }

    Point2<T> operator-(const T &f) const 
    {
        return Point2<T>(x - f, y - f);
    }

    Point2<T> &operator-=(const Vector2<T> &v) 
    {
        assert(!v.hasNaNs());
        x -= v.x; 
        y -= v.y;

        return *this;
    }

    Point2<T> &operator+=(const Point2<T> &p) 
    {
        assert(!p.hasNaNs());
        x += p.x; 
        y += p.y;

        return *this;
    }

    Point2<T> operator+(const Point2<T> &p) const 
    {
        assert(!p.hasNaNs());
        return Point2<T>(x + p.x, y + p.y);
    }

    // + operator with int
    Point2<T> operator+(const int &f) const 
    {
        return Point2<T>(x + f, y + f);
    }

    Point2<T> operator* (T f) const {
        return Point2<T>(f*x, f*y);
    }

    Point2<T> &operator*=(T f) 
    {
        x *= f; 
        y *= f;

        return *this;
    }

    Point2<T> operator/ (T f) const 
    {
        Float inv = (Float)1 / f;
        return Point2<T>(inv*x, inv*y);
    }

    Point2<T> &operator/=(T f) 
    {
        Float inv = (Float)1 / f;
        x *= inv; 
        y *= inv;

        return *this;
    }

    T operator[](int i) const 
    {
        assert(i >= 0 && i <= 1);

        if (i == 0) 
            return x;
        else 
            return y;
    }
    
    T &operator[](int i) 
    {
        assert(i >= 0 && i <= 1);

        if (i == 0) 
            return x;
        else
            return y;
    }

    bool operator==(const Point2<T> &p) const {
        return x == p.x && y == p.y;
    }

    bool operator!=(const Point2<T> &p) const {
        return x != p.x || y != p.y;
    }

    bool hasNaNs() const {
        return isNaN(x) || isNaN(y);
    }

    bool hasInf() const {
        return isInf(x) || isInf(y);
    }
};

typedef Point2<Float> Point2f;
typedef Point2<int>   Point2i;

template <typename T>
inline Float distance(const Point2<T> &p1, const Point2<T> &p2) {
    return (p1 - p2).length();
}

template <typename T>
inline Float distanceSquared(const Point2<T> &p1, const Point2<T> &p2) {
    return (p1 - p2).lengthSquared();
}

// pow
inline Point2f pow2(const Point2f &p) {
    return Point2f(p.x*p.x, p.y*p.y);
}

Point2f operator*(Float f, const Point2f &p) {
    assert(!p.hasNaNs());
    return p*f;
}
Point3f operator*(Float f, const Point3f &p) {
    assert(!p.hasNaNs());
    return p*f;
}

// Inverse - operato
Point2f operator-(Float f, const Point2f &p) {
    assert(!p.hasNaNs());
    return Point2f(f - p.x, f - p.y);
}


// Inverse - operato
Point2f operator*(Point2f p1, const Point2f &p2) {
    assert(!p1.hasNaNs());
    assert(!p2.hasNaNs());
    return Point2f(p1.x * p2.x, p1.y * p2.y);
}

// Inverse / operato
Point2f operator/(Float f, const Point2f &p) {
    assert(!p.hasNaNs());
    return Point2f(f / p.x, f / p.y);
}
