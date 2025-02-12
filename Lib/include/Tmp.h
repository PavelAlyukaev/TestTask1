#pragma once
#include "Point.h"
#include "Vector.h"

class Tmp
{
public:
    explicit Tmp(const Point& A, const Point& B, const Point& T);

    std::pair<double, Point> Calculate();

private:
    Point m_T, m_A, m_B;
};

