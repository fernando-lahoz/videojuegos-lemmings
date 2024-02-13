#pragma once 
#include "geometry/bounding_box.hpp"

template <typename T>
constexpr BoundingBox3<T>::BoundingBox3() 
{
    pMin = Point3<T>(0, 0, 0);
    pMax = Point3<T>(0, 0, 0);
}

template <typename T>
constexpr BoundingBox3<T>::BoundingBox3(T k)
{
    pMin = Point3<T>(k);
    pMax = Point3<T>(k);
}

template <typename T>
constexpr BoundingBox3<T>::BoundingBox3(const Point3<T> &p) 
    : pMin(p), pMax(p) 
{ }

template <typename T>
constexpr BoundingBox3<T>::BoundingBox3(const Point3<T> &p1, const Point3<T> &p2)
    : pMin(std::min(p1.x, p2.x), std::min(p1.y, p2.y),
            std::min(p1.z, p2.z)),
        pMax(std::max(p1.x, p2.x), std::max(p1.y, p2.y),
            std::max(p1.z, p2.z)) 
{}

template <typename T>
constexpr const Point3<T> &BoundingBox3<T>::operator[](int i) const
{
    if (i == 0) 
        return pMin;
    else
        return pMax;
}

template <typename T>
constexpr Point3<T> &BoundingBox3<T>::operator[](int i)
{
    if (i == 0) 
        return pMin;
    else
        return pMax;
}

template <typename T>
constexpr bool BoundingBox3<T>::operator==(const BoundingBox3<T> &b) const {
    return b.pMin == pMin && b.pMax == pMax;
}

template <typename T>
constexpr bool BoundingBox3<T>::operator!=(const BoundingBox3<T> &b) const {
    return b.pMin != pMin || b.pMax != pMax;
}

template <typename T>
constexpr Point3<T> BoundingBox3<T>::corner(int corner) const 
{
    BoundingBox3<T> &this_box = *this;

    return Point3<T>(this_box[(corner & 1)].x,
                    this_box[(corner & 2) ? 1 : 0].y,
                    this_box[(corner & 4) ? 1 : 0].z);
}

template <typename T>
constexpr BoundingBox3<T> BoundingBox3<T>::operator+(const Point3<T> &p) const 
{
    return BoundingBox3<T>
        (
            Point3<T>(std::min(pMin.x, p.x),
                    std::min(pMin.y, p.y),
                    std::min(pMin.z, p.z)),
            Point3<T>(std::max(pMax.x, p.x),
                    std::max(pMax.y, p.y),
                    std::max(pMax.z, p.z))
        );
}

template <typename T>
constexpr BoundingBox3<T> BoundingBox3<T>::operator+(const BoundingBox3<T> &b) const 
{
    return BoundingBox3<T>
        (
            Point3<T>(std::min(pMin.x, b.pMin.x),
                    std::min(pMin.y, b.pMin.y),
                    std::min(pMin.z, b.pMin.z)),
            Point3<T>(std::max(pMax.x, b.pMax.x),
                    std::max(pMax.y, b.pMax.y),
                    std::max(pMax.z, b.pMax.z))
        );
}

template <typename T>
constexpr BoundingBox3<T> &BoundingBox3<T>::operator+=(const Point3<T> &p) 
{
    pMin = Point3<T>(std::min(pMin.x, p.x),
                    std::min(pMin.y, p.y),
                    std::min(pMin.z, p.z));
    pMax = Point3<T>(std::max(pMax.x, p.x),
                    std::max(pMax.y, p.y),
                    std::max(pMax.z, p.z));
    return *this;
}

//Operator -
template <typename T>
constexpr BoundingBox3<T> BoundingBox3<T>::operator-(const Point3<T> &p) const 
{
    return BoundingBox3<T>
        (
            Point3<T>(std::max(pMin.x, p.x),
                    std::max(pMin.y, p.y),
                    std::max(pMin.z, p.z)),
            Point3<T>(std::min(pMax.x, p.x),
                    std::min(pMax.y, p.y),
                    std::min(pMax.z, p.z))
        );
}

