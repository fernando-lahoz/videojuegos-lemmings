#include "geometry/transform.hpp"

Transform::Transform() 
{ }

Transform::Transform(const Matrix4x4f &m) 
    : m(m)
{ }

std::ostream &operator<<(std::ostream &os, const Transform &t) 
{
    Matrix4x4f temp = t.get_matrix();

    // Puts 0 instead of very small numbers
    for (int i = 0; i < 4; ++i) 
    {
        for (int j = 0; j < 4; ++j) 
        {
            if (abs(temp[i][j]) < FLOAT_ERROR_MARGIN) 
                temp[i][j] = 0.0f;
        }
    }

    os << "[ " << temp[0][0] << " " << temp[0][1] << " " << temp[0][2] << " " << temp[0][3] << " ]\n"
        << "[ " << temp[1][0] << " " << temp[1][1] << " " << temp[1][2] << " " << temp[1][3] << " ]\n"
        << "[ " << temp[2][0] << " " << temp[2][1] << " " << temp[2][2] << " " << temp[2][3] << " ]\n"
        << "[ " << temp[3][0] << " " << temp[3][1] << " " << temp[3][2] << " " << temp[3][3] << " ]";
    
    return os;
}

void Transform::print() const
{
    Matrix4x4f temp = m;

    // Puts 0 instead of very small numbers
    for (int i = 0; i < 4; ++i) 
    {
        for (int j = 0; j < 4; ++j) 
        {
            if (abs(temp[i][j]) < FLOAT_ERROR_MARGIN) 
                temp[i][j] = 0.0f;
        }
    }

    printf("[ %f %f %f %f ]\n", temp[0][0], temp[0][1], temp[0][2], temp[0][3]);
    printf("[ %f %f %f %f ]\n", temp[1][0], temp[1][1], temp[1][2], temp[1][3]);
    printf("[ %f %f %f %f ]\n", temp[2][0], temp[2][1], temp[2][2], temp[2][3]);
    printf("[ %f %f %f %f ]\n", temp[3][0], temp[3][1], temp[3][2], temp[3][3]);
}

bool Transform::operator==(const Transform &t) const {
    return t.m == m;
}

bool Transform::operator!=(const Transform &t) const {
    return t.m != m;
}

bool Transform::operator<(const Transform &t2) const 
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++) 
        {
            if (m[i][j] < t2.m[i][j]) 
                return true;

            if (m[i][j] > t2.m[i][j]) 
                return false;
        }
    }

    return false;
}

bool Transform::is_identity() const 
{
    return (m[0][0] == 1.0f && m[0][1] == 0.0f &&
            m[0][2] == 0.0f && m[0][3] == 0.0f &&
            m[1][0] == 0.0f && m[1][1] == 1.0f &&
            m[1][2] == 0.0f && m[1][3] == 0.0f &&
            m[2][0] == 0.0f && m[2][1] == 0.0f &&
            m[2][2] == 1.0f && m[2][3] == 0.0f &&
            m[3][0] == 0.0f && m[3][1] == 0.0f &&
            m[3][2] == 0.0f && m[3][3] == 1.0f);
}

const Matrix4x4f &Transform::get_matrix() const { 
    return m; 
}


bool Transform::has_scale() const 
{
    Vector3f x (1, 0, 0);
    Vector3f y (0, 1, 0);
    Vector3f z (0, 0, 1);

    const Transform &transform = *this;

    // Transform the base vectors to check for scaling.
    // Length squared is used, since if the vector is still 1
    //  the square will not do anything
    Float x_transformed = transform(x).length_squared();
    Float y_transformed = transform(y).length_squared();
    Float z_transformed = transform(z).length_squared();
    
    // If any of the vectors have a length different from 1
    return (std::abs(x_transformed - 1.0f) > FLOAT_ERROR_MARGIN ||
            std::abs(y_transformed - 1.0f) > FLOAT_ERROR_MARGIN ||
            std::abs(z_transformed - 1.0f) > FLOAT_ERROR_MARGIN); 
            
}

