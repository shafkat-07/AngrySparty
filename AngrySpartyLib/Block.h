/**
 * @file Block.h
 * @author Western Tanager
 *
 * Class to represent a block
 */

#ifndef ANGRYSPARTY_BLOCK_H
#define ANGRYSPARTY_BLOCK_H

#include "PhysicalObject.h"
#include "ItemVisitor.h"

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
    std::unique_ptr<b2Shape> CreateShape() override;

    /**
     * Accept a visitor to this item
     * @param visitor The visitor we accept
     */
    void Accept(ItemVisitor* visitor) override { visitor->VisitBlock(this); }
};

#endif //ANGRYSPARTY_BLOCK_H