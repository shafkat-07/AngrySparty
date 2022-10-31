/**
 * @file FoeCounter.h
 * @author Western Tanager
 *
 * Concrete visitor for counting foes
 */

#ifndef ANGRYSPARTY_FOECOUNTER_H
#define ANGRYSPARTY_FOECOUNTER_H

#include "ItemVisitor.h"
#include "Item.h"

/**
 * Concrete visitor for counting foes
 */
class FoeCounter : public ItemVisitor {
private:
    /// Number of foes alive in the current level
    int mAliveFoes = 0;

public:
    void VisitFoe(Foe* foe) override;

    /**
     * A getter for the foe count from the level
     * @return The number of foes
     */
    int GetNumFoes() const { return  mAliveFoes; }
};

#endif //ANGRYSPARTY_FOECOUNTER_H