Point3f Transform::operator()(const Point3f &p) const 
{
    Float x = p.x, y = p.y, z = p.z;
    Float xp = m[0][0] * x + m[0][1] * y + m[0][2] * z + m[0][3];
    Float yp = m[1][0] * x + m[1][1] * y + m[1][2] * z + m[1][3];
    Float zp = m[2][0] * x + m[2][1] * y + m[2][2] * z + m[2][3];
    Float wp = m[3][0] * x + m[3][1] * y + m[3][2] * z + m[3][3];

    return Point3f(xp, yp, zp) / wp;
}

Vector3f Transform::operator()(const Vector3f &v) const
{
    Float x = v.x, y = v.y, z = v.z;
    Float xp = m[0][0] * x + m[0][1] * y + m[0][2] * z;
    Float yp = m[1][0] * x + m[1][1] * y + m[1][2] * z;
    Float zp = m[2][0] * x + m[2][1] * y + m[2][2] * z;

    return Vector3f(xp, yp, zp);
}

Point3f Transform::operator()(const Point3f &p, Vector3f &pError)
{
    Float x = p.x, y = p.y, z = p.z;
    Float xp = m[0][0] * x + m[0][1] * y + m[0][2] * z + m[0][3];
    Float yp = m[1][0] * x + m[1][1] * y + m[1][2] * z + m[1][3];
    Float zp = m[2][0] * x + m[2][1] * y + m[2][2] * z + m[2][3];
    Float wp = m[3][0] * x + m[3][1] * y + m[3][2] * z + m[3][3];

    // Compute absolute error for transformed point
    Float xAbsSum = (std::abs(m[0][0] * x) + std::abs(m[0][1] * y) +
                    std::abs(m[0][2] * z) + std::abs(m[0][3]));

    Float yAbsSum = (std::abs(m[1][0] * x) + std::abs(m[1][1] * y) +
                    std::abs(m[1][2] * z) + std::abs(m[1][3]));

    Float zAbsSum = (std::abs(m[2][0] * x) + std::abs(m[2][1] * y) +
                    std::abs(m[2][2] * z) + std::abs(m[2][3]));

    pError += Vector3f(xAbsSum, yAbsSum, zAbsSum) * math::error_bound(4) * std::abs(wp);

    return Point3f(xp, yp, zp) / wp;
}

Bound3f Transform::operator()(const Bound3f &b) const 
{
    const Transform &transform = *this;

    // Transforms each corner and adds it to the bounding box
    Bound3f ret (transform(Point3f(b.pMin.x, b.pMin.y, b.pMin.z)));    

    ret += transform(Point3f(b.pMax.x, b.pMin.y, b.pMin.z));
    ret += transform(Point3f(b.pMin.x, b.pMax.y, b.pMin.z));
    ret += transform(Point3f(b.pMin.x, b.pMin.y, b.pMax.z));
    ret += transform(Point3f(b.pMin.x, b.pMax.y, b.pMax.z));
    ret += transform(Point3f(b.pMax.x, b.pMax.y, b.pMin.z));
    ret += transform(Point3f(b.pMax.x, b.pMin.y, b.pMax.z));
    ret += transform(Point3f(b.pMax.x, b.pMax.y, b.pMax.z));

    return ret;
}

Transform Transform::operator*(const Transform &t2) const 
{
    Matrix4x4f m1 = m * t2.m;

    return Transform(m1);
}


Transform Transform::operator()(const Transform &b) const 
{
    const Transform &a = (*this);
    return a * b; 
}


bool Transform::swaps_handedness() const 
{
    // A transformation swaps handedness when the determinant is negative
    Float det = 
        m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]) -
        m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0]) +
        m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);

    return det < 0; 
}


