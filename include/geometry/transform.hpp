#pragma once

#include "lib/types.hpp"
#include "math/matrix4x4.hpp"
#include "math/math.hpp"

#include "geometry/vector.hpp"
#include "geometry/point.hpp"
#include "geometry/bounding_box.hpp"

class Transform
{
public:
    Matrix4x4f m;

public:
    // TODO: transform should init to identity matrix
    Transform();
    Transform(const Matrix4x4f &m);
    //Transform(const Matrix4x4f &m, const Matrix4x4f &mInv);

    bool operator==(const Transform &t) const;
    bool operator!=(const Transform &t) const;
    bool operator<(const Transform &t2) const;

    bool is_identity() const;

    const Matrix4x4f &get_matrix() const;

    bool has_scale() const;

    Point3f operator()(const Point3f &p) const;
    Vector3f operator()(const Vector3f &v) const;
    Point3f operator()(const Point3f &p, Vector3f &pError);
    Bound3f operator()(const Bound3f &b) const;
    Transform operator()(const Transform &b) const;

    Transform operator*(const Transform &t2) const;

    bool swaps_handedness() const;

    //SurfaceInteraction *operator()(const SurfaceInteraction &si) const {return nullptr;}
    Point3f operator()(const Point3f &point, Vector3f &absError) const;
    Point3f operator()(const Point3f &p, const Vector3f &pError,
                Vector3f &pTransError) const;
    Vector3f operator()(const Vector3f &v, Vector3f &vTransError) const;
    Vector3f operator()(const Vector3f &v, const Vector3f &vError,
                Vector3f &vTransError) const;

    Ray operator()(const Ray &ray, Vector3f &oError, Vector3f &dError) const;
    Transform* operator()(const Transform *t) const;

    void print() const;
    friend std::ostream &operator<<(std::ostream &os, const Transform &t);

    friend Transform inverse(const Transform &t);
    friend Transform transpose(const Transform &t);
};

std::ostream &operator<<(std::ostream &os, const Transform &t);

Transform inverse(const Transform &t);
Transform* inverse(const Transform *t);

Transform transpose(const Transform &t);
// TODO: Transform* wtf?
Transform* transpose(const Transform *t);

Transform translate(const Vector3f &delta);

Transform scale(Float x, Float y, Float z);

// @param angle Rotation angle in degrees
Transform rotateX(Float angle);

// @param angle Rotation angle in degrees
Transform rotateY(Float angle);

// @param angle Rotation angle in degrees
Transform rotateZ(Float angle);

Transform base_change(const Point3f &o, 
                      const Vector3f &u, 
                      const Vector3f &v, 
                      const Vector3f &w);

Transform* new_base_change(const Point3f &o, 
                           const Vector3f &u, 
                           const Vector3f &v, 
                           const Vector3f &w);

Transform rotate(Float theta, const Vector3f &axis);
 
Transform look_at(const Point3f &pos, const Point3f &look, const Vector3f &up);

#include "geometry/transform.ipp"
