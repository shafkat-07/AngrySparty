/**
 * @file LocationVisitor.h
 * @author Western Tanager
 *
 * Concerete visitor to compute the location
 * for shooting sparties
 */

#ifndef ANGRYSPARTY_LOCATIONVISITOR_H
#define ANGRYSPARTY_LOCATIONVISITOR_H

#include <b2_math.h>
#include "ItemVisitor.h"

class Shooter;

/**
 * Concerete visitor to compute the location
 * for shooting sparties
 */
class LocationVisitor : public ItemVisitor{
private:
    /// The location computed by this visitor
    b2Vec2 mComputedLocation = b2Vec2(0,0);

    double mX; ///< The x location passed to this visitor
    double mY; ///< The y location passed to this visitor

public:
    /**
     * Constructor for the location visitor
     * @param x The x location used to compute a final location
     * @param y The y location used to compute a final location
     */
    LocationVisitor(double x, double y) : mX(x), mY(y) {mComputedLocation = b2Vec2(mX,mY); }

    void VisitShooter(Shooter* shooter) override;

    /**
     * Getter for the location computed by this visitor
     * @return The location computed by this visitor
     */
    b2Vec2 GetComputedLocation() { return mComputedLocation; }

};

#endif //ANGRYSPARTY_LOCATIONVISITOR_H
