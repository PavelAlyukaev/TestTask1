#include "Tmp.h"
Tmp::Tmp(const Point& A, const Point& B, const Point& T)
        : m_A(A), m_B(B), m_T(T) {}

std::pair<double, Point> Tmp::Calculate() {
    Vector AT(m_A, m_T);
    Vector BT(m_B, m_T);
    Vector AB(m_A, m_B);


    if(AB.length() == 0)
    {
        return {AT.length(), m_A};
    }

    auto q = AB.dot(AT) / AB.length();

    if (q < 0.0) {
        return {AT.length(), m_A};
    } else if (q > AB.length()) {
        return {BT.length(), m_B};
    } else {
        double h = AB.cross(AT).length() / AB.length();
        Point p = (Vector({0, 0, 0}, m_A) + AB.normalized() * q).toPoint();
        return {h, p};
    }
}