/**
 * @file Item.cpp
 * @author Western Tanager
 *
 * The base class for items in the game.
 */

#include "pch.h"
#include "Item.h"
#include "Level.h"

#include <b2_fixture.h>
#include <b2_circle_shape.h>

/// The standard radius of a circle item.
const double StandardRadius = 0.3f;

/**
 * Constructor with a body definition.
 * @param level The level this item is contained in
 */
Item::Item(Level* level) : mLevel(level)
{
    b2BodyDef bodyDef;
    mBodyDef = &bodyDef;
    mBodyDef->type = b2_staticBody;
    mBody = GetWorld()->CreateBody(mBodyDef);

    // Create a circular default fixture.
    b2CircleShape shape;
    shape.m_radius = StandardRadius;

    mFixture = Item::CreateFixture(&shape);
}

/**
 * Test items to see if they have been clicked on.
 * @param x X location in meters to test
 * @param y Y location in meters to test
 * @return Reference to the item clicked on.
 */
bool Item::HitTest(double x, double y)
{
    b2Fixture* fixture = mBody->GetFixtureList();
    for ( ; fixture !=nullptr; fixture = fixture->GetNext())
    {
        auto shape = fixture->GetShape();
        if (shape->GetType() == b2Shape::e_polygon)
        {
            if(fixture->TestPoint(b2Vec2(x, y)))
            {
                return true;
            }
        }
    }
    return false;
}


/**
 * Create a fixture and assign a given shape to it.
 *
 * A fixture connects a shape to a body.
 *
 * @param shape Shape to assign.
 * @return the created b2Fixture object
 */
b2Fixture* Item::CreateFixture(b2Shape* shape)
{
    b2FixtureDef fixtureDef;
    fixtureDef.shape = shape;
    fixtureDef.density = 1;
    fixtureDef.friction = 0.5f;
    fixtureDef.restitution = 0.5f;

    return mBody->CreateFixture(&fixtureDef);
}

/**
 * Get the world that this item is in.
 * @return The world this item is in.
 */
b2World* Item::GetWorld()
{
    return mLevel->GetWorld();
}

/**
 * Destroy the item.
 */
Item::~Item()
{
    if (mBody != nullptr)
    {
        mLevel->GetWorld()->DestroyBody(mBody);
    }
}

/**
 * Set the transform for the item.
 * @param location Item location in meters
 * @param angle Angle in radians
 */
void Item::SetTransform(const b2Vec2& location, double angle)
{
    mBody->SetTransform(location, (float)angle);
}

/**
 * Draw the item.
 * @param graphics The drawing context to draw on.
 */
void Item::OnDraw(std::shared_ptr<wxGraphicsContext> graphics)
{
    if (mItemBitmap == nullptr)
    {
        return;
    }

    b2Vec2 position = mBody->GetPosition();
    double angle = mBody->GetAngle();

    graphics->Translate(position.x, position.y);
    graphics->Rotate(angle);

    graphics->DrawBitmap(*mItemBitmap, -mWidth / 2, -mHeight / 2, mWidth, mHeight);
}

/**
 * Load the attributes for an item node.
 *
 * This is the  base class version that loads the attributes
 * common to all items. Override this to load custom attributes
 * for specific items.
 *
 * @param node The Xml node we are loading the item from
 */
void Item::XmlLoad(wxXmlNode* node)
{
    // Get the attributes for this item
    mX = std::stof(node->GetAttribute(L"x", "0.0").ToStdWstring());
    mY = std::stof(node->GetAttribute(L"y", "0.0").ToStdWstring());
    mWidth = std::stof(node->GetAttribute(L"width", "0.0").ToStdWstring());
    mHeight = std::stof(node->GetAttribute(L"height", "0.0").ToStdWstring());
    mAngle = std::stof(node->GetAttribute(L"angle", "0.0").ToStdWstring());
    mFriction = std::stof(node->GetAttribute(L"friction", "0.5").ToStdWstring());
    mRestitution = std::stof(node->GetAttribute(L"restitution", "0.5").ToStdWstring());

    mBodyDef->type = b2_staticBody;
    mBodyDef->position.Set(mX, mY);
    mBodyDef->angle = (float) mAngle;
    mBodyDef->angularDamping = 1.0f;

    mWidth = mItemImage->GetWidth();
    mHeight = mItemImage->GetHeight();

    b2CircleShape shape;
    shape.m_radius = StandardRadius;

    GetWorld()->DestroyBody(mBody);
    mBody = GetWorld()->CreateBody(mBodyDef);

    mFixture = Item::CreateFixture(&shape);
}
/**
 * Save this item to an XML node
 * @param node The parent node we are going to be a child of
 * @return wxXmlNode that we saved the item into
 */
wxXmlNode* Item::XmlSave(wxXmlNode* node)
{
    return nullptr;
}
