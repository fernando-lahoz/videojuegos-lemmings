#pragma once

#include "../math/math.cpp"
#include "../lib/types.h"
#include "Point.cpp"
#include "Vector.cpp"
#include "Ray.cpp"


template <typename T>
class BoundingBox3
{
    public:
    Point3<T> pMin, pMax;

    BoundingBox3() 
    {
        pMin = Point3<T>(0, 0, 0);
        pMax = Point3<T>(0, 0, 0);
    }

    BoundingBox3(T k)
    {
        pMin = Point3<T>(k);
        pMax = Point3<T>(k);
    }

    BoundingBox3(int k)
    {
        pMin = Point3<T>((T)k);
        pMax = Point3<T>((T)k);
    }
    
    BoundingBox3(const Point3<T> &p) 
        : pMin(p), pMax(p) 
    { }

    BoundingBox3(const Point3<T> &p1, const Point3<T> &p2)
        : pMin(min(p1.x, p2.x), min(p1.y, p2.y),
                min(p1.z, p2.z)),
            pMax(max(p1.x, p2.x), max(p1.y, p2.y),
                max(p1.z, p2.z)) 
    {}

    const Point3<T> &operator[](int i) const
    {
        if (i == 0) 
            return pMin;
        else
            return pMax;
    }

    Point3<T> &operator[](int i)
    {
        if (i == 0) 
            return pMin;
        else
            return pMax;
    }

    bool operator==(const BoundingBox3<T> &b) const {
        return b.pMin == pMin && b.pMax == pMax;
    }

    bool operator!=(const BoundingBox3<T> &b) const {
        return b.pMin != pMin || b.pMax != pMax;
    }

    Point3<T> corner(int corner) const 
    {
        BoundingBox3<T> &this_box = *this;

        return Point3<T>(this_box[(corner & 1)].x,
                        this_box[(corner & 2) ? 1 : 0].y,
                        this_box[(corner & 4) ? 1 : 0].z);
    }

    BoundingBox3<T> operator+(const Point3<T> &p) const 
    {
        return BoundingBox3<T>
            (
                Point3<T>(min(pMin.x, p.x),
                        min(pMin.y, p.y),
                        min(pMin.z, p.z)),
                Point3<T>(max(pMax.x, p.x),
                        max(pMax.y, p.y),
                        max(pMax.z, p.z))
            );
    }

    BoundingBox3<T> operator+(const BoundingBox3<T> &b) const 
    {
        return BoundingBox3<T>
            (
                Point3<T>(min(pMin.x, b.pMin.x),
                        min(pMin.y, b.pMin.y),
                        min(pMin.z, b.pMin.z)),
                Point3<T>(max(pMax.x, b.pMax.x),
                        max(pMax.y, b.pMax.y),
                        max(pMax.z, b.pMax.z))
            );
    }

    BoundingBox3<T> &operator+=(const Point3<T> &p) 
    {
        pMin = Point3<T>(min(pMin.x, p.x),
                        min(pMin.y, p.y),
                        min(pMin.z, p.z));
        pMax = Point3<T>(max(pMax.x, p.x),
                        max(pMax.y, p.y),
                        max(pMax.z, p.z));
        return *this;
    }

    //Operator -
    BoundingBox3<T> operator-(const Point3<T> &p) const 
    {
        return BoundingBox3<T>
            (
                Point3<T>(max(pMin.x, p.x),
                        max(pMin.y, p.y),
                        max(pMin.z, p.z)),
                Point3<T>(min(pMax.x, p.x),
                        min(pMax.y, p.y),
                        min(pMax.z, p.z))
            );
    }

    BoundingBox3<T> operator-(const BoundingBox3<T> &b) const 
    {
        return BoundingBox3<T>
            (
                Point3<T>(max(pMin.x, b.pMin.x),
                        max(pMin.y, b.pMin.y),
                        max(pMin.z, b.pMin.z)),
                Point3<T>(min(pMax.x, b.pMax.x),
                        min(pMax.y, b.pMax.y),
                        min(pMax.z, b.pMax.z))
            );
    }

