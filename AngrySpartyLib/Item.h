/**
 * @file Item.h
 * @author Western Tanager
 *
 * Base Class for all items in the game.
 */

#pragma once

#include <b2_body.h>
#include <memory>

class ItemVisitor;
class Level;

/**
 * Base class for all items in the physics system
 */
class Item {
private:
    /// The level this item is contained in
    Level *mLevel;

    /// The underlying item image
    std::shared_ptr<wxImage> mItemImage;

    /// The underlying bitmap for the image.
    std::shared_ptr<wxBitmap> mItemBitmap;

public:
    /// Default constructor (disabled)
    Item() = delete;

    /// Copy constructor (disabled)
    Item(const Item &) = delete;

    Item(Level* level);

    /// Assignment operator (disabled)
    void operator=(const Item &) = delete;

    /// Destructor
    virtual ~Item();

    /**
     * Handle updates for animation
     * @param elapsed The time since the last update in seconds
     */
    virtual void Update(double elapsed) {}

    /// Indicates that the item has been released by the mouse
    virtual void Release() {}

    b2World* GetWorld();

    /**
     * Get the level this item is contained in.
     * @return The level this item is contained in.
     */
    Level* GetLevel() { return mLevel; }

    /**
     * The picture for this item
     * @return The wxImage for this item
     */
    std::shared_ptr<wxImage> GetPicture()  { return mItemImage; }

    /**
     * The bitmap for this item
     * @return The wxBitmap for this item
     */
    std::shared_ptr<wxBitmap> GetBitmap() { return mItemBitmap; }

    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics);

    virtual wxXmlNode* XmlSave(wxXmlNode* node);

    virtual void XmlLoad(wxXmlNode* node);

    /** Installs physics for an item */
    virtual void InstallPhysics() {}

    /**
     * Test to see if an item is hit by a mouse click
     * @param x x location of the mouse click
     * @param y y location of the mouse click
     * @return if the hit test is positive
     */
    virtual bool HitTest(double x, double y) { return false; }

    /**
     * Accept a visitor to the item.
     * @param visitor The visitor to accept.
     */
    virtual void Accept(ItemVisitor *visitor) = 0;
};
