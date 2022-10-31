/**
 * @file CircleBody.h
 * @author Western Tanager
 *
 * Class to represent objects that have circle bodies.
 *
 * Sparties
 */

#ifndef ANGRYSPARTY_CIRCLEBODY_H
#define ANGRYSPARTY_CIRCLEBODY_H

#include "PhysicalObject.h"

class Level;

/**
 * Class to represent objects that have circle bodies.
 *
 * Sparties (circle) are derived from this class.
 */
class CircleBody : public PhysicalObject
{
private:
    double mRadius = 0; ///< Radius of the circle body

public:
    CircleBody(Level* level);
    std::unique_ptr<b2Shape> CreateShape();
    void XmlLoad(wxXmlNode* node) override;
    bool HitTest(double x, double y) override;
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    /**
     * Get the radius of this circle body
     * @return The radius of this circle body
     */
    double GetRadius() const { return mRadius; }
};

#endif //ANGRYSPARTY_CIRCLEBODY_H
