/**
 * @file ItemVisitor.h
 * @author Western Tanager
 *
 * A visitor to adjust values in various items.
 */

#ifndef ANGRYSPARTY_ITEMVISITOR_H
#define ANGRYSPARTY_ITEMVISITOR_H


class Foe;
class Sparty;
class Poly;
class Block;
class Shooter;

/**
 * A visitor to adjust values in various items.
 */
class ItemVisitor {
protected:
    /**
     * Constructor
     * Ensures this is an abstract class
     */
    ItemVisitor() {}

public:

    virtual ~ItemVisitor() {}

    /**
     * Visit a Foe object
     * @param foe Foe we are visiting
     */
    virtual void VisitFoe(Foe* foe) {}

    /**
     * Visit a Sparty object
     * @param sparty Sparty we are visiting
     */
    virtual void VisitSparty(Sparty* sparty) {}

    /**
     * Visit a Poly object.
     * @param poly Poly we are visiting
     */
    virtual void VisitPoly(Poly* poly) {}

    /**
     * Visit a Block object.
     * @param block Block we are visiting
     */
    virtual void VisitBlock(Block* block) {}

    /**
     * Visit a Shooter object.
     * @param shooter Shooter we are visiting
     */
    virtual void VisitShooter(Shooter* shooter) {}
};

#endif //ANGRYSPARTY_ITEMVISITOR_H
