#pragma once

#include "lib/types.hpp"
#include "math/math.hpp"
#include "geometry/point.hpp"
#include "geometry/ray.hpp"
#include "geometry/vector.hpp"

template <typename T>
class BoundingBox3
{
public:
    Point3<T> pMin, pMax;

    constexpr BoundingBox3();
    constexpr BoundingBox3(T k);
    constexpr BoundingBox3(const Point3<T> &p);
    constexpr BoundingBox3(const Point3<T> &p1, const Point3<T> &p2);

    template <typename U> 
    constexpr explicit BoundingBox3(const BoundingBox3<U>& b);

    constexpr const Point3<T> &operator[](int i) const;
    constexpr Point3<T> &operator[](int i);

    constexpr bool operator==(const BoundingBox3<T> &b) const;
    constexpr bool operator!=(const BoundingBox3<T> &b) const;

    constexpr Point3<T> corner(int corner) const;

    constexpr BoundingBox3<T> operator+(const Point3<T> &p) const;
    constexpr BoundingBox3<T> operator+(const BoundingBox3<T> &b) const;
    constexpr BoundingBox3<T> &operator+=(const Point3<T> &p);

    constexpr BoundingBox3<T> operator-(const Point3<T> &p) const;
    constexpr BoundingBox3<T> operator-(const BoundingBox3<T> &b) const;
    constexpr BoundingBox3<T> &operator-=(const Point3<T> &p);

    constexpr Point3f centroid() const;

    constexpr Point3f get_unit_cube_coordinates(Point3f p) const;

    constexpr bool overlaps(const BoundingBox3<T> &b2);

    constexpr bool contains(const Point3<T> &p) const;

    // Same as contains, but the borders are not included
    constexpr bool contains_exclusively(const Point3<T> &p);

    constexpr BoundingBox3<T> expand(T delta);

    constexpr Vector3<T> diagonal() const;

    constexpr T surface_area() const;

    constexpr T volume() const;

    constexpr int largest_axis() const;

    constexpr Point3<T> linear_interpolation(const Point3f &t) const;

    constexpr Vector3<T> relative_offset(const Point3<T> &p) const;

    constexpr void bounding_sphere(Point3<T> &center, Float &radius) const;

    // Algorithm based on the 2D box slab intersection 
    //  implemented branchless by Tavian Barnes
    constexpr bool intersects(const Ray &ray, Float &hitOffset) const;

    constexpr bool is_empty() const;

    void print() const;
};

template <typename T>
std::ostream &operator<<(std::ostream &os, const BoundingBox3<T> &b);

using Bound3f = BoundingBox3<Float>;
using Bound3i = BoundingBox3<int>;

//------------------------------------------------------------------------------

template <typename T>
class BoundingBox2
{
public:
    Point2<T> pMin, pMax;

    constexpr BoundingBox2() = default;
    constexpr BoundingBox2(const Point2<T> &p);
    constexpr BoundingBox2(const Point2<T> &p1, const Point2<T> &p2);

    template <typename U> 
    constexpr explicit BoundingBox2(const BoundingBox2<U>& b);

    constexpr const Point2<T> &operator[](int i) const;
    constexpr Point2<T> &operator[](int i);

    constexpr bool operator==(const BoundingBox2<T> &b) const;
    constexpr bool operator!=(const BoundingBox2<T> &b) const;

    constexpr Point2<T> corner(int corner) const;

    constexpr BoundingBox2<T> operator+(const Point2<T> &p) const;
    constexpr BoundingBox2<T> operator+(const BoundingBox2<T> &b) const;
    constexpr BoundingBox2<T> &operator+=(const Point2<T> &p);

    constexpr BoundingBox2<T> operator-(const Point2<T> &p) const;
    constexpr BoundingBox2<T> operator-(const BoundingBox2<T> &b) const;
    constexpr BoundingBox2<T> &operator-=(const Point2<T> &p);

    constexpr bool overlaps(const BoundingBox2<T> &b2);

    constexpr bool contains(const Point2<T> &p) const;

    // Same as contains, but the borders are not included
    constexpr bool contains_exclusively(const Point2<T> &p);

    enum class Border { TOP, BOTTOM, RIGHT, LEFT };
    constexpr T is_near_border(const Point2<T> &p, Border border, T distance);

    constexpr BoundingBox2<T> expand(T delta);

    constexpr Vector2<T> diagonal() const;

    constexpr T width() const;

    constexpr T height() const;

    constexpr T area() const;

    constexpr int largest_axis() const;

    constexpr Point2<T> linear_interpolation(const Point2f &t) const;

    constexpr Vector2<T> relative_offset(const Point2<T> &p) const;

    constexpr void bounding_sphere(Point2<T> &center, Float &radius) const;

    // Algorithm based on the 2D box slab intersection 
    //  implemented branchless by Tavian Barnes
    constexpr bool intersects(const Ray &ray, Float &hit_offset) const;

    void print() const;
};

template <typename T>
std::ostream &operator<<(std::ostream &os, const BoundingBox2<T> &b);

using Bound2f = BoundingBox2<Float>;
using Bound2i = BoundingBox2<int>;

#include "geometry/bounding_box.ipp"