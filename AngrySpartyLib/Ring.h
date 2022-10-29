/**
 * @file Ring.h
 * @author Western Tanager
 *
 * The moving ring for a level
 */

#ifndef ANGRYSPARTY_RING_H
#define ANGRYSPARTY_RING_H

#include "Item.h"

class Level;

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
    bool mActive = false; ///< Is the ring active?

    /// The underlying ring image
    std::shared_ptr<wxImage> mRingImage;

    /// The ring bitmap for the image.
    std::shared_ptr<wxBitmap> mRingBitmap;

public:
    Ring(Level* level);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    void Update(double elapsed) override;

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

    /**
     * Is the ring active?
     * @return True if the ring is active
     */
    bool IsActive() const { return mActive; }

    /**
     * Enable/disable the ring
     * @param activate True to enable the ring
     */
    void SetActive(bool activate)  { mActive = activate; }

    void Reset() override;
};

#endif //ANGRYSPARTY_RING_H