template <typename T>
constexpr BoundingBox3<T> BoundingBox3<T>::operator-(const BoundingBox3<T> &b) const 
{
    return BoundingBox3<T>
        (
            Point3<T>(std::max(pMin.x, b.pMin.x),
                    std::max(pMin.y, b.pMin.y),
                    std::max(pMin.z, b.pMin.z)),
            Point3<T>(std::min(pMax.x, b.pMax.x),
                    std::min(pMax.y, b.pMax.y),
                    std::min(pMax.z, b.pMax.z))
        );
}

template <typename T>
constexpr BoundingBox3<T> &BoundingBox3<T>::operator-=(const Point3<T> &p) 
{
    pMin = Point3<T>(std::max(pMin.x, p.x),
                    std::max(pMin.y, p.y),
                    std::max(pMin.z, p.z));
    pMax = Point3<T>(std::min(pMax.x, p.x),
                    std::min(pMax.y, p.y),
                    std::min(pMax.z, p.z));
    return *this;
}

template <typename T>
constexpr Point3f BoundingBox3<T>::centroid() const
{
    return (pMin + pMax) / 2;
}

template <typename T>
constexpr Point3f BoundingBox3<T>::get_unit_cube_coordinates(Point3f p) const
{
    Vector3f diagonal = this->diagonal();

    return Point3f((p.x - pMin.x) / diagonal.x,
                    (p.y - pMin.y) / diagonal.y,
                    (p.z - pMin.z) / diagonal.z);
}

template <typename T>
constexpr bool BoundingBox3<T>::overlaps(const BoundingBox3<T> &b2) 
{
    bool x = (pMax.x >= b2.pMin.x) && (pMin.x <= b2.pMax.x);
    bool y = (pMax.y >= b2.pMin.y) && (pMin.y <= b2.pMax.y);
    bool z = (pMax.z >= b2.pMin.z) && (pMin.z <= b2.pMax.z);

    return (x && y && z);
}

template <typename T>
constexpr bool BoundingBox3<T>::contains(const Point3<T> &p) const
{
    return (p.x >= pMin.x && p.x <= pMax.x &&
            p.y >= pMin.y && p.y <= pMax.y &&
            p.z >= pMin.z && p.z <= pMax.z);
}

// Same as contains, but the borders are not included
template <typename T>
constexpr bool BoundingBox3<T>::contains_exclusively(const Point3<T> &p) 
{
    return (p.x >= pMin.x && p.x < pMax.x &&
            p.y >= pMin.y && p.y < pMax.y &&
            p.z >= pMin.z && p.z < pMax.z);
}

template <typename T>
constexpr BoundingBox3<T> BoundingBox3<T>::expand(T delta) 
{
    return BoundingBox3<T>(pMin - Vector3<T>(delta, delta, delta),
                    pMax + Vector3<T>(delta, delta, delta));
}

template <typename T>
constexpr Vector3<T> BoundingBox3<T>::diagonal() const { 
    return pMax - pMin; 
}

template <typename T>
constexpr T BoundingBox3<T>::surface_area() const 
{
    Vector3<T> direction = diagonal();
    return 2 * (direction.x * direction.y + direction.x * direction.z + direction.y * direction.z);
}

template <typename T>
constexpr T BoundingBox3<T>::volume() const 
{
    Vector3<T> direction = diagonal();
    return direction.x * direction.y * direction.z;
}

template <typename T>
constexpr int BoundingBox3<T>::largest_axis() const 
{
    Vector3<T> direction = diagonal();

    if (direction.x > direction.y && direction.x > direction.z)
        return 0;
    else if (direction.y > direction.z)
        return 1;
    else
        return 2;
}

template <typename T>
constexpr Point3<T> BoundingBox3<T>::linear_interpolation(const Point3f &t) const 
{
    return Point3<T>(lerp(t.x, pMin.x, pMax.x), // Lerp is linear interpolate
                    lerp(t.y, pMin.y, pMax.y),
                    lerp(t.z, pMin.z, pMax.z));
}

template <typename T>
constexpr Vector3<T> BoundingBox3<T>::relative_offset(const Point3<T> &p) const 
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

template <typename T>
constexpr void BoundingBox3<T>::bounding_sphere(Point3<T> &center, Float &radius) const 
{
    center = (pMin + pMax) / 2;

    if (this->contains(center))
        radius = distance(center, pMax);
    else
        radius = 0;
}

