/**
 * @file Item.cpp
 * @author kabir and Brendan Bushbaker
 *
 * The base class for items in the game.
 */

//#include "pch.h"
#include "Item.h"
#include "Level.h"

#include <b2_fixture.h>


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
 * @param dc The drawing context to draw on.
 */
void Item::Draw(wxDC* dc)
{
    double wid = mItemBitmap->GetWidth();
    double hit = mItemBitmap->GetHeight();
    dc->DrawBitmap(*mItemBitmap,
            int(GetX() - wid / 2),
            int(GetY() - hit / 2));
}

void Item::XmlLoad(wxXmlNode* node)
{

}

wxXmlNode* Item::XmlSave(wxXmlNode* node)
{
    return nullptr;
}
