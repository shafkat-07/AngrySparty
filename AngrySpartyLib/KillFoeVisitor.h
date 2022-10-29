/**
 * @file KillFoeVisitor.h
 * @author Western Tanager
 *
 * This visitor will remove the foe from the game when it is in a down state.
 */

#ifndef ANGRYSPARTY_KILLFOEVISITOR_H
#define ANGRYSPARTY_KILLFOEVISITOR_H

#include "ItemVisitor.h"

class Foe;

/**
 * This visitor will remove the foe from the game when it is in a down state.
 */
class KillFoeVisitor : public ItemVisitor
{
private:
    int mKilledFoes = 0; ///< Total number of foes eliminated by this visitor

public:
    void VisitFoe(Foe* foe) override;

    /**
     * Get the total number of foes eliminated
     * @return Total number of foes eliminated
     */
    int GetTotalKills() const { return mKilledFoes; }
};

#endif //ANGRYSPARTY_KILLFOEVISITOR_H