    BoundingBox3<T> &operator-=(const Point3<T> &p) 
    {
        pMin = Point3<T>(max(pMin.x, p.x),
                        max(pMin.y, p.y),
                        max(pMin.z, p.z));
        pMax = Point3<T>(min(pMax.x, p.x),
                        min(pMax.y, p.y),
                        min(pMax.z, p.z));
        return *this;
    }

    Point3f centroid() const
    {
        return (pMin + pMax) / 2;
    }

    Point3f getUnitCubeCoordinates(Point3f p) const
    {
        Vector3f diagonal = this->diagonal();

        return Point3f((p.x - pMin.x) / diagonal.x,
                        (p.y - pMin.y) / diagonal.y,
                        (p.z - pMin.z) / diagonal.z);
    }

    bool overlaps(const BoundingBox3<T> &b2) 
    {
        bool x = (pMax.x >= b2.pMin.x) && (pMin.x <= b2.pMax.x);
        bool y = (pMax.y >= b2.pMin.y) && (pMin.y <= b2.pMax.y);
        bool z = (pMax.z >= b2.pMin.z) && (pMin.z <= b2.pMax.z);

        return (x && y && z);
    }

    bool contains(const Point3<T> &p) const
    {
        return (p.x >= pMin.x && p.x <= pMax.x &&
                p.y >= pMin.y && p.y <= pMax.y &&
                p.z >= pMin.z && p.z <= pMax.z);
    }

    // Same as contains, but the borders are not included
    bool containsExclusively(const Point3<T> &p) 
    {
        return (p.x >= pMin.x && p.x < pMax.x &&
                p.y >= pMin.y && p.y < pMax.y &&
                p.z >= pMin.z && p.z < pMax.z);
    }

    template <typename U>
    BoundingBox3<T> expand(U delta) 
    {
        return BoundingBox3<T>(pMin - Vector3<T>(delta, delta, delta),
                        pMax + Vector3<T>(delta, delta, delta));
    }

    Vector3<T> diagonal() const { 
        return pMax - pMin; 
    }

    T surfaceArea() const 
    {
        Vector3<T> direction = diagonal();
        return 2 * (direction.x * direction.y + direction.x * direction.z + direction.y * direction.z);
    }

    T volume() const 
    {
        Vector3<T> direction = diagonal();
        return direction.x * direction.y * direction.z;
    }

    int largestAxis() const 
    {
        Vector3<T> direction = diagonal();

        if (direction.x > direction.y && direction.x > direction.z)
            return 0;
        else if (direction.y > direction.z)
            return 1;
        else
            return 2;
    }

    Point3<T> linearInterpolation(const Point3f &t) const 
    {
        return Point3<T>(lerp(t.x, pMin.x, pMax.x), // Lerp is linear interpolate
                        lerp(t.y, pMin.y, pMax.y),
                        lerp(t.z, pMin.z, pMax.z));
    }

    Vector3<T> relativeOffset(const Point3<T> &p) const 
    {
        Vector3<T> origin = p - pMin;

        if (pMax.x > pMin.x)
            origin.x /= pMax.x - pMin.x;

        if (pMax.y > pMin.y) 
            origin.y /= pMax.y - pMin.y;
            
        if (pMax.z > pMin.z) 
            origin.z /= pMax.z - pMin.z;

        return origin;
    }

    void boundingSphere(Point3<T> &center, Float &radius) const 
    {
        center = (pMin + pMax) / 2;

        if (this->contains(center))
            radius = distance(center, pMax);
        else
            radius = 0;
    }

    template <typename U> 
    explicit operator BoundingBox3<U>() const {
        return BoundingBox3<U>((Point3<U>)pMin, (Point3<U>)pMax);
    }

