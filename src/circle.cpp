// Copyright 2022 UNN-CS
#define _USE_MATH_DEFINES
#include <cmath>
#include "circle.h"

namespace {
constexpr double kPi = M_PI;
}

void Circle::recalcFromRadius() {
    ference_ = 2.0 * kPi * radius_;
    area_ = kPi * radius_ * radius_;
}

void Circle::recalcFromFerence() {
    radius_ = ference_ / (2.0 * kPi);
    area_ = (ference_ * ference_) / (4.0 * kPi);
}

void Circle::recalcFromArea() {
    radius_ = std::sqrt(area_ / kPi);
    ference_ = 2.0 * kPi * radius_;
}

Circle::Circle(double radius) {
    radius_ = radius;
    recalcFromRadius();
}

void Circle::setRadius(double radius) {
    radius_ = radius;
    recalcFromRadius();
}

void Circle::setFerence(double ference) {
    ference_ = ference;
    recalcFromFerence();
}

void Circle::setArea(double area) {
    area_ = area;
    recalcFromArea();
}

double Circle::getRadius() const {
    return radius_;
}

double Circle::getFerence() const {
    return ference_;
}

double Circle::getArea() const {
    return area_;
}
