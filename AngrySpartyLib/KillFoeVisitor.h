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

public:
    void VisitFoe(Foe* foe) override;
};

#endif //ANGRYSPARTY_KILLFOEVISITOR_H
