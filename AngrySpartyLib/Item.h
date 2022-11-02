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

    /// Assignment operator (disabled)
    void operator=(const Item &) = delete;

    /// Destructor
    virtual ~Item();

    Item(Level* level);
    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics);
    virtual void XmlLoad(wxXmlNode* node);
    b2World* GetWorld();

    /**
     * Handle updates for animation
     * @param elapsed The time since the last update in seconds
     */
    virtual void Update(double elapsed) {}

    /**
     * Get the level this item is contained in.
     * @return The level this item is contained in.
     */
    Level* GetLevel() { return mLevel; }

    /**
     * The bitmap for this item
     * @return The wxBitmap for this item
     */
    virtual std::shared_ptr<wxBitmap> GetBitmap() { return mItemBitmap; }

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

    /**
     * Get the body for an item
     * @return This item's body (nullptr if no body)
     */
    virtual b2Body* GetBody() { return nullptr; }

    /**
     * Get the mouse joint for this item
     * Always nullptr for non-physical bodies
     * @return The mouse joint for this item
     */
    virtual b2MouseJoint* GetMouseJoint() { return nullptr; }

    /**
     * Set the mouse joint for this item
     * Does nothing for everything except for sparties
     * @param mouseJoint The mouse joint to be set
     */
    virtual void SetMouseJoint(b2MouseJoint* mouseJoint) {}

    /**
     * Handles launching a sparty
     *
     * Empty for everything except shooters
     */
    virtual void LaunchSparty() {};

    /**
     * Handle a click on an item
     * Does nothing for everything except for sparties
     * @param mouseLocation The location of the click
     */
    virtual void ClickItem(b2Vec2 mouseLocation) {}

    /**
     * Handle mouse movement for an item
     * Does nothing for everything except sparties
     * @param event The mouse event to be handled
     * @param mouseLocation The location of the mouse
     */
    virtual void MoveItem(wxMouseEvent &event, b2Vec2 mouseLocation) {}
};