    // Algorithm based on the 2D box slab intersection 
    //  implemented branchless by Tavian Barnes
    inline bool intersects(const Ray &ray, Float &hitOffset) const
    {   
        //if (pMin.isZero() && pMax.isZero())
        //    return true;        

        Float tx1 = (this->pMin.x - ray.origin.x)*ray.invDirection.x;
        Float tx2 = (this->pMax.x - ray.origin.x)*ray.invDirection.x;

        Float tmin = min(tx1, tx2);
        Float tmax = max(tx1, tx2);

        Float ty1 = (this->pMin.y - ray.origin.y)*ray.invDirection.y;
        Float ty2 = (this->pMax.y - ray.origin.y)*ray.invDirection.y;

        tmin = max(tmin, min(ty1, ty2));
        tmax = min(tmax, max(ty1, ty2));

        Float tz1 = (this->pMin.z - ray.origin.z)*ray.invDirection.z;
        Float tz2 = (this->pMax.z - ray.origin.z)*ray.invDirection.z;

        tmin = max(tmin, min(tz1, tz2));
        tmax = min(tmax, max(tz1, tz2));

        // Initialize hitOffset to the minimum distance in case 
        //  there was an intersection
        if (tmin > 0)
            hitOffset = tmin;
        else
            hitOffset = tmax;

        // If the intersection exists, and is positive, and is within the ray's maximum offset
        return tmax >= tmin && hitOffset >= 0 && hitOffset <= ray.maximumOffset;
    }

    inline bool isEmpty() const
    {
        return (pMin.x >= pMax.x || pMin.y >= pMax.y || pMin.z >= pMax.z);
    }

    // Opeerator << for printing
    friend std::ostream &operator<<(std::ostream &os, const BoundingBox3<T> &b) 
    {
        os << "[ " << b.pMin << " - " << b.pMax << " ]";
        return os;
    }

    void print() const
    {
        printf("[ %f %f %f - %f %f %f ]\n", pMin.x, pMin.y, pMin.z, pMax.x, pMax.y, pMax.z);
    }
};



typedef BoundingBox3<Float> Bound3f;
typedef BoundingBox3<int>   Bound3i;



template <typename T>
class BoundingBox2
{
    public:
    Point2<T> pMin, pMax;

    BoundingBox2() 
    {
        pMin = Point2<T>(0, 0);
        pMax = Point2<T>(0, 0);
    }
    
    BoundingBox2(const Point2<T> &p) 
        : pMin(p), pMax(p) 
    { }

    BoundingBox2(const Point2<T> &p1, const Point2<T> &p2)
        : pMin(min(p1.x, p2.x), min(p1.y, p2.y)),
            pMax(max(p1.x, p2.x), max(p1.y, p2.y)) 
    {}

    const Point2<T> &operator[](int i) const
    {
        if (i == 0) 
            return pMin;
        else
            return pMax;
    }

    Point2<T> &operator[](int i)
    {
        if (i == 0) 
            return pMin;
        else
            return pMax;
    }

    bool operator==(const BoundingBox2<T> &b) const {
        return b.pMin == pMin && b.pMax == pMax;
    }

    bool operator!=(const BoundingBox2<T> &b) const {
        return b.pMin != pMin || b.pMax != pMax;
    }

    Point2<T> corner(int corner) const 
    {
        BoundingBox2<T> &this_box = *this;

        return Point2<T>(this_box[(corner & 1)].x,
                        this_box[(corner & 2) ? 1 : 0].y);
    }

    BoundingBox2<T> operator+(const Point2<T> &p) const 
    {
        return BoundingBox2<T>
            (
                Point2<T>(min(pMin.x, p.x),
                        min(pMin.y, p.y)),
                Point2<T>(max(pMax.x, p.x),
                        max(pMax.y, p.y))
            );
    }

    BoundingBox2<T> operator+(const BoundingBox2<T> &b) const 
    {
        return BoundingBox2<T>
            (
                Point2<T>(min(pMin.x, b.pMin.x),
                        min(pMin.y, b.pMin.y)),
                Point2<T>(max(pMax.x, b.pMax.x),
                        max(pMax.y, b.pMax.y))
            );
    }

    BoundingBox2<T> &operator+=(const Point2<T> &p) 
    {
        pMin = Point2<T>(min(pMin.x, p.x),
                        min(pMin.y, p.y));
        pMax = Point2<T>(max(pMax.x, p.x),
                        max(pMax.y, p.y));
        return *this;
    }

    //Operator -
    BoundingBox2<T> operator-(const Point2<T> &p) const 
    {
        return BoundingBox2<T>
            (
                Point2<T>(max(pMin.x, p.x),
                        max(pMin.y, p.y)),
                Point2<T>(min(pMax.x, p.x),
                        min(pMax.y, p.y))
            );
    }

