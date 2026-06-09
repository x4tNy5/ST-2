// Copyright 2025 UNN-CS Team

#define _USE_MATH_DEFINES
#include <cmath>
#include <gtest/gtest.h>
#include "circle.h"
#include "tasks.h"

namespace {
constexpr double kEps = 1e-4;
}

TEST(Circle, ConstructorStoresRadius) {
    Circle circle(7.5);
    EXPECT_NEAR(circle.getRadius(), 7.5, kEps);
}

TEST(Circle, SetRadiusUpdatesFerence) {
    Circle circle(1.0);
    circle.setRadius(4.0);
    EXPECT_NEAR(circle.getFerence(), 2.0 * M_PI * 4.0, kEps);
}

TEST(Circle, SetRadiusUpdatesArea) {
    Circle circle(1.0);
    circle.setRadius(4.0);
    EXPECT_NEAR(circle.getArea(), M_PI * 16.0, kEps);
}

TEST(Circle, SetFerenceUpdatesRadius) {
    Circle circle(2.0);
    const double targetFerence = 20.0;
    circle.setFerence(targetFerence);
    EXPECT_NEAR(circle.getRadius(), targetFerence / (2.0 * M_PI), kEps);
}

TEST(Circle, SetFerenceUpdatesArea) {
    Circle circle(2.0);
    const double targetFerence = 20.0;
    circle.setFerence(targetFerence);
    EXPECT_NEAR(circle.getArea(), (targetFerence * targetFerence) / (4.0 * M_PI), kEps);
}

TEST(Circle, SetAreaUpdatesRadius) {
    Circle circle(2.0);
    const double targetArea = 50.0;
    circle.setArea(targetArea);
    EXPECT_NEAR(circle.getRadius(), std::sqrt(targetArea / M_PI), kEps);
}

TEST(Circle, SetAreaUpdatesFerence) {
    Circle circle(2.0);
    const double targetArea = 50.0;
    circle.setArea(targetArea);
    EXPECT_NEAR(circle.getFerence(), 2.0 * M_PI * std::sqrt(targetArea / M_PI), kEps);
}

TEST(Circle, UnitCircleHasExpectedMetrics) {
    Circle circle(1.0);
    EXPECT_NEAR(circle.getFerence(), 2.0 * M_PI, kEps);
    EXPECT_NEAR(circle.getArea(), M_PI, kEps);
}

TEST(Circle, ZeroRadiusProducesZeroMetrics) {
    Circle circle(0.0);
    EXPECT_DOUBLE_EQ(circle.getRadius(), 0.0);
    EXPECT_DOUBLE_EQ(circle.getFerence(), 0.0);
    EXPECT_DOUBLE_EQ(circle.getArea(), 0.0);
}

TEST(Circle, RadiusAreaFerenceStayConsistent) {
    Circle circle(12.0);
    const double radius = circle.getRadius();
    const double ference = circle.getFerence();
    const double area = circle.getArea();

    EXPECT_NEAR(ference, 2.0 * M_PI * radius, kEps);
    EXPECT_NEAR(area, M_PI * radius * radius, kEps);
    EXPECT_NEAR(area, (ference * ference) / (4.0 * M_PI), kEps);
}

TEST(Circle, RepeatedSetAreaKeepsRadius) {
    Circle circle(8.0);
    const double area = circle.getArea();
    circle.setArea(area);
    EXPECT_NEAR(circle.getRadius(), 8.0, kEps);
}

TEST(Circle, RepeatedSetFerenceKeepsRadius) {
    Circle circle(8.0);
    const double ference = circle.getFerence();
    circle.setFerence(ference);
    EXPECT_NEAR(circle.getRadius(), 8.0, kEps);
}

TEST(Circle, LargeRadiusScalesAreaQuadratically) {
    Circle small(10.0);
    Circle large(20.0);
    EXPECT_NEAR(large.getArea(), 4.0 * small.getArea(), kEps);
}

TEST(Circle, SmallRadiusHasSmallArea) {
    Circle circle(0.01);
    EXPECT_LT(circle.getArea(), 0.001);
}

TEST(EarthRope, GapIsPositive) {
    EXPECT_GT(earthRopeGap(), 0.0);
}

TEST(EarthRope, GapMatchesAnalyticalEstimate) {
    const double expectedGap = 1.0 / (2.0 * M_PI);
    EXPECT_NEAR(earthRopeGap(), expectedGap, 0.01);
}

TEST(EarthRope, GapIsMuchSmallerThanEarthRadius) {
    EXPECT_LT(earthRopeGap(), 1.0);
}

TEST(EarthRope, GapIsDeterministic) {
    EXPECT_DOUBLE_EQ(earthRopeGap(), earthRopeGap());
}

TEST(PoolMaterials, TotalCostIsPositive) {
    EXPECT_GT(poolMaterialsCost(), 0.0);
}

TEST(PoolMaterials, TotalCostMatchesManualCalculation) {
    Circle pool(3.0);
    Circle outer(4.0);

    const double expectedConcrete = (outer.getArea() - pool.getArea()) * 1000.0;
    const double expectedFence = outer.getFerence() * 2000.0;
    const double expectedTotal = expectedConcrete + expectedFence;

    EXPECT_NEAR(poolMaterialsCost(), expectedTotal, 0.5);
}

TEST(PoolMaterials, FencePartDominatesConcretePart) {
    Circle pool(3.0);
    Circle outer(4.0);

    const double concretePart = (outer.getArea() - pool.getArea()) * 1000.0;
    const double fencePart = outer.getFerence() * 2000.0;

    EXPECT_GT(fencePart, concretePart);
    EXPECT_NEAR(poolMaterialsCost(), concretePart + fencePart, 0.5);
}
