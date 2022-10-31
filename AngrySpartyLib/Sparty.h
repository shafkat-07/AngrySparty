/**
 * @file Sparty.h
 * @author Western Tanager
 *
 * The Sparty class for the Angry Sparty game.
 *
 * Sparties attack the foes. They can be launched from a shooter and can score points.
 */

#ifndef ANGRYSPARTY_SPARTY_H
#define ANGRYSPARTY_SPARTY_H

#include "CircleBody.h"
#include "ItemVisitor.h"

class Level;

/**
 * Class to represent a sparty
 */
class Sparty : public CircleBody
{
private:
    double mStopVelocity = 0;    ///< Velocity at which this sparty disappears
    float mVelocityFactor = 0; ///< Velocity factor for this sparty
    bool mBoosted = false; ///< If the sparty has been boosted by a booster.

public:
    Sparty(Level* level);
    void XmlLoad(wxXmlNode* node) override;
    void ModifyBodyToDynamic();
    b2Body* DefineBody(b2Shape* shape, b2World* world) override;
    void Reset() override;

    /**
     * Accept a visitor to this item
     * @param visitor The visitor we accept
     *
     * This will install the physics for the sparty.
     */
    void Accept(ItemVisitor* visitor) override { visitor->VisitSparty(this); }

    /**
     * Set the velocity factor of this sparty.
     * @param factor The velocity factor of this sparty.
     */
    void SetVelocityFactor(double factor) { mVelocityFactor = factor; }

    /**
     * Get the velocity factor of this sparty.
     * @return The velocity factor of this sparty.
     */
    double GetVelocityFactor() { return mVelocityFactor; }

    /**
     * Set the boosted state of this sparty.
     * @param boosted The boosted state of this sparty.
     */
    void SetBoosted(bool boosted) { mBoosted = boosted; }

    /**
     * Get the boosted state of this sparty.
     * @return The boosted state of this sparty.
     */
    bool GetBoosted() { return mBoosted; }
};

#endif //ANGRYSPARTY_SPARTY_H

