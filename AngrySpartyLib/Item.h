/**
 * @file Item.h
 * @author kabir and Brendan Bushbaker
 *
 * Base Class for all items in the game.
 */

#pragma once

#include <b2_body.h>
#include <memory>
#include <wx/graphics.h>
#include <wx/xml/xml.h>

class Level;
class b2Body;
class b2World;
class b2Fixture;
class b2Shape;

/**
 * Base class for all items in the physics system
 */
class Item {
private:
    /// The level this item is contained in
    Level *mLevel;

    /// The physics system body
    b2Body* mBody = nullptr;

    /// The box2d fixture
    b2Fixture* mFixture;

    /// The box2d body definition
    b2BodyDef mBodyDef;

    double mX = 0; ///< X location for the center of the item
    double mY = 0; ///< Y location for the center of the item

    double mWidth = 0; ///< Width of the item
    double mHeight = 0; ///< Height of the item

    std::unique_ptr<wxImage> mItemImage; ///< The underlying item image

    std::unique_ptr<wxBitmap> mItemBitmap; ///< The bitmap that can be displayed for an item
public:
    /// Default constructor (disabled)
    Item() = delete;

    /// Copy constructor (disabled)
    Item(const Item &) = delete;


    Item(Level* level, b2BodyDef bodyDef);


    /// Assignment operator (disabled)
    void operator=(const Item &) = delete;

    /// Destructor
    virtual ~Item();

    /**
     * Get the body of the item
     * @return body of the item
     */
    b2Body* GetBody() { return mBody; }

    /**
     * Get the fixture of the item
     * @return fixture of the item
     */
    b2Fixture* GetFixture() { return mFixture; }

    /**
     * Handle updates for animation
     * @param elapsed The time since the last update in seconds
     */
    virtual void Update(double elapsed) = 0;

    void SetTransform(const b2Vec2& location, double angle);

    virtual bool HitTest(double x, double y);

    b2Fixture* CreateFixture(b2Shape* sssssshape);

    /// Indicates that the item has been released by the mouse
    virtual void Release() {}

    b2World* GetWorld();

    /**
     * Get the X location for the center of the item
     * @return X location in pixels
     */
    double GetX() const { return mX; }

    /**
     * Get the Y location for the center of the item
     * @return Y location in pixels
     */
     double GetY() const { return mY; }

    /**
    * The width of the item.
    * @return Width in pixels
    */
    double GetWidth() const { return mWidth; }

    /**
     * The height of the item.
     * @return Height in pixels.
     */
    double GetHeight() const { return mHeight; }

    virtual void Draw(wxDC *dc);

    virtual wxXmlNode* XmlSave(wxXmlNode* node);

    virtual void XmlLoad(wxXmlNode* node);
};
