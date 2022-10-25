/**
 * @file Poly.h
 * @author Western Tanager
 *
 * Class to represent a poly
 */

#ifndef ANGRYSPARTY_POLY_H
#define ANGRYSPARTY_POLY_H

#include "PolygonBody.h"
#include "ItemVisitor.h"

/**
 * Class to represent a poly
 */
class Poly : public PolygonBody {
private:

public:
    Poly(Level* level);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    void XmlLoad(wxXmlNode* node) override;

    /**
     * Accept a visitor to this item
     * @param visitor The visitor we accept
     */
    void Accept(ItemVisitor* visitor) override { visitor->VisitPoly(this); }
};

#endif //ANGRYSPARTY_POLY_H