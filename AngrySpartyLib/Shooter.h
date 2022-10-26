/**
 * @file Shooter.h
 * @author Western Tanager
 *
 * The shooter class of the game.
 *
 * Can shoot angry sparties towards the enemies.
 */

#ifndef ANGRYSPARTY_SHOOTER_H
#define ANGRYSPARTY_SHOOTER_H

#include "Item.h"
#include "ItemVisitor.h"

class Sparty;

/**
 * The shooter class of the game.
 *
 * Can shoot angry sparties towards the enemies.
 */
class Shooter : public Item {
private:
    double mX = 0; ///< X location of the shooter
    double mY = 0; ///< Y location of the shooter
    double mWidth = 0; ///< Width of the shooter
    double mHeight = 0; ///< Height of the shooter
    std::shared_ptr<wxImage> mFrontImage; ///< The front image for the shooter
    std::shared_ptr<wxBitmap> mFrontBitmap; ///< The front bitmap for the shooter
    std::vector<std::shared_ptr<Sparty>> mSparties; ///< The sparties in the ready queue for the shooter.
    std::shared_ptr<Sparty> mSparty; ///< The sparty currently being shot by the shooter.

public:
    Shooter(Level* level);
    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics);
    virtual void XmlLoad(wxXmlNode* node);

    /**
     * Get the width of the shooter
     * @return Width of the shooter
     */
    double GetWidth() const {return mWidth;}

    /**
     * Set the width of the shooter
     * @param width The width of the shooter
     */
    void SetWidth(double width) { mWidth = width;}

    /**
     * Get the height of the shooter
     * @return Height of the shooter
     */
    double GetHeight() const {return mHeight;}

    /**
     * Set the height of the shooter
     * @param height The height of the shooter
     */
    void SetHeight(double height) { mHeight = height;}

    /**
     * Get the x position of the shooter
     * @return X position of the shooter
     */
    double GetX() const {return mX;}
    /**
     * Get the y position of the shooter
     * @return Y position of the shooter
     */
    double GetY() const {return mY;}

    /**
     * Get the pointer to the sparty currently being shot.
     */
    std::shared_ptr<Sparty> GetSparty() {return mSparty;}

    /**
     * The front bitmap for this shooter
     * @return The front wxBitmap for this shooter
     */
    std::shared_ptr<wxBitmap> GetFrontBitmap() { return mFrontBitmap; }

    /**
     * Accept a visitor to this item
     * @param visitor The visitor we accept
     *
     * Does nothing.
     */
    virtual void Accept(ItemVisitor* visitor) { }

    void SetSparties(std::vector<std::shared_ptr<Sparty>>& sparties) override;

    void Clear() override;

    void Update(double elapsed) override;
};

#endif //ANGRYSPARTY_SHOOTER_H