template <typename T>
template <typename U> 
constexpr BoundingBox3<T>::BoundingBox3(const BoundingBox3<U>& b)
    : pMin(Point3<U>(b.pMin)), pMax(Point3<U>(b.pMax))
{

}

// Algorithm based on the 2D box slab intersection 
//  implemented branchless by Tavian Barnes
template <typename T>
constexpr bool BoundingBox3<T>::intersects(const Ray &ray, Float &hitOffset) const
{   
    //if (pMin.isZero() && pMax.isZero())
    //    return true;        

    Float tx1 = (this->pMin.x - ray.origin.x)*ray.inv_direction.x;
    Float tx2 = (this->pMax.x - ray.origin.x)*ray.inv_direction.x;

    Float tmin = std::min(tx1, tx2);
    Float tmax = std::max(tx1, tx2);

    Float ty1 = (this->pMin.y - ray.origin.y)*ray.inv_direction.y;
    Float ty2 = (this->pMax.y - ray.origin.y)*ray.inv_direction.y;

    tmin = std::max(tmin, std::min(ty1, ty2));
    tmax = std::min(tmax, std::max(ty1, ty2));

    Float tz1 = (this->pMin.z - ray.origin.z)*ray.inv_direction.z;
    Float tz2 = (this->pMax.z - ray.origin.z)*ray.inv_direction.z;

    tmin = std::max(tmin, std::min(tz1, tz2));
    tmax = std::min(tmax, std::max(tz1, tz2));

    // Initialize hitOffset to the minimum distance in case 
    //  there was an intersection
    if (tmin > 0)
        hitOffset = tmin;
    else
        hitOffset = tmax;

    // If the intersection exists, and is positive, and is within the ray's maximum offset
    return tmax >= tmin && hitOffset >= 0 && hitOffset <= ray.maximum_offset;
}

template <typename T>
constexpr bool BoundingBox3<T>::is_empty() const
{
    return (pMin.x >= pMax.x || pMin.y >= pMax.y || pMin.z >= pMax.z);
}

// Operator << for printing
template <typename T>
std::ostream &operator<<(std::ostream &os, const BoundingBox3<T> &b) 
{
    os << "[ " << b.pMin << " - " << b.pMax << " ]";
    return os;
}

template <typename T>
void BoundingBox3<T>::print() const
{
    printf("[ %f %f %f - %f %f %f ]\n", pMin.x, pMin.y, pMin.z, pMax.x, pMax.y, pMax.z);
}

//------------------------------------------------------------------------------

template <typename T>
constexpr BoundingBox2<T>::BoundingBox2(const Point2<T> &p) 
    : pMin(p), pMax(p) 
{ }

template <typename T>
constexpr BoundingBox2<T>::BoundingBox2(const Point2<T> &p1, const Point2<T> &p2)
    : pMin(std::min(p1.x, p2.x), std::min(p1.y, p2.y)),
        pMax(std::max(p1.x, p2.x), std::max(p1.y, p2.y)) 
{}

template <typename T>
template <typename U> 
constexpr BoundingBox2<T>::BoundingBox2(const BoundingBox2<U>& b)
    : pMin(Point2<U>(b.pMin)), pMax(Point2<U>(b.pMax))
{

}

template <typename T>
constexpr const Point2<T> &BoundingBox2<T>::operator[](int i) const
{
    if (i == 0) 
        return pMin;
    else
        return pMax;
}

template <typename T>
constexpr Point2<T> &BoundingBox2<T>::operator[](int i)
{
    if (i == 0) 
        return pMin;
    else
        return pMax;
}

template <typename T>
constexpr bool BoundingBox2<T>::operator==(const BoundingBox2<T> &b) const {
    return b.pMin == pMin && b.pMax == pMax;
}

template <typename T>
constexpr bool BoundingBox2<T>::operator!=(const BoundingBox2<T> &b) const {
    return b.pMin != pMin || b.pMax != pMax;
}

