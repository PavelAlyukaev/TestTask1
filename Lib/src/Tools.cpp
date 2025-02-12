#include "Tools.h"
#include "Tmp.h"
#include "Point.h"


std::vector<Point> readPointsFromFile(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<Point> points;

    if (!file.is_open()) {
        std::cerr << "Mistake: couldn't open the file " << filename << std::endl;
        return points;
    }

    double x, y, z;
    while (file >> x >> y >> z) {
        points.emplace_back(x, y, z);
    }

    file.close();
    return points;
}

std::optional<Point> getPoint(char *const *argv) {
    double x, y, z;
    try {
        x = std::stod(argv[2]);
        y = std::stod(argv[3]);
        z = std::stod(argv[4]);
    }
    catch (std::invalid_argument ex)
    {
        return std::nullopt;
    }

    const Point O{x, y, z};
    return O;
}
std::map<int, Point> FindMinDistance(const Point &O, const std::vector<Point> &points) {
    std::map<int, Point> closestPoints;
    double minDistance = std::numeric_limits<double>::max();
    const double epsilon = std::numeric_limits<double>::epsilon();

    for (size_t i = 1; i < points.size(); ++i) {
        Tmp t(points[i - 1], points[i], O);
        auto [distance, point] = t.Calculate();
        if (minDistance - distance > epsilon) {
            minDistance = distance;
            closestPoints.clear();
            closestPoints.emplace(i, point);
        } else if (std::abs(minDistance - distance) < epsilon) {
            closestPoints.emplace(i, point);
        }
    }
    return closestPoints;
}
