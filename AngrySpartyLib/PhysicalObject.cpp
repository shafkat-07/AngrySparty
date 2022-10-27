/**
 * @file PhysicalObject.cpp
 * @author Western Tanager
 */

#include "pch.h"

#include <cmath>

#include <b2_body.h>
#include <b2_fixture.h>

#include "PhysicalObject.h"
#include "Level.h"
#include "Consts.h"

using namespace std;

/**
 * Constructor for a physical object
 * @param level The level this object is in
 */
PhysicalObject::PhysicalObject(Level* level) : Item(level)
{
}

/**
 * Draw the physical body.
 * @param graphics The drawing context to draw on.
 */
void PhysicalObject::Draw(shared_ptr<wxGraphicsContext> graphics)
{
}


/**
 * Update the object
 * @param elapsed time since last update
 */
void PhysicalObject::Update(double elapsed)
{

}

/**
 * Load the attributes for a physical object.
 *
 * This is the base class version that loads the attributes
 * common to all physical bodies. Override this to load custom
 * attributes for specific physical objects.
 *
 * @param node The Xml node we are loading the item from
 */
void PhysicalObject::XmlLoad(wxXmlNode* node)
{
    Item::XmlLoad(node);

    // Physical object common attributes
    mPosition.x = stof(node->GetAttribute(L"x", "0.0").ToStdWstring());
    mPosition.y = stof(node->GetAttribute(L"y", "0.0").ToStdWstring());

    node->GetAttribute(L"angle", "0.0").ToDouble( &mAngle);
    mAngle *= Consts::DtoR;

    auto staticType = node->GetAttribute(L"type", "");
    mStatic = staticType == "static";
}

/**
 * Install physics for a physical object
 * @param physicsWorld The physics world in which to install the object
 */
void PhysicalObject::InstallPhysics(std::shared_ptr<World> physicsWorld) // TODO Add physics parameter
{
    auto world = GetWorld(); // TODO use physics object in the level and get its world
    mBody = DefineBody(&(*CreateShape()), world);
}

/**
 * Define the body for a particular physical object
 * @param shape The b2Shape of the body
 * @param world The world in which this object resides
 * @return A pointer to a b2Body
 */
b2Body* PhysicalObject::DefineBody(b2Shape* shape, b2World* world)
{
    // Create the body definition
    b2BodyDef bodyDefinition;
    bodyDefinition.position = mPosition;
    bodyDefinition.angle = mAngle;
    bodyDefinition.type = mStatic ? b2_staticBody : b2_dynamicBody;
    auto body = world->CreateBody(&bodyDefinition);

    if(mStatic)
    {
        body->CreateFixture(shape, 0.0f);
    }
    else
    {
        b2FixtureDef fixtureDef;
        fixtureDef.shape = shape;
        fixtureDef.density = (float)mDensity;
        fixtureDef.friction = (float)mFriction;
        fixtureDef.restitution = (float)mRestitution;

        body->CreateFixture(&fixtureDef);
    }

    return body;
}

/**
 * Test items to see if they have been clicked on.
 * @param x X location in meters to test
 * @param y Y location in meters to test
 * @return Reference to the item clicked on.
 */
bool PhysicalObject::HitTest(double x, double y)
{
    b2Fixture* fixture = GetBody()->GetFixtureList();
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
 * Set a transfrom for this physical object's b2body
 * @param location The location for the transform
 * @param angle The angle of the transform
 */
void PhysicalObject::SetTransform(const b2Vec2& location, double angle)
{
    mBody->SetTransform(location, (float)angle);
}

/**
 * Find the distance between this body and another.
 * @param distantPos The position of the distant object in a vector.
 * @return The distance in meters of two bodies.
 */
double PhysicalObject::DistanceBetweenBodies(b2Vec2 distantPos)
{
    auto pos = mBody->GetPosition();
    auto distance = std::hypot(distantPos.x - pos.x, distantPos.y - pos.y);
    return distance;
}

/**
 * Find the angle between two bodies.
 * @param distantPos The position of the distant body.
 * @return The angle between the two bodies.
 */
double PhysicalObject::AngleBetweenBodies(b2Vec2 distantPos)
{
    auto pos = mBody->GetPosition();
    auto angle = std::atan2(distantPos.y - pos.y, distantPos.x - pos.x);
    return angle;
}