template <typename T>
constexpr Point2<T> BoundingBox2<T>::corner(int corner) const 
{
    BoundingBox2<T> &this_box = *this;

    return Point2<T>(this_box[(corner & 1)].x,
                    this_box[(corner & 2) ? 1 : 0].y);
}

template <typename T>
constexpr BoundingBox2<T> BoundingBox2<T>::operator+(const Point2<T> &p) const 
{
    return BoundingBox2<T>
        (
            Point2<T>(std::min(pMin.x, p.x),
                    std::min(pMin.y, p.y)),
            Point2<T>(std::max(pMax.x, p.x),
                    std::max(pMax.y, p.y))
        );
}

template <typename T>
constexpr BoundingBox2<T> BoundingBox2<T>::operator+(const BoundingBox2<T> &b) const 
{
    return BoundingBox2<T>
        (
            Point2<T>(std::min(pMin.x, b.pMin.x),
                    std::min(pMin.y, b.pMin.y)),
            Point2<T>(std::max(pMax.x, b.pMax.x),
                    std::max(pMax.y, b.pMax.y))
        );
}

template <typename T>
constexpr BoundingBox2<T> &BoundingBox2<T>::operator+=(const Point2<T> &p) 
{
    pMin = Point2<T>(std::min(pMin.x, p.x),
                    std::min(pMin.y, p.y));
    pMax = Point2<T>(std::max(pMax.x, p.x),
                    std::max(pMax.y, p.y));
    return *this;
}

template <typename T>
constexpr BoundingBox2<T> BoundingBox2<T>::operator-(const Point2<T> &p) const 
{
    return BoundingBox2<T>
        (
            Point2<T>(std::max(pMin.x, p.x),
                    std::max(pMin.y, p.y)),
            Point2<T>(std::min(pMax.x, p.x),
                    std::min(pMax.y, p.y))
        );
}

template <typename T>
constexpr BoundingBox2<T> BoundingBox2<T>::operator-(const BoundingBox2<T> &b) const 
{
    return BoundingBox2<T>
        (
            Point2<T>(std::max(pMin.x, b.pMin.x),
                    std::max(pMin.y, b.pMin.y)),
            Point2<T>(std::min(pMax.x, b.pMax.x),
                    std::min(pMax.y, b.pMax.y))
        );
}


// 0: Right
// 1: Top
// 2: Left
// 3: Bottom
template <typename T>
constexpr int BoundingBox2<T>::closest_side (Point2<T> p) const
{
    Float distance_right = pMax.x - p.x;
    Float distance_top = pMax.y - p.y;
    Float distance_left = p.x - pMin.x;
    Float distance_bottom = p.y - pMin.y;

    Float min_distance = std::min(std::min(distance_right, distance_top), std::min(distance_left, distance_bottom));

    if (min_distance == distance_right)
        return 0;
    else if (min_distance == distance_top)
        return 1;
    else if (min_distance == distance_left)
        return 2;
    else
        return 3;
}

template <typename T>
constexpr BoundingBox2<T> &BoundingBox2<T>::operator-=(const Point2<T> &p) 
{
    pMin = Point2<T>(std::max(pMin.x, p.x),
                    std::max(pMin.y, p.y));
    pMax = Point2<T>(std::min(pMax.x, p.x),
                    std::min(pMax.y, p.y));
    return *this;
}

template <typename T>
constexpr bool BoundingBox2<T>::overlaps(const BoundingBox2<T> &b2) 
{
    return (pMin.x < b2.pMax.x &&
        pMax.x > b2.pMin.x &&
        pMin.y < b2.pMax.y &&
        pMax.y > b2.pMin.y);
}

template <typename T>
constexpr bool BoundingBox2<T>::contains(const Point2<T> &p) const
{
    return (p.x >= pMin.x && p.x <= pMax.x &&
            p.y >= pMin.y && p.y <= pMax.y);
}

// Same as contains, but the borders are not included
template <typename T>
constexpr bool BoundingBox2<T>::contains_exclusively(const Point2<T> &p) 
{
    return (p.x >= pMin.x && p.x < pMax.x &&
            p.y >= pMin.y && p.y < pMax.y);
}

template <typename T>
constexpr BoundingBox2<T> BoundingBox2<T>::expand(T delta) 
{
    return BoundingBox2<T>(pMin - Vector2<T>(delta, delta),
                    pMax + Vector2<T>(delta, delta));
}

