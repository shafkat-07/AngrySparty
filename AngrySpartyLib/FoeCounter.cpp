/**
 * @file FoeCounter.cpp
 * @author Western Tanager
 */

#include "pch.h"
#include "FoeCounter.h"
#include "Foe.h"

/**
 * Visits each foe and increments it's counter
 * @param foe The visited foe
 */
void FoeCounter::VisitFoe(Foe* foe)
{
    if (foe->IsAlive())
    {
        ++mAliveFoes;
    }
}