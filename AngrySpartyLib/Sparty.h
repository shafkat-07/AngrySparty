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
    float mVelocityFactor = 0; ///< Velocity factor for this sparty
    bool mBoosted = false; ///< If the sparty has been boosted by a booster.
    b2MouseJoint* mMouseJoint = nullptr; ///< Mouse joint for moving things

public:
    Sparty(Level* level);
    void XmlLoad(wxXmlNode* node) override;
    void ModifyBodyToDynamic();
    b2Body* DefineBody(b2Shape* shape, b2World* world) override;
    void Reset() override;

    // Mouse functions
    void ClickItem(b2Vec2 mouseLocation) override;
    void MoveItem(wxMouseEvent& event, b2Vec2 mouseLocation) override;

    /**
     * Accept a visitor to this item
     * @param visitor The visitor we accept
     *
     * This will install the physics for the sparty.
     */
    void Accept(ItemVisitor* visitor) override { visitor->VisitSparty(this); }

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

    /**
     * Get this sparty's mouse joint
     * @return The sparty's mouse joint
     */
    b2MouseJoint* GetMouseJoint() override { return mMouseJoint; }

    /**
     * Set the mouse for this sparty
     *
     * Used by game to reset the mouse joint to nullptr on release
     * @param mouseJoint The mouse joint to be set
     */
    void SetMouseJoint(b2MouseJoint* mouseJoint) override { mMouseJoint = mouseJoint; }
};

#endif //ANGRYSPARTY_SPARTY_H