template <typename T>
constexpr Vector2<T> BoundingBox2<T>::diagonal() const { 
    return pMax - pMin; 
}

template <typename T>
constexpr Float BoundingBox2<T>::width() const 
{
    return pMax.x - pMin.x;
}

template <typename T>
constexpr Float BoundingBox2<T>::height() const 
{
    return pMax.y - pMin.y;
}

template <typename T>
constexpr T BoundingBox2<T>::area() const 
{
    Vector2<T> direction = diagonal();
    return (direction.x * direction.y);
}

template <typename T>
constexpr int BoundingBox2<T>::largest_axis() const 
{
    Vector2<T> direction = diagonal();

    if (direction.x > direction.y)
        return 0;
    else
        return 1;
}

template <typename T>
constexpr Point2<T> BoundingBox2<T>::linear_interpolation(const Point2f &t) const 
{
    return Point2<T>(lerp(t.x, pMin.x, pMax.x), // Lerp is linear interpolate
                    lerp(t.y, pMin.y, pMax.y));
}

template <typename T>
constexpr Vector2<T> BoundingBox2<T>::relative_offset(const Point2<T> &p) const 
{
    Vector2<T> origin = p - pMin;

    if (pMax.x > pMin.x)
        origin.x /= pMax.x - pMin.x;

    if (pMax.y > pMin.y) 
        origin.y /= pMax.y - pMin.y;

    return origin;
}

template <typename T>
constexpr void BoundingBox2<T>::bounding_sphere(Point2<T> &center, Float &radius) const 
{
    center = (pMin + pMax) / 2;

    if (this->contains(center))
        radius = distance(center, pMax);
    else
        radius = 0;
}


// Algorithm based on the 2D box slab intersection 
//  implemented branchless by Tavian Barnes
template <typename T>
constexpr bool BoundingBox2<T>::intersects(const Ray &ray, Float &hit_offset) const
{
    Float tx1 = (this->pMin.x - ray.origin.x)*ray.inv_direction.x;
    Float tx2 = (this->pMax.x - ray.origin.x)*ray.inv_direction.x;

    Float tmin = std::min(tx1, tx2);
    Float tmax = std::max(tx1, tx2);

    Float ty1 = (this->pMin.y - ray.origin.y)*ray.inv_direction.y;
    Float ty2 = (this->pMax.y - ray.origin.y)*ray.inv_direction.y;

    tmin = std::max(tmin, std::min(ty1, ty2));
    tmax = std::min(tmax, std::max(ty1, ty2));
    
    // Initialize hit_offset to the minimum distance in case 
    //  there was an intersection
    if (tmin > 0)
        hit_offset = tmin;
    else
        hit_offset = tmax;

    return tmax >= tmin && hit_offset >= 0 && hit_offset <= ray.maximum_offset;
}

template <typename T>
constexpr bool BoundingBox2<T>::second_intersection(const Ray &ray, Float &hit_offset) const
{
    Float tx1 = (this->pMin.x - ray.origin.x)*ray.inv_direction.x;
    Float tx2 = (this->pMax.x - ray.origin.x)*ray.inv_direction.x;

    Float tmin = std::min(tx1, tx2);
    Float tmax = std::max(tx1, tx2);

    Float ty1 = (this->pMin.y - ray.origin.y)*ray.inv_direction.y;
    Float ty2 = (this->pMax.y - ray.origin.y)*ray.inv_direction.y;

    tmin = std::max(tmin, std::min(ty1, ty2));
    tmax = std::min(tmax, std::max(ty1, ty2));
    
    // Initialize hit_offset to the minimum distance in case 
    //  there was an intersection
    hit_offset = tmax;

    return tmax >= tmin && hit_offset >= 0 && hit_offset <= ray.maximum_offset;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const BoundingBox2<T> &b) 
{
    os << "[ " << b[0] << " - " << b[1] << " ]";
    return os;
}

template <typename T>
void BoundingBox2<T>::print() const
{
    printf("[ %f %f - %f %f ]\n", pMin.x, pMin.y, pMax.x, pMax.y);
}