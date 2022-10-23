/**
 * @file Poly.h
 * @author Western Tanager
 *
 * Class to represent a poly
 */

#ifndef ANGRYSPARTY_POLY_H
#define ANGRYSPARTY_POLY_H

#include "Item.h"
#include "PolygonBody.h"

/**
 * Class to represent a poly
 */
class Poly : public PolygonBody {
private:

public:
    Poly(Level* level);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    void XmlLoad(wxXmlNode* node) override;
};

#endif //ANGRYSPARTY_POLY_H