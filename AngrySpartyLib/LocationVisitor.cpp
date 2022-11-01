/**
 * @file LocationVisitor.cpp
 * @author Western Tanager
 */

#include "pch.h"
#include "LocationVisitor.h"
#include "Shooter.h"

/**
 * Visit this shooter to compute the launch
 * location of the sparty based on the shooter's
 * characteristics
 * @param shooter The shooter from which we launch
 */
void LocationVisitor::VisitShooter(Shooter* shooter)
{
    mComputedLocation = shooter->ComputeLocation(mX, mY);
}