#include <gtest/gtest.h>
#include <fstream>
#include "Vector.h"
#include "Tmp.h"
#include "Tools.h"


TEST(VectorTest, ConstructorXYZ) {
    Vector v(1.0, 2.0, 3.0);
    EXPECT_DOUBLE_EQ(v.getX(), 1.0);
    EXPECT_DOUBLE_EQ(v.getY(), 2.0);
    EXPECT_DOUBLE_EQ(v.getZ(), 3.0);
}

TEST(VectorTest, ConstructorFromPoints) {
    Point a(1.0, 2.0, 3.0);
    Point b(4.0, 5.0, 6.0);
    Vector v(a, b);
    EXPECT_DOUBLE_EQ(v.getX(), 3.0);
    EXPECT_DOUBLE_EQ(v.getY(), 3.0);
    EXPECT_DOUBLE_EQ(v.getZ(), 3.0);
}

TEST(VectorTest, AdditionOperator) {
    Vector v1(1.0, 2.0, 3.0);
    Vector v2(4.0, 5.0, 6.0);
    Vector result = v1 + v2;
    EXPECT_DOUBLE_EQ(result.getX(), 5.0);
    EXPECT_DOUBLE_EQ(result.getY(), 7.0);
    EXPECT_DOUBLE_EQ(result.getZ(), 9.0);
}

TEST(VectorTest, ScalarMultiplication) {
    Vector v(1.0, 2.0, 3.0);
    Vector result = v * 2.0;
    EXPECT_DOUBLE_EQ(result.getX(), 2.0);
    EXPECT_DOUBLE_EQ(result.getY(), 4.0);
    EXPECT_DOUBLE_EQ(result.getZ(), 6.0);
}

TEST(VectorTest, DotProduct) {
    Vector v1(1.0, 2.0, 3.0);
    Vector v2(4.0, 5.0, 6.0);
    double result = v1.dot(v2);
    EXPECT_DOUBLE_EQ(result, 32.0);
}

TEST(VectorTest, CrossProduct) {
    Vector v1(1.0, 0.0, 0.0);
    Vector v2(0.0, 1.0, 0.0);
    Vector result = v1.cross(v2);
    EXPECT_DOUBLE_EQ(result.getX(), 0.0);
    EXPECT_DOUBLE_EQ(result.getY(), 0.0);
    EXPECT_DOUBLE_EQ(result.getZ(), 1.0);
}

TEST(VectorTest, Length) {
    Vector v(3.0, 4.0, 0.0);
    double length = v.length();
    EXPECT_DOUBLE_EQ(length, 5.0);
}

TEST(VectorTest, Normalized) {
    Vector v(3.0, 4.0, 0.0);
    Vector normalized = v.normalized();
    EXPECT_DOUBLE_EQ(normalized.length(), 1.0);
    EXPECT_DOUBLE_EQ(normalized.getX(), 0.6);
    EXPECT_DOUBLE_EQ(normalized.getY(), 0.8);
    EXPECT_DOUBLE_EQ(normalized.getZ(), 0.0);
}

TEST(VectorTest, ToPoint) {
    Vector v(1.0, 2.0, 3.0);
    Point p = v.toPoint();
    EXPECT_DOUBLE_EQ(p.x, 1.0);
    EXPECT_DOUBLE_EQ(p.y, 2.0);
    EXPECT_DOUBLE_EQ(p.z, 3.0);
}

TEST(TmpTest, ClosestToA) {
    Point A(0, 0, 0);
    Point B(10, 0, 0);
    Point T(-1, 0, 0);

    Tmp tmp(A, B, T);
    auto result = tmp.Calculate();

    EXPECT_DOUBLE_EQ(result.first, 1.0);
    EXPECT_EQ(result.second, A);
}


TEST(TmpTest, ClosestToB) {
    Point A(0, 0, 0);
    Point B(10, 0, 0);
    Point T(11, 0, 0);

    Tmp tmp(A, B, T);
    auto result = tmp.Calculate();

    EXPECT_DOUBLE_EQ(result.first, 1.0);
    EXPECT_EQ(result.second, B);
}


TEST(TmpTest, OnLineAB) {
    Point A(0, 0, 0);
    Point B(10, 0, 0);
    Point T(5, 0, 0);

    Tmp tmp(A, B, T);
    auto result = tmp.Calculate();

    EXPECT_DOUBLE_EQ(result.first, 0.0);
    EXPECT_EQ(result.second, T);
}


TEST(TmpTest, PerpendicularToMidpoint) {
    Point A(0, 0, 0);
    Point B(10, 0, 0);
    Point T(5, 5, 0);

    Tmp tmp(A, B, T);
    auto result = tmp.Calculate();

    EXPECT_DOUBLE_EQ(result.first, 5.0);
    EXPECT_EQ(result.second, Point(5, 0, 0));
}


TEST(ReadPointsFromFileTest, ReadValidFile) {
    std::string filename = "test_points.txt";
    std::ofstream outfile(filename);
    outfile << "1.0 2.0 3.0\n4.0 5.0 6.0\n7.0 8.0 9.0\n";
    outfile.close();


    std::vector<Point> points = readPointsFromFile(filename);

    ASSERT_EQ(points.size(), 3);
    EXPECT_EQ(points[0], Point(1.0, 2.0, 3.0));
    EXPECT_EQ(points[1], Point(4.0, 5.0, 6.0));
    EXPECT_EQ(points[2], Point(7.0, 8.0, 9.0));


    std::remove(filename.c_str());
}

TEST(ReadPointsFromFileTest, ReadInvalidFile) {
    std::string filename = "non_existent_file.txt";
    std::vector<Point> points = readPointsFromFile(filename);

    EXPECT_TRUE(points.empty());
}

TEST(GetPointTest, ValidInput) {
    char* argv[] = {
            (char*)"arg0",
            (char*)"arg1",
            (char*)"1.0",
            (char*)"2.0",
            (char*)"3.0"
    };

    auto O = getPoint(argv);
    EXPECT_EQ(O.value(), Point(1.0, 2.0, 3.0));
}

TEST(GetPointTest, InvalidInput) {
    char* argv[] = {
            (char*)"arg0",
            (char*)"arg1",
            (char*)"one",
            (char*)"2.0",
            (char*)"3.0"
    };

    EXPECT_EQ(getPoint(argv), std::nullopt);
}

TEST(FindMinDistanceTest, SingleClosestPoint) {
    Point O(0, 0, 0);
    std::vector<Point> points = {
            Point(1, 0, 0),
            Point(2, 0, 0),
            Point(3, 0, 0)
    };

    std::map<int, Point> closestPoints = FindMinDistance(O, points);

    ASSERT_EQ(closestPoints.size(), 1);
    EXPECT_EQ(closestPoints[1], Point(1, 0, 0));
}

TEST(FindMinDistanceTest, MultipleClosestPoints) {
    Point O(0, 0, 0);
    std::vector<Point> points = {
            Point(1, 0, 0),
            Point(1, 0, 0),
            Point(2, 0, 0)
    };

    std::map<int, Point> closestPoints = FindMinDistance(O, points);

    ASSERT_EQ(closestPoints.size(), 2);
    EXPECT_EQ(closestPoints[1], Point(1, 0, 0));
    EXPECT_EQ(closestPoints[2], Point(1, 0, 0));
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}