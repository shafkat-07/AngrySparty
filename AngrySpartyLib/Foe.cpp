/**
 * @file Foe.cpp
 * @author Western Tanager
 */

#include "pch.h"

#include <b2_world.h>
#include <b2_circle_shape.h>
#include <b2_polygon_shape.h>
#include <b2_fixture.h>
#include "Foe.h"
#include "Consts.h"

/**
 * Constructor for a foe object
 *
 * Adds the physics to the item
 * @param level The level this item is contained in
 */
Foe::Foe(Level* level) : Item(level)
{

}

/**
 * Draw the foe.
 * @param graphics The drawing context to draw on.
 */
void Foe::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    auto body = GetBody();
    //auto position = body->GetPosition(); TODO Uncomment this?
    //auto angle = body->GetAngle(); TODO Uncomment this?

    auto wid = mRadius * Consts::MtoCM * 2;
    auto x = mPosition.x * Consts::MtoCM; // TODO Change this to position.x ?
    auto y = mPosition.y * Consts::MtoCM;

    graphics->PushState();
    graphics->Translate(x, y);
    graphics->Rotate(mAngle * Consts::DtoR); // TODO Change this to angle ?

    std::shared_ptr<wxBitmap> bitmap = std::make_shared<wxBitmap>(*GetPicture());

    graphics->Scale(1, -1);
    graphics->DrawBitmap(*bitmap,
            -wid/2,
            -wid/2,
            wid, wid);

    graphics->PopState();
}

/**
 * Load the attributes for a foe
 *
 * @param node The Xml node we are loading the item from
 */
void Foe::XmlLoad(wxXmlNode* node)
{
    Item::XmlLoad(node);

    mPosition.x = std::stof(node->GetAttribute(L"x", "0.0").ToStdWstring());
    mPosition.y = std::stof(node->GetAttribute(L"y", "0.0").ToStdWstring());
    node->GetAttribute(L"angle", L"0").ToDouble(&mAngle);
    node->GetAttribute(L"radius", L"0").ToDouble(&mRadius);
    node->GetAttribute(L"down", L"0").ToDouble(&mDown);

    // Create the octagon to represent the Foe
    float x;
    float y;
    double degrees = 45;
    for (auto i = 0; i < 8; i++)
    {
        x = mRadius * cos(degrees*Consts::DtoR*i + mAngle * Consts::DtoR);
        y = mRadius * sin(degrees*Consts::DtoR*i + mAngle * Consts::DtoR);
        mVertices.push_back(b2Vec2(x,y));
    }
}

/**
 * Create a fixture and assign a given shape to it.
 *
 * A fixture connects a shape to a body.
 *
 * @param shape Shape to assign.
 * @return the created b2Fixture object
 */
b2Fixture* Foe::CreateFixture(b2Shape* shape)
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
bool Foe::HitTest(double x, double y)
{
    // TODO There is a nullptr error on the following line. Try debugging here
    std::cout << "Checking Foe at " << x << " | " << y <<'\n';
    return false; // Remove this to test
    auto fixture = GetBody()->GetFixtureList();
    for( ; fixture != nullptr; fixture = fixture->GetNext())
    {
        if(fixture->TestPoint(b2Vec2(x, y)))
        {
            return true;
        }
    }
    return false;
}

/**
 * Set the transform for the item.
 * @param location Item location in meters
 * @param angle Angle in radians
 */
void Foe::SetTransform(const b2Vec2& location, double angle)
{
    mBody->SetTransform(location, (float)angle);
}

/**
 * Install physics for a foe
 */
void Foe::InstallPhysics()
{
    b2World* world = GetWorld();

    // Create the polygon for the foe
    b2PolygonShape poly;
    poly.Set(&mVertices[0], mVertices.size());

    // Create the body definition
    b2BodyDef bodyDefinition;
    bodyDefinition.position = mPosition;
    bodyDefinition.angle = mAngle;
    bodyDefinition.type = mStatic ? b2_staticBody : b2_dynamicBody;
    auto body = world->CreateBody(&bodyDefinition);

    if(mStatic)
    {
        body->CreateFixture(&poly, 0.0f);
    }
    else
    {
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &poly;
        fixtureDef.density = (float)mDensity;
        fixtureDef.friction = (float)mFriction;
        fixtureDef.restitution = (float)mRestitution;

        body->CreateFixture(&fixtureDef);
    }
}
