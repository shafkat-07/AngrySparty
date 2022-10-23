/**
 * @file Foe.h
 * @author Western Tanager
 *
 * Class to represent a Foe
 */

#ifndef ANGRYSPARTY_FOE_H
#define ANGRYSPARTY_FOE_H

#include "Item.h"
#include "PolygonBody.h"

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
};

#endif //ANGRYSPARTY_FOE_H
