/**
 * @file FoeVisitor.cpp
 * @author Western Tanager
 */

#include "pch.h"
#include "FoeVisitor.h"
#include "Foe.h"

/**
 * Visits each foe and increments it's counter
 * @param foe The visited foe
 */
void FoeVisitor::VisitFoe(Foe* foe)
{
    if (foe->IsAlive())
    {
        ++mAliveFoes;
    }
}