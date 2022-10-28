/**
 * @file Item.h
 * @author Western Tanager
 *
 * Base Class for all items in the game.
 */

#pragma once

#include <b2_body.h>
#include <memory>
#include "World.h"

class ItemVisitor;
class Level;
class Sparty;

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

    /// Is this item alive?
    bool mAlive = false;

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
     * The bitmap for this item
     * @return The wxBitmap for this item
     */
    std::shared_ptr<wxBitmap> GetBitmap() { return mItemBitmap; }

    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics);

    virtual void XmlLoad(wxXmlNode* node);

    /** Installs physics for an item */
    virtual void InstallPhysics(std::shared_ptr<World>) {}

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

    // Shooter pass down methods.

    /**
     * Set the sparties to shoot inside the shooter.
     *
     * When the sparty is inside the shooter, it needs to be drawn by it.
     * @param sparties The sparties of the current level. These can be shot out of a shooter object.
     */
    virtual void SetSparties(std::vector<std::shared_ptr<Sparty>>& sparties) {}

    /**
     * Clear the Sparties that are in the shooter.
     *
     * If there are any sparties left in the shooter, they will be cleared out.
     */
    virtual void Clear() {}

    /**
     * Get the body for an item
     * @return This item's body (nullptr if no body)
     */
    virtual b2Body* GetBody() { return nullptr; }

    /**
     * Handles launching a sparty
     *
     * Empty for everything except shooters
     */
    virtual void LaunchSparty() {};

    /**
     * Whether or not this item is to be considered in the game
     * @return True if this item should still exist in the game
     */
    bool IsAlive() const { return mAlive; }

    /**
     * Enable/disable an item from the game
     * @param alive False to disable this item, true to "reset" it
     */
    void SetAlive(bool alive) { mAlive = alive; }

    /**
     * Resets an item
     *
     * Sets it to dead. Every item gets set
     * back to alive when setting its level
     */
    virtual void Reset() { mAlive = false; }
};
