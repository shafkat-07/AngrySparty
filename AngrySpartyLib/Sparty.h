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
    double mDown = 0;    ///< Velocity at which this sparty disappears

public:
    Sparty(Level* level);
    void XmlLoad(wxXmlNode* node) override;

    /**
     * Accept a visitor to this item
     * @param visitor The visitor we accept
     *
     * This will install the physics for the sparty.
     */
    void Accept(ItemVisitor* visitor) override { visitor->VisitSparty(this); }
};

#endif //ANGRYSPARTY_SPARTY_H