//SurfaceInteraction *operator()(const SurfaceInteraction &si) const {return nullptr;}
Point3f Transform::operator()(const Point3f &point, Vector3f &absError) const
{
    Float xAbsSum = (std::abs(m[0][0] * point.x) + std::abs(m[0][1] * point.y) +
                    std::abs(m[0][2] * point.z) + std::abs(m[0][3]));

    Float yAbsSum = (std::abs(m[1][0] * point.x) + std::abs(m[1][1] * point.y) +
                    std::abs(m[1][2] * point.z) + std::abs(m[1][3]));

    Float zAbsSum = (std::abs(m[2][0] * point.x) + std::abs(m[2][1] * point.y) +
                    std::abs(m[2][2] * point.z) + std::abs(m[2][3]));

    absError = Vector3f(xAbsSum, yAbsSum, zAbsSum) * math::error_bound((3));

    return operator()(point);
}


Point3f Transform::operator()(const Point3f &, const Vector3f &, Vector3f &) const 
{
    throw std::runtime_error("Transform doesn't support pError transformation");
}

Vector3f Transform::operator()(const Vector3f &v, Vector3f &vTransError) const 
{
    Float xAbsSum = (abs(m[0][0] * v.x) + abs(m[0][1] * v.y) +
                    abs(m[0][2] * v.z));

    Float yAbsSum = (abs(m[1][0] * v.x) + abs(m[1][1] * v.y) +
                    abs(m[1][2] * v.z));

    Float zAbsSum = (abs(m[2][0] * v.x) + abs(m[2][1] * v.y) +
                    abs(m[2][2] * v.z));

    vTransError = Vector3f(xAbsSum, yAbsSum, zAbsSum) * (math::error_bound(3));

    return operator()(v);
}

Vector3f Transform::operator()(const Vector3f &, const Vector3f &, Vector3f &) const 
{
    throw std::runtime_error("Transform doesn't support vError transformation");
}

Ray Transform::operator()(const Ray &ray, Vector3f &oError, Vector3f &dError) const 
{
    Point3f origin = operator()(ray.origin, oError);
    Vector3f direction = operator()(ray.direction, dError);

    Float tMax = ray.maximum_offset;
    Float lengthSquared = direction.length_squared();

    if (lengthSquared > 0) 
    {
        Float dt = dot(abs(direction), oError) / lengthSquared;
        origin += direction * dt;
        tMax -= dt;
    }

    //TODO: ray.medium does not exist
    return Ray(origin, direction, tMax, ray.time, 1/*ray.medium*/);
}

Transform* Transform::operator()(const Transform *t) const
{
    Transform *ret = new Transform((*this)(*t));
    return ret;
}



Transform inverse(const Transform &t)
{
    return Transform(inverse(t.m));
}
Transform* inverse(const Transform *t)
{
    return new Transform(inverse(t->m));
}

Transform transpose(const Transform &t)
{
    return Transform(transpose(t.m));
}

// TODO: Transform* wtf?
Transform* transpose(const Transform *t)
{
    return new Transform(transpose(t->m));
}

Transform translate(const Vector3f &delta)
{
    Matrix4x4f m(1, 0, 0, delta.x,
                0, 1, 0, delta.y,
                0, 0, 1, delta.z,
                0, 0, 0, 1);

    /* Matrix4x4f mInv(1, 0, 0, -delta.x,
                    0, 1, 0, -delta.y,
                    0, 0, 1, -delta.z,
                    0, 0, 0, 1); */

    return Transform(m);
}

Transform scale(Float x, Float y, Float z)
{
    Matrix4x4f m(x, 0, 0, 0,
                0, y, 0, 0,
                0, 0, z, 0,
                0, 0, 0, 1);

   /*  Matrix4x4f mInv(1.0f / x, 0, 0, 0,
                    0, 1.0f / y, 0, 0,
                    0, 0, 1.0f / z, 0,
                    0, 0, 0, 1); */

    return Transform(m);
}

// @param angle Rotation angle in degrees
Transform rotateX(Float angle)
{
    Float sinTheta = std::sin(math::radians(angle));
    Float cosTheta = std::cos(math::radians(angle));

    Matrix4x4f m(1, 0, 0, 0,
                0, cosTheta, -sinTheta, 0,
                0, sinTheta, cosTheta, 0,
                0, 0, 0, 1);

    return Transform(m);
}

