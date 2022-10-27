/**
 * @file FoeVisitor.h
 * @author Western Tanager
 *
 * Concrete visitor for counting foes
 */

#ifndef ANGRYSPARTY_FOEVISITOR_H
#define ANGRYSPARTY_FOEVISITOR_H

#include "ItemVisitor.h"
#include "Item.h"

/**
 * Concrete visitor for counting foes
 */
class FoeVisitor : public ItemVisitor{
private:
    /// Number of foes alive in the current level
    int mAliveFoes = 0;

public:
    /**
     * Visits each foe and increments it's counter
     * @param foe The visited foe
     */
    void VisitFoe(Foe* foe) override { ++mAliveFoes; }

    /**
     * A getter for the foe count from the level
     * @return The number of foes
     */
    int GetNumFoes() const { return  mAliveFoes; }
};

#endif //ANGRYSPARTY_FOEVISITOR_H
