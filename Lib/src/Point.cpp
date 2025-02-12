#include <format>
#include "Point.h"

std::string Point::toString() const {
    return std::format("{} {} {}", x, y, z);
}