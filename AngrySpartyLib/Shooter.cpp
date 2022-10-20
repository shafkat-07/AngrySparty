/**
 * @file Shooter.cpp
 * @author Western Tanager
 *
 * The function definitions for the shooter class.
 */

#include "pch.h"
#include <b2_world.h>
#include <b2_circle_shape.h>
#include <b2_polygon_shape.h>
#include <b2_fixture.h>
#include "Shooter.h"
#include "Consts.h"

/// File pointer to the image for the shooter
const std::wstring imageFilename = L"images/slingshot.png";

/// Size of the slingshot image in meters
const b2Vec2 WoodSlingshotSize = b2Vec2(0.5, 1.446);

/// Back band attachment point
const b2Vec2 WoodSlingshotBandAttachBack = b2Vec2(-0.15f, 1.12f);

/// Front band attachment point
const b2Vec2 WoodSlingshotBandAttachFront = b2Vec2(0.15f, 1.2f);

/// Maximum amount the slingshot can be pulled in meters
const double WoodSlingshotMaximumPull = 1;

/// Pull angles from -pi to this value are allowed
const double SlingshotMaximumNegativePullAngle = -1.7;

/// Pull angles from +pi to this value are allowed
const double SlingshotMinimumPositivePullAngle = 2.42;

/// Width of the slingshot band in centimeters
const int SlingshotBandWidth = 15;

/// The slingshot band colour
const wxColour SlingshotBandColor = wxColour(55, 18, 1);

Shooter::Shooter(Level* level)
        :Item(level)
{

}

void Shooter::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    graphics->PushState();

    auto bitmap = GetBitmap();

    graphics->Translate(mPosition.x, mPosition.y);
    graphics->Scale(1, -1);
    graphics->DrawBitmap(*bitmap, mPosition.x, mPosition.y, WoodSlingshotSize.x, WoodSlingshotSize.y);

    graphics->PopState();
}

/**
 * Load the attributes for a shooter
 *
 * @param node The node we are loading the shooter from
 */
void Shooter::XmlLoad(wxXmlNode* node)
{
    Item::XmlLoad(node);

    mPosition.x = std::stof(node->GetAttribute(L"x", "0.0").ToStdWstring()) * Consts::MtoCM;
    mPosition.y = std::stof(node->GetAttribute(L"y", "0.0").ToStdWstring()) * Consts::MtoCM;
}
/**
 * Install the physics for shooter
 */
void Shooter::InstallPhysics()
{
    b2World* world = GetWorld();

    // Create the box
    b2PolygonShape box;
    box.SetAsBox(WoodSlingshotSize.x/2, WoodSlingshotSize.y/2);

    // Create the body definition
    b2BodyDef bodyDefinition;
    bodyDefinition.position = mPosition;
    bodyDefinition.type = b2_staticBody;
    mBody = world->CreateBody(&bodyDefinition);

    mBody->CreateFixture(&box, 0.0f);
}
