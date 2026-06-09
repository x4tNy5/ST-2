// Copyright 2022 UNN-CS
#include "tasks.h"
#include "circle.h"

double earthRopeGap() {
    const double earthRadiusMeters = 6378.1 * 1000.0;
    const double addedRopeLength = 1.0;

    Circle equator(earthRadiusMeters);
    const double radiusBefore = equator.getRadius();
    equator.setFerence(equator.getFerence() + addedRopeLength);

    return equator.getRadius() - radiusBefore;
}

double poolMaterialsCost() {
    const double poolRadius = 3.0;
    const double walkwayWidth = 1.0;
    const double concretePrice = 1000.0;
    const double fencePrice = 2000.0;

    Circle pool(poolRadius);
    Circle walkwayRing(poolRadius + walkwayWidth);

    const double walkwayArea = walkwayRing.getArea() - pool.getArea();
    const double concreteCost = walkwayArea * concretePrice;
    const double fenceCost = walkwayRing.getFerence() * fencePrice;

    return concreteCost + fenceCost;
}
