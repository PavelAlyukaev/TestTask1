#include "Point.h"

std::optional<Point> getPoint(char *const *argv);

std::vector<Point> readPointsFromFile(const std::string& filename);

std::map<int, Point> FindMinDistance(const Point &O, const std::vector<Point> &points);