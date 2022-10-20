/**
 * @file Background.h
 * @author Western Tanager
 *
 * Class for a background item
 */

#ifndef ANGRYSPARTY_BACKGROUND_H
#define ANGRYSPARTY_BACKGROUND_H

#include "Item.h"

/**
 * Class for a background item
 */
class Background : public Item {
private:
    double mWidth = 0; ///< Width of the item
    double mHeight = 0; ///< Height of the item

public:
    Background(Level* level);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    void XmlLoad(wxXmlNode* node) override;
    bool HitTest(double x, double y) override;
};

#endif //ANGRYSPARTY_BACKGROUND_H
