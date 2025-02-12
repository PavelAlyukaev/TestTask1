#pragma once
#include "Point.h"

class Vector
{
public:
    Vector(double x, double y, double z);
    Vector(const Point& a, const Point& b);

    Vector operator+(const Vector& other) const;
    Vector operator*(double scalar) const;

    [[nodiscard]] double dot(const Vector& other) const;
    [[nodiscard]] Vector cross(const Vector& other) const;
    [[nodiscard]] double length() const;
    [[nodiscard]] Vector normalized() const;
    [[nodiscard]] Point toPoint() const;

    [[nodiscard]] double getX() const;
    [[nodiscard]] double getY() const;
    [[nodiscard]] double getZ() const;

private:
    double m_x, m_y, m_z;
};
