/**
 * @file CircleBody.cpp
 * @author Western Tanager
 *
 * The CircleBody class for the Angry Sparty game.
 *
 * Defines the member functions for the CircleBody class.
 */
#include "pch.h"

#include <b2_circle_shape.h>

#include "CircleBody.h"
#include "Level.h"
#include "Consts.h"

const double DefaultRadius = 0.25f;

/**
 * Constructor for a circle body
 * @param level The level this item is contained in
 */
CircleBody::CircleBody(Level* level) : PhysicalObject(level)
{
    mRadius = DefaultRadius;
}

/**
 * Create a shape for a circle body
 * @return The b2CircleShape for a circle body
 */
std::unique_ptr<b2Shape> CircleBody::CreateShape()
{
    std::unique_ptr<b2CircleShape> circle = std::make_unique<b2CircleShape>();
    circle->m_radius = mRadius;
    return circle;
}

/**
 * Load the attributes for a circle body
 *
 * Load radius and down, which are specific to a circle body
 * @param node The Xml node we are loading the circle body from
 */
void CircleBody::XmlLoad(wxXmlNode* node)
{
    PhysicalObject::XmlLoad(node);

    // CircleBody-specific attributes
    auto position = GetPosition();
    double spacing = std::stof(node->GetParent()->GetAttribute(L"spacing", "0.0").ToStdWstring()) * GetLevel()->GetSpartyCount();
    position.x = std::stof(node->GetParent()->GetAttribute(L"x", "0.0").ToStdWstring()) + spacing;
    position.y = std::stof(node->GetParent()->GetAttribute(L"y", "0.0").ToStdWstring());
    SetXPosition(position.x);
    SetYPosition(position.y);

}

void CircleBody::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    auto body = GetBody();
    auto position = body->GetPosition();
    auto angle = body->GetAngle();
    auto wid = mRadius * Consts::MtoCM * 2;

    auto x = position.x * Consts::MtoCM;
    auto y = position.y * Consts::MtoCM;

    graphics->PushState();
    graphics->Translate(x, y);
    graphics->Rotate(angle);

    std::shared_ptr<wxBitmap> bitmap = GetBitmap();

    graphics->Scale(1, -1);
    graphics->DrawBitmap(*bitmap,
            -wid/2,
            -wid/2,
            wid, wid);
    graphics->PopState();
}

/**
 * Test items to see if they have been clicked on.
 * @param x X location in meters to test
 * @param y Y location in meters to test
 * @return True if this item was clicked on
 */
bool CircleBody::HitTest(double x, double y)
{
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
