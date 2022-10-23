/**
 * @file Block.h
 * @author Western Tanager
 *
 * Class to represent a block
 */

#ifndef ANGRYSPARTY_BLOCK_H
#define ANGRYSPARTY_BLOCK_H

#include "Item.h"
#include "PhysicalObject.h"

/**
 * Class to represent a block
 */
class Block : public PhysicalObject {
private:
    b2Vec2 mSize = b2Vec2(0.0f, 0.0f); ///< The dimensions of the block in meters
    int mRepeatX = 1; ///< Times this block repeats

public:
    Block(Level* level);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    void XmlLoad(wxXmlNode* node) override;
    b2PolygonShape CreateShape() override;
};

#endif //ANGRYSPARTY_BLOCK_H