// @param angle Rotation angle in degrees
Transform rotateY(Float angle)
{
    Float sinTheta = std::sin(math::radians(angle));
    Float cosTheta = std::cos(math::radians(angle));

    Matrix4x4f m(cosTheta, 0, sinTheta, 0,
                0, 1, 0, 0,
                -sinTheta, 0, cosTheta, 0,
                0, 0, 0, 1);

    return Transform(m);
}

// @param angle Rotation angle in degrees
Transform rotateZ(Float angle)
{
    Float sinTheta = std::sin(math::radians(angle));
    Float cosTheta = std::cos(math::radians(angle));

    Matrix4x4f m(cosTheta, -sinTheta, 0, 0,
                sinTheta, cosTheta, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1);

    return Transform(m);
}

Transform base_change(const Point3f &o, 
        const Vector3f &u, 
        const Vector3f &v, 
        const Vector3f &w)
{
    Matrix4x4f m(u.x, v.x, w.x, o.x,
                 u.y, v.y, w.y, o.y,
                 u.z, v.z, w.z, o.z,
                 0.0f, 0.0f, 0.0f, 1.0f);

    return Transform(m);
}

Transform* new_base_change(const Point3f &o, 
        const Vector3f &u, 
        const Vector3f &v, 
        const Vector3f &w)
{
    Matrix4x4f m(u.x, v.x, w.x, o.x,
                 u.y, v.y, w.y, o.y,
                 u.z, v.z, w.z, o.z,
                 0.0f, 0.0f, 0.0f, 1.0f);

    return new Transform(m);
}

Transform rotate(Float theta, const Vector3f &axis) 
{
    Vector3f a = normalize(axis);
    Float sinTheta = std::sin(math::radians(theta));
    Float cosTheta = std::cos(math::radians(theta));

    Matrix4x4f matrix;
    
    // Compute rotation of first basis vector
    matrix[0][0] = a.x * a.x + (1 - a.x * a.x) * cosTheta;
    matrix[0][1] = a.x * a.y * (1 - cosTheta) - a.z * sinTheta;
    matrix[0][2] = a.x * a.z * (1 - cosTheta) + a.y * sinTheta;
    matrix[0][3] = 0;

    // Second basis vector
    matrix[1][0] = a.x * a.y * (1 - cosTheta) + a.z * sinTheta;
    matrix[1][1] = a.y * a.y + (1 - a.y * a.y) * cosTheta;
    matrix[1][2] = a.y * a.z * (1 - cosTheta) - a.x * sinTheta;
    matrix[1][3] = 0;
    
    // Third basis vector
    matrix[2][0] = a.x * a.z * (1 - cosTheta) - a.y * sinTheta;
    matrix[2][1] = a.y * a.z * (1 - cosTheta) + a.x * sinTheta;
    matrix[2][2] = a.z * a.z + (1 - a.z * a.z) * cosTheta;
    matrix[2][3] = 0;

    return Transform(matrix);
}
 
Transform look_at(const Point3f &pos, const Point3f &look, const Vector3f &up) 
{
    Matrix4x4f cameraToWorld;

    // Initialize fourth column of viewing matrix
    cameraToWorld[0][3] = pos.x;
    cameraToWorld[1][3] = pos.y;
    cameraToWorld[2][3] = pos.z;
    cameraToWorld[3][3] = 1;

    // Initialize first three columns of viewing matrix
    Vector3f dir = normalize(look - pos);   // Look direction vector
    Vector3f right = normalize(cross(normalize(up), dir));
    Vector3f newUp = cross(dir, right);

    cameraToWorld[0][0] = right.x;
    cameraToWorld[1][0] = right.y;
    cameraToWorld[2][0] = right.z;
    cameraToWorld[3][0] = 0.;
    cameraToWorld[0][1] = newUp.x;
    cameraToWorld[1][1] = newUp.y;
    cameraToWorld[2][1] = newUp.z;
    cameraToWorld[3][1] = 0.;
    cameraToWorld[0][2] = dir.x;
    cameraToWorld[1][2] = dir.y;
    cameraToWorld[2][2] = dir.z;
    cameraToWorld[3][2] = 0.;

    return Transform(inverse(cameraToWorld));
}

