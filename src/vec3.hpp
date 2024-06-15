#pragma once

#include <array>
#include <cmath>
#include <iostream>

class Vec3
{
public:
    std::array<double, 3> e;

    Vec3();
    Vec3(double e0, double e1, double e2);

    double x() const;
    double y() const;
    double z() const;

    Vec3 operator-() const;
    double operator[](int i) const;
    double& operator[](int i);

    Vec3& operator+=(const Vec3& v);
    Vec3& operator*=(double t);
    Vec3& operator/=(double t);

    double length() const;
    double length_squared() const;
};

using Point3 = Vec3;

inline std::ostream& operator<<(std::ostream& out, const Vec3& v);

inline Vec3 operator+(const Vec3& u, const Vec3& v);
inline Vec3 operator-(const Vec3& u, const Vec3& v);
inline Vec3 operator*(const Vec3& u, const Vec3& v);
inline Vec3 operator*(double t, const Vec3& v);
inline Vec3 operator*(const Vec3& v, double t);
inline Vec3 operator/(const Vec3& v, double t);

inline double dot(const Vec3& u, const Vec3& v);
inline Vec3 cross(const Vec3& u, const Vec3& v);

inline Vec3 unitVector(const Vec3& v);