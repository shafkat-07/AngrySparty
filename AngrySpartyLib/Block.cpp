/**
 * @file Block.cpp
 * @author Western Tanager
 */

#include "pch.h"

#include <b2_world.h>
#include <b2_circle_shape.h>
#include <b2_polygon_shape.h>
#include <b2_fixture.h>
#include "Block.h"
#include "Consts.h"

/**
 * Constructor for a block object
 *
 * Adds the physics to the item
 * @param level The level this item is contained in
 */
Block::Block(Level* level) : Item(level)
{

}

/**
 * Draw the block.
 * @param graphics The drawing context to draw on.
 */
void Block::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    graphics->PushState();

    b2Body* body = GetBody();
    auto position = body->GetPosition();
    auto angle = body->GetAngle();

    graphics->Translate(mPosition.x * Consts::MtoCM,
            mPosition.y * Consts::MtoCM); // TODO change to position.x and position.y ?
    graphics->Rotate(mAngle * Consts::DtoR); // TODO change to angle ?

    // Make this is left side of the rectangle
    double x = -mSize.x/2 * Consts::MtoCM;

    // And the top
    double y = mSize.y/2 * Consts::MtoCM;

    // The width of each repeated block
    double xw = mSize.x / mRepeatX * Consts::MtoCM;

    std::shared_ptr<wxBitmap> bitmap = std::make_shared<wxBitmap>(*GetPicture());

    graphics->Translate(0, y);
    graphics->Scale(1, -1);
    for(int ix=0; ix<mRepeatX;  ix++)
    {
        graphics->DrawBitmap(*bitmap,
                x,
                0,
                xw, mSize.y * Consts::MtoCM);

        x += xw;
    }

    graphics->PopState();
}

/**
 * Load the attributes for a block
 *
 * @param node The Xml node we are loading the item from
 */
void Block::XmlLoad(wxXmlNode* node)
{
    Item::XmlLoad(node);

    mPosition.x = std::stof(node->GetAttribute(L"x", "0.0").ToStdWstring());
    mPosition.y = std::stof(node->GetAttribute(L"y", "0.0").ToStdWstring());
    mSize.x = std::stof(node->GetAttribute(L"width", "0.0").ToStdWstring());
    mSize.y = std::stof(node->GetAttribute(L"height", "0.0").ToStdWstring());
    node->GetAttribute(L"angle", L"0").ToDouble(&mAngle);
    node->GetAttribute(L"repeat-x", L"1").ToInt(&mRepeatX);
}

/**
 * Create a fixture and assign a given shape to it.
 *
 * A fixture connects a shape to a body.
 *
 * @param shape Shape to assign.
 * @return the created b2Fixture object
 */
b2Fixture* Block::CreateFixture(b2Shape* shape)
{
    b2FixtureDef fixtureDef;
    fixtureDef.shape = shape;
    fixtureDef.density = 1;
    fixtureDef.friction = 0.5f;
    fixtureDef.restitution = 0.5f;

    return mBody->CreateFixture(&fixtureDef);
}

/**
 * Test items to see if they have been clicked on.
 * @param x X location in meters to test
 * @param y Y location in meters to test
 * @return Reference to the item clicked on.
 */
bool Block::HitTest(double x, double y)
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
 * Set the transform for the item.
 * @param location Item location in meters
 * @param angle Angle in radians
 */
void Block::SetTransform(const b2Vec2& location, double angle)
{
    mBody->SetTransform(location, (float)angle);
}

/**
 * Install physics for a block
 */
void Block::InstallPhysics()
{
    b2World* world = GetWorld();

    // Create the box
    b2PolygonShape box;
    box.SetAsBox(mSize.x/2, mSize.y/2);

    // Create the body definition
    b2BodyDef bodyDefinition;
    bodyDefinition.position = mPosition;
    bodyDefinition.angle = mAngle * Consts::DtoR;
    bodyDefinition.type = mStatic ? b2_staticBody : b2_dynamicBody;
    mBody = world->CreateBody(&bodyDefinition);

    if(mStatic)
    {
        mBody->CreateFixture(&box, 0.0f);
    }
    else
    {
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &box;
        fixtureDef.density = (float) mDensity;
        fixtureDef.friction = (float) mFriction;
        fixtureDef.restitution = (float) mRestitution;

        mBody->CreateFixture(&fixtureDef);
    }
}