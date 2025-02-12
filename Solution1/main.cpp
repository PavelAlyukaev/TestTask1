#include "Tools.h"
#include "Point.h"

int main(int argc, char* argv[])
{
    if (argc != 5) {
        std::cerr << "Using: " << argv[0] << " <path_to_file> <x> <y> <z>" << std::endl;
        return 1;
    }


    auto O = getPoint(argv);
    if(O == std::nullopt)
    {
        std::cerr << "The coordinates <x> <y> <z> are not correct!" << std::endl;
        return 1;
    }

    std::vector<Point> points = readPointsFromFile(argv[1]);
    std::map<int, Point> closestPoints = FindMinDistance(O.value(), points);

    for (const auto& [index, point] : closestPoints) {
        std::cout << "segment " << index << " point " << point.toString() << std::endl;
    }

    return 0;
}