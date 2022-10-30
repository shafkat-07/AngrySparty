/**
 * @file Foe.h
 * @author Western Tanager
 *
 * Class to represent a Foe
 */

#ifndef ANGRYSPARTY_FOE_H
#define ANGRYSPARTY_FOE_H

#include "PolygonBody.h"
#include "ItemVisitor.h"

/**
 * Class to represent a foe
 */
class Foe : public PolygonBody {
private:
    double mRadius = 0; ///< Radius of the foe
    double mDown = 0; ///< Height below which this foe disappears

public:
    Foe(Level* level);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    void XmlLoad(wxXmlNode* node) override;

    /**
     * Accept a visitor to this item
     * @param visitor The visitor we accept
     */
    void Accept(ItemVisitor* visitor) override { visitor->VisitFoe(this); }

    /**
     * Get the down position of this foe.
     * @return The down position of this foe.
     */
    double GetDown() { return mDown; }
};

#endif //ANGRYSPARTY_FOE_H
