/**
 * @file Ring.h
 * @author Western Tanager
 *
 * The moving ring for a level
 */

#ifndef ANGRYSPARTY_RING_H
#define ANGRYSPARTY_RING_H

#include "Item.h"

/**
 * Class to represent our team's feature
 *
 * It is a moving ring that goes up and down.
 * If a Sparty hits the ring, it will gain a 2x speed boost.
 */
class Ring : public Item {
private:
    double mY = 0; ///< Inital x-position of the ring in meters
    double mSpeedY = 0;///< Vertical speed of the ring
    double mRadius = 0; ///< The radius of the ring
    double mAngle = 0; ///< The angle to make the ring rotate

    /// The underlying ring image
    std::shared_ptr<wxImage> mRingImage;

    /// The ring bitmap for the image.
    std::shared_ptr<wxBitmap> mRingBitmap;

public:
    Ring(Level* level);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    void Update(double elapsed) override;
    void Reset() override;

    /**
     * Visit the ring
     * @param visitor The visitor to pass through
     *
     * Does nothing.
     */
    void Accept(ItemVisitor* visitor) override {  }

    /**
     * The bitmap for the ring
     * @return The wxBitmap for this item
     */
    std::shared_ptr<wxBitmap> GetBitmap() override { return mRingBitmap; }
};

#endif //ANGRYSPARTY_RING_H
