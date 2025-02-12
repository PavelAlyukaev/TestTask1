#include "Vector.h"

Vector::Vector(double x, double y, double z) : m_x(x), m_y(y), m_z(z) {}

Vector::Vector(const Point& a, const Point& b)
        : m_x(b.x - a.x), m_y(b.y - a.y), m_z(b.z - a.z) {}

Vector Vector::operator+(const Vector& other) const {
    return {m_x + other.m_x, m_y + other.m_y, m_z + other.m_z};
}

Vector Vector::operator*(double scalar) const {
    return {m_x * scalar, m_y * scalar, m_z * scalar};
}

double Vector::dot(const Vector& other) const {
    return m_x * other.m_x + m_y * other.m_y + m_z * other.m_z;
}

Vector Vector::cross(const Vector& other) const {
    return {
            m_y * other.m_z - m_z * other.m_y,
            m_z * other.m_x - m_x * other.m_z,
            m_x * other.m_y - m_y * other.m_x
    };
}

double Vector::length() const {
    return std::sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
}

Vector Vector::normalized() const {
    double len = length();
    if (len != 0.0) {
        return *this * (1.0 / len);
    }
    return *this;
}

Point Vector::toPoint() const {
    return {m_x, m_y, m_z};
}

double Vector::getX() const {
    return m_x;
}

double Vector::getY() const {
    return m_y;
}

double Vector::getZ() const {
    return m_z;
}

