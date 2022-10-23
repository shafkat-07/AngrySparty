/**
 * @file Foe.cpp
 * @author Western Tanager
 */

#include "pch.h"

#include <b2_world.h>
#include <b2_polygon_shape.h>
#include <b2_fixture.h>
#include "Foe.h"
#include "Consts.h"

/**
 * Constructor for a foe object
 *
 * @param level The level this item is contained in
 */
Foe::Foe(Level* level) : PolygonBody(level)
{
}

/**
 * Load the attributes for a foe
 *
 * Load radius and down, which are specific to a foe
 * Creates the vertices to denote the underlying octagon
 * @param node The Xml node we are loading the foe from
 */
void Foe::XmlLoad(wxXmlNode* node)
{
    PolygonBody::XmlLoad(node);

    // Foe-specific attributes
    node->GetAttribute(L"radius", L"0").ToDouble(&mRadius);
    node->GetAttribute(L"down", L"0").ToDouble(&mDown);

    // Create the octagon to represent the Foe
    std::vector<b2Vec2> & vertices = GetVertices();
    float x;
    float y;
    double degrees = 45;
    for (auto i = 0; i < 8; i++)
    {
        x = mRadius * cos(degrees*Consts::DtoR*i + GetAngle());
        y = mRadius * sin(degrees*Consts::DtoR*i + GetAngle());
        vertices.push_back(b2Vec2(x,y));
    }
}

/**
 * Draw the foe.
 * @param graphics The drawing context to draw on.
 */
void Foe::Draw(std::shared_ptr<wxGraphicsContext> graphics)
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
