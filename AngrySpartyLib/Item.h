/**
 * @file Item.h
 * @author Western Tanager
 *
 * Base Class for all items in the game.
 */

#pragma once

#include <b2_body.h>
#include <memory>

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

    /** Pure virtual function for hit testing **/
    virtual bool HitTest(double x, double y) { return false; };
};