    BoundingBox2<T> operator-(const BoundingBox2<T> &b) const 
    {
        return BoundingBox2<T>
            (
                Point2<T>(max(pMin.x, b.pMin.x),
                        max(pMin.y, b.pMin.y)),
                Point2<T>(min(pMax.x, b.pMax.x),
                        min(pMax.y, b.pMax.y))
            );
    }

    BoundingBox2<T> &operator-=(const Point2<T> &p) 
    {
        pMin = Point2<T>(max(pMin.x, p.x),
                        max(pMin.y, p.y));
        pMax = Point2<T>(min(pMax.x, p.x),
                        min(pMax.y, p.y));
        return *this;
    }

    // Uses exclusive comparisons
    bool overlaps(const BoundingBox2<T> &b2) 
    {
        return (pMin.x < b2.pMax.x &&
            pMax.x > b2.pMin.x &&
            pMin.y < b2.pMax.y &&
            pMax.y > b2.pMin.y);
    }

    bool contains(const Point2<T> &p) const
    {
        return (p.x >= pMin.x && p.x <= pMax.x &&
                p.y >= pMin.y && p.y <= pMax.y);
    }

    // Same as contains, but the borders are not included
    bool containsExclusively(const Point2<T> &p) 
    {
        return (p.x >= pMin.x && p.x < pMax.x &&
                p.y >= pMin.y && p.y < pMax.y);
    }

    template <typename U>
    BoundingBox2<T> expand (U delta) 
    {
        return BoundingBox2<T>(pMin - Vector2<T>(delta, delta),
                        pMax + Vector2<T>(delta, delta));
    }

    Vector2<T> diagonal() const { 
        return pMax - pMin; 
    }

    Float width() const 
    {
        return pMax.x - pMin.x;
    }

    Float height() const 
    {
        return pMax.y - pMin.y;
    }

    T area() const 
    {
        Vector2<T> direction = diagonal();
        return (direction.x * direction.y);
    }

    int largestAxis() const 
    {
        Vector2<T> direction = diagonal();

        if (direction.x > direction.y)
            return 0;
        else
            return 1;
    }

    Point2<T> linearInterpolation(const Point2f &t) const 
    {
        return Point2<T>(lerp(t.x, pMin.x, pMax.x), // Lerp is linear interpolate
                        lerp(t.y, pMin.y, pMax.y));
    }

    Vector2<T> relativeOffset(const Point2<T> &p) const 
    {
        Vector2<T> origin = p - pMin;

        if (pMax.x > pMin.x)
            origin.x /= pMax.x - pMin.x;

        if (pMax.y > pMin.y) 
            origin.y /= pMax.y - pMin.y;

        return origin;
    }

    void boundingSphere(Point2<T> &center, Float &radius) const 
    {
        center = (pMin + pMax) / 2;

        if (this->contains(center))
            radius = distance(center, pMax);
        else
            radius = 0;
    }

    template <typename U> 
    explicit operator BoundingBox2<U>() const {
        return BoundingBox2<U>((Point2<U>)pMin, (Point2<U>)pMax);
    }

    // Algorithm based on the 2D box slab intersection 
    //  implemented branchless by Tavian Barnes
    inline bool intersects(const Ray &ray) const
    {
        Float tx1 = (this->pMin.x - ray.origin.x)*ray.invDirection.x;
        Float tx2 = (this->pMin.x - ray.origin.x)*ray.invDirection.x;

        Float tmin = min(tx1, tx2);
        Float tmax = max(tx1, tx2);

        Float ty1 = (this->pMin.y - ray.origin.y)*ray.invDirection.y;
        Float ty2 = (this->pMax.y - ray.origin.y)*ray.invDirection.y;

        tmin = max(tmin, min(ty1, ty2));
        tmax = min(tmax, max(ty1, ty2));

        return tmax >= tmin;
    }
    

   // OPerator cout
    friend std::ostream &operator<<(std::ostream &os, const BoundingBox2<T> &b) 
    {
        os << "[ " << b.pMin << " - " << b.pMax << " ]";
        return os;
    }

    void print() const
    {
        printf("[ %f %f - %f %f ]\n", pMin.x, pMin.y, pMax.x, pMax.y);
    }
};


typedef BoundingBox2<Float> Bound2f;
typedef BoundingBox2<int>   Bound2i;